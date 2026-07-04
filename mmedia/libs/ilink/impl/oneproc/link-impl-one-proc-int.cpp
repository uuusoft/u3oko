/**
\file       link-impl-one-proc-int.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_ilink
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "link-impl-one-proc-int.hpp"

namespace libs::ilink::impl::oneproc
{
auto
to_string (
  const CreateInfoExt&                      info,
  const syn::IEvent::ptr&                   msg,
  const syn::CallSyncs&                     sync,
  const syn::Calls&                         req,
  const ::libs::events::ISeqEvent::id_type& id) -> std::string
{
  std::string res = to_string (info);

  res += " " + to_string (sync);
  res += " " + to_string (req);
  res += (id.empty () ? "" : (" sid=" + ::libs::utility::utils::to_string (id)));

  if (::libs::events::helpers::get_base_msg (msg)->get_mid () != msg->get_mid ())
  {
    res += " msgs=" + std::string { msg->get_mid () } + "+" + std::string { ::libs::events::helpers::get_base_msg (msg)->get_mid () };
  }
  else
  {
    res += " msg=" + std::string { msg->get_mid () };
  }
  return res;
}


LinkImplOneProcInt::LinkImplOneProcInt () :
  cmd_send_msgs_ (::libs::ilink::consts::max_count_unsend_msg),
  cmd_recv_msgs_ (::libs::ilink::consts::max_count_unsend_msg)
{
  create_flag_.store (false);
  counter_ref_.store (0);
}


auto
LinkImplOneProcInt::connect (const CreateInfoExt& info) -> bool
{
  U3_XLOG_DBG ("LinkImplOneProcInt::connect::---->" + TOLOG (to_string (info)));
  U3_ASSERT (!info.id_arg2val_[::libs::link::consts::text::id_name_queue2dest].empty ());
  U3_ASSERT (!info.id_arg2val_[::libs::link::consts::text::id_name_shared_mem].empty ());

  ++counter_ref_;

  if (!info.id_arg2val_[::libs::link::consts::text::id_proc_name].empty ())
  {
    create_flag_.store (true);

    loader_.load (
      info.run_as_,
      &info,
      info.id_arg2val_[::libs::link::consts::text::id_proc_name],
      info.id_arg2val_[::libs::link::consts::text::id_lib_name],
      info.args_);
  }
  U3_ASSERT (counter_ref_ <= 2);
  return loader_.is_load ();
}


auto
LinkImplOneProcInt::listen (const CreateInfoExt& info) -> bool
{
  U3_ASSERT (!info.id_arg2val_[::libs::link::consts::text::id_name_queue2dest].empty ());
  U3_ASSERT (!info.id_arg2val_[::libs::link::consts::text::id_name_shared_mem].empty ());
  ++counter_ref_;
  create_flag_.store (false);
  U3_ASSERT (counter_ref_ <= 2);
  return true;
}


auto
LinkImplOneProcInt::destroy (const CreateInfoExt& info, const ::libs::link::LinkDestroys& type) -> bool
{
  const std::string name_subsys = info.id_arg2val_[::libs::link::consts::text::id_subsys_name];
  const bool        force       = ::libs::link::LinkDestroys::force == type;
  bool              res_unload  = false;

  {
    lock_type lock (mtx_);
    --counter_ref_;
    if (counter_ref_ > 0 && !force)
    {
      return true;
    }
  }

  std::int32_t counter = 0;
  do
  {
    lock_type lock (mtx_);
    res_unload = loader_.unload (force);
    if (res_unload || !force)
    {
      info.id_arg2val_.clear ();
    }
    ++counter;
  } while (!res_unload && !force);
  return true;
}


auto
LinkImplOneProcInt::is_connected () const -> bool
{
  return counter_ref_ > 1 ? true : false;
}


auto
LinkImplOneProcInt::received_msg (const CreateInfoExt& info) -> syn::IEvent::ptr
{
  event_msgs_type* plist = info.server_side_ ? &cmd_recv_msgs_ : &cmd_send_msgs_;
  if (0 == plist->read_available ())
  {
    return {};
  }

  syn::IEvent::ptr ret;
  U3_CHECK (plist->pop (ret), "plist->pop(ret) empty");
  return ret;
}


auto
LinkImplOneProcInt::wrap_msg (
  const syn::CallSyncs&                     sync,
  const syn::Calls&                         req,
  const ::libs::events::ISeqEvent::id_type& seqid,
  syn::IEvent::ptr                          msg) -> syn::IEvent::ptr
{
  switch (req)
  {
  case ::libs::link::details::Calls::request:
    msg = ::libs::events::helpers::wrap_request_msg (msg);
    break;
  case ::libs::link::details::Calls::answer:
    msg = ::libs::events::helpers::wrap_answer_msg (msg);
    break;
  case ::libs::link::details::Calls::set:
  case ::libs::link::details::Calls::generate:
  case ::libs::link::details::Calls::unknown:
    // no wrap
    break;
  default:
    // no wrap
    break;
  }

  if (syn::CallSyncs::sync == sync)
  {
    msg = ::libs::events::helpers::wrap_sync_msg (msg);
  }

  if (!seqid.empty ())
  {
    msg = ::libs::events::helpers::wrap_seq_msg (msg, seqid);
  }
  return msg;
}


auto
LinkImplOneProcInt::send_msg (
  const CreateInfoExt&                      info,
  syn::IEvent::ptr                          msg,
  const syn::CallSyncs&                     sync,
  const syn::Calls&                         req,
  const ::libs::events::ISeqEvent::id_type& seqid) -> syn::IEvent::ptr
{
  event_msgs_type* plist = info.server_side_ ? &cmd_send_msgs_ : &cmd_recv_msgs_;
  if (0 == plist->write_available ())
  {
    return {};
  }

  msg = wrap_msg (sync, req, seqid, msg);

  U3_CHECK (plist->push (msg), "plist->push (msg) full");
  if (syn::CallSyncs::async == sync)
  {
    return {};
  }

  SyncStackState sync_block;
  {
    lock_type        lock (mtx_);
    syn::IEvent::ptr base_msg = ::libs::events::helpers::get_base_msg (msg);
    U3_ASSERT (wait_sync_msgs_.end () == wait_sync_msgs_.find (base_msg));
    U3_ASSERT_NT (wait_sync_msgs_.size () < 256, "wait_sync_msgs_.size () < 256" + VTOLOG (wait_sync_msgs_.size ()));
    wait_sync_msgs_[base_msg] = &sync_block;
  }
  if (!sync_block.complited_)
  {
    std::unique_lock< SyncStackState::sync_type > intlock (sync_block.evnt_mtx_);
    auto                                          wres = sync_block.evnt_.wait_for (intlock, std::chrono::milliseconds (60 * 1000));
    if (wres == std::cv_status::timeout)
    {
      U3_XLOG_ERROR ("LinkImplOneProcInt::send_msg: timeout wait sync msg sync" + PTR_TOLOG (&sync_block));
    }
  }
  return sync_block.active_msg_;
}


void
LinkImplOneProcInt::complite_msg (
  const CreateInfoExt&                   info,
  const syn::IEvent::ptr&                msg,
  const ::libs::link::StateProcessEvent& state)
{
  {
    lock_type        lock (mtx_);
    syn::IEvent::ptr base_ret = ::libs::events::helpers::get_base_msg (msg);
    auto             rit      = wait_sync_msgs_.find (base_ret);

    if (wait_sync_msgs_.end () != rit)
    {
      U3_XLOG_DBG ("LinkImplOneProcInt::complite_msg: prepeare send sync answer" + TOLOG (to_string (state.id_seq_)));
      SyncStackState::lock_type intlock (rit->second->evnt_mtx_);
      U3_XLOG_DBG ("LinkImplOneProcInt::complite_msg: begin send sync answer" + TOLOG (to_string (state.id_seq_)));
      rit->second->complited_  = true;
      rit->second->active_msg_ = base_ret;
      rit->second->evnt_.notify_all ();
      wait_sync_msgs_.erase (rit);
      U3_XLOG_DBG ("LinkImplOneProcInt::complite_msg: end send sync answer" + TOLOG (to_string (state.id_seq_)));
      return;
    }
  }

  U3_XLOG_DBG ("begin send answer" + TOLOG (to_string (state.id_seq_)));
  auto ret = send_msg (info, msg, syn::CallSyncs::async, syn::Calls::answer, state.id_seq_);
  U3_XLOG_DBG ("end send answer" + TOLOG (to_string (state.id_seq_)));
  U3_ASSERT (!ret);
}
}   // namespace libs::ilink::impl::oneproc
