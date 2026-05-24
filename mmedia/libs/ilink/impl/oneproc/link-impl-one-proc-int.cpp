/**
\file       link-impl-one-proc-int.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "link-impl-one-proc-int.hpp"

namespace libs::ilink::impl::oneproc::consts
{
constexpr std::uint64_t max_count_unsend_msg     = 32 * 1024;   //<
constexpr std::uint64_t warning_count_unsend_msg = 1 * 1024;    //<
}   // namespace libs::ilink::impl::oneproc::consts


namespace libs::ilink::impl::oneproc
{
std::string
to_string (
  const CreateInfoExt&                      info,
  const ::libs::events::IEvent::ptr&        msg,
  const ::libs::link::details::CallSyncs&   sync,
  const ::libs::link::details::Calls&       req,
  const ::libs::events::ISeqEvent::id_type& id)
{
  std::string res = to_string (info);

  res += " " + to_string (sync);
  res += " " + to_string (req);
  res += (id.empty () ? "" : (" sid=" + ::libs::helpers::utils::to_string (id)));

  if (::libs::events::helpers::get_base_msg (msg)->get_mid () != msg->get_mid ())
  {
    res += " msgs=" + msg->get_mid () + "+" + ::libs::events::helpers::get_base_msg (msg)->get_mid ();
  }
  else
  {
    res += " msg=" + msg->get_mid ();
  }
  return res;
}


LinkImplOneProcInt::LinkImplOneProcInt ()
{
  create_flag_.store (false);
  counter_ref_.store (0);
}


LinkImplOneProcInt::~LinkImplOneProcInt ()
{
}


bool
LinkImplOneProcInt::connect (const CreateInfoExt& info)
{
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


bool
LinkImplOneProcInt::listen (const CreateInfoExt& info)
{
  U3_ASSERT (!info.id_arg2val_[::libs::link::consts::text::id_name_queue2dest].empty ());
  U3_ASSERT (!info.id_arg2val_[::libs::link::consts::text::id_name_shared_mem].empty ());
  ++counter_ref_;
  create_flag_.store (false);
  U3_ASSERT (counter_ref_ <= 2);
  return true;
}


bool
LinkImplOneProcInt::destroy (const CreateInfoExt& info, const ::libs::link::LinkDestroys& type)
{
  const std::string name_subsys = info.id_arg2val_[::libs::link::consts::text::id_subsys_name];
  const bool        force       = ::libs::link::LinkDestroys::force == type;
  bool              res_unload  = false;

  {
    lock_type lock (mtx_);
    // U3_ASSERT_INFO (counter_ref_ > 0, "count ref less or equal 0");
    --counter_ref_;
    if (counter_ref_ > 0 && !force)
    {
      return true;
    }
  }

  std::int32_t counter_unload = 0;
  do
  {
    lock_type lock (mtx_);
    res_unload = loader_.unload (force);
    if (res_unload || !force)
    {
      info.id_arg2val_.clear ();
    }
    counter_unload = counter_unload + 1;
  } while (!res_unload && !force);
  return true;
}


bool
LinkImplOneProcInt::is_connected () const
{
  return counter_ref_ > 1 ? true : false;
}


::libs::events::IEvent::ptr
LinkImplOneProcInt::received_msg (const CreateInfoExt& info)
{
  lock_type         lock (mtx_);
  list_events_type* plist = info.server_side_ ? &cmd_recv_msgs_ : &cmd_send_msgs_;

  if (plist->empty ())
  {
    return ::libs::events::IEvent::ptr ();
  }

  ::libs::events::IEvent::ptr ret = plist->back ();
  plist->pop_back ();
  return ret;
}


::libs::events::IEvent::ptr
LinkImplOneProcInt::send_msg (
  const CreateInfoExt&                      info,
  ::libs::events::IEvent::ptr               msg,
  const ::libs::link::details::CallSyncs&   sync,
  const ::libs::link::details::Calls&       req,
  const ::libs::events::ISeqEvent::id_type& id)
{
  TSyncStack sync_block;

  {
    lock_type         lock (mtx_);
    list_events_type* plist = info.server_side_ ? &cmd_send_msgs_ : &cmd_recv_msgs_;
    const auto        size  = plist->size ();

    if (size >= consts::warning_count_unsend_msg && 0 == size % consts::warning_count_unsend_msg)
    {
      U3_XLOG_WARN ("send_msg, list allmost full: " + to_string (info, msg, sync, req, id) + VTOLOG (size) + VTOLOG (info.server_side_) + PTR_TOLOG (plist));
    }
    if (size > consts::max_count_unsend_msg)
    {
#if 0
      //debug
      for (auto& dumpmsg : *plist)
      {
        U3_XLOG_WARN ("msg id=" + dumpmsg->get_mid ());
      }
#endif
      return ::libs::events::IEvent::ptr ();
    }

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

    if (::libs::link::details::CallSyncs::sync == sync)
    {
      msg = ::libs::events::helpers::wrap_sync_msg (msg);
    }

    if (!id.empty ())
    {
      msg = ::libs::events::helpers::wrap_seq_msg (msg, id);
    }

    plist->push_front (msg);

    if (plist->size () >= 1024 && 0 == plist->size () % 1024)
    {
      U3_XLOG_WARN ("push msg" + VTOLOG (plist->size ()) + VTOLOG (info.server_side_) + PTR_TOLOG (plist))
    }

    if (::libs::link::details::CallSyncs::async == sync)
    {
      return ::libs::events::IEvent::ptr ();
    }

    ::libs::events::IEvent::ptr base_msg = ::libs::events::helpers::get_base_msg (msg);
    U3_ASSERT (wait_sync_msgs_.end () == wait_sync_msgs_.find (base_msg));
    U3_ASSERT_NT (wait_sync_msgs_.size () < 256, "wait_sync_msgs_.size () < 256" + VTOLOG (wait_sync_msgs_.size ()));
    wait_sync_msgs_[base_msg] = &sync_block;
  }

  {
    std::unique_lock< TSyncStack::sync_type > intlock (sync_block.mtx_);
    if (sync_block.allready_complite_)
    {
      U3_XLOG_DEV ("LinkImplOneProcInt::send_msg: skip sync msg - allready compilte sync" + PTR_TOLOG (&sync_block));
    }
    else
    {
      auto wres = sync_block.evnt_.wait_for (intlock, std::chrono::milliseconds (60 * 1000));
      if (wres == std::cv_status::timeout)
      {
        U3_XLOG_ERROR ("LinkImplOneProcInt::send_msg: timeout wait sync msg sync" + PTR_TOLOG (&sync_block));
      }
    }
  }
  return sync_block.msg_in_progress_;
}


void
LinkImplOneProcInt::complite_msg (
  const CreateInfoExt&                   info,
  ::libs::events::IEvent::ptr            msg,
  const ::libs::link::StateProcessEvent& state)
{
  {
    lock_type                   lock (mtx_);
    ::libs::events::IEvent::ptr base_ret = ::libs::events::helpers::get_base_msg (msg);
    auto                        it_ret   = wait_sync_msgs_.find (base_ret);

    if (wait_sync_msgs_.end () != it_ret)
    {
      U3_XLOG_DBG ("LinkImplOneProcInt::complite_msg: prepeare send sync answer " << state.id_seq_.name () << " base=" << base_ret);
      TSyncStack::lock_type intlock (it_ret->second->mtx_);
      U3_XLOG_DBG ("LinkImplOneProcInt::complite_msg: begin send sync answer " << state.id_seq_.name () << " base=" << base_ret);
      it_ret->second->allready_complite_ = true;
      it_ret->second->msg_in_progress_   = base_ret;
      it_ret->second->evnt_.notify_all ();
      wait_sync_msgs_.erase (it_ret);
      U3_XLOG_DBG ("LinkImplOneProcInt::complite_msg: end send sync answer " << state.id_seq_.name () << " base=" << base_ret);
      return;
    }
  }

  U3_XLOG_DBG ("begin send answer " << state.id_seq_.name ());
  auto ret = send_msg (
    info,
    msg,
    ::libs::link::details::CallSyncs::async,
    ::libs::link::details::Calls::answer,
    state.id_seq_);
  U3_XLOG_DBG ("end send answer " << state.id_seq_.name ());
  U3_ASSERT (!ret);
}
}   // namespace libs::ilink::impl::oneproc
