//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       link-impl-one-proc-int.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes.hpp"
#include "link-impl-one-proc-int.hpp"

namespace libs { namespace ilink { namespace impl { namespace oneproc { namespace consts {

const std::size_t max_count_unsend_msg = 1 * 128;      //< пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ.

}}}}}      // namespace libs::ilink::impl::oneproc::consts

namespace libs { namespace ilink { namespace impl { namespace oneproc {

std::string
to_str (
  const CreateInfoExt&      _info,
  IEvent::ptr               _msg,
  const TypeSyncCall&       _sync,
  const TypeRequestCall&    _req,
  const ISeqEvent::id_type& _id)
{
  std::string _res = to_str (_info);
  _res += " " + to_str (_sync);
  _res += " " + to_str (_req);
  _res += (_id.empty () ? "" : (" sid=" + _id.name ()));
  if (::libs::events::helpers::get_base_msg (_msg)->get_mid () != _msg->get_mid ())
    {
      _res += " msgs=" + _msg->get_mid () + "+" + ::libs::events::helpers::get_base_msg (_msg)->get_mid ();
    }
  else
    {
      _res += " msg=" + _msg->get_mid ();
    }
  return _res;
}

LinkImplOneProcInt::LinkImplOneProcInt ()
{
  create_flag_.store (false);
  counter_ref_.store (0);
}


LinkImplOneProcInt::~LinkImplOneProcInt ()
{
  //CHECK_CALL_NO_THROW( destroy( true ) );
}


bool
LinkImplOneProcInt::connect (const CreateInfoExt& _info)
{
  UASSERT (!_info.id2val_[::libs::link::consts::text::id_name_queue2dest].empty ());
  UASSERT (!_info.id2val_[::libs::link::consts::text::id_name_shared_mem].empty ());

  ++counter_ref_;

  if (!_info.id2val_[::libs::link::consts::text::id_proc_name].empty ())
    {
      create_flag_.store (true);
      loader_.load (_info.run_as_, &_info, _info.id2val_[::libs::link::consts::text::id_proc_name], _info.id2val_[::libs::link::consts::text::id_lib_name], _info.args_);
      /*
      while ( create_flag_.load () )
      {
        std::this_thread::yield();
      }
      */
    }
  UASSERT (counter_ref_ <= 2);
  return loader_.is_load ();
}


bool
LinkImplOneProcInt::listen (const CreateInfoExt& _info)
{
  UASSERT (!_info.id2val_[::libs::link::consts::text::id_name_queue2dest].empty ());
  UASSERT (!_info.id2val_[::libs::link::consts::text::id_name_shared_mem].empty ());
  ++counter_ref_;
  create_flag_.store (false);
  UASSERT (counter_ref_ <= 2);
  return true;
}


bool
LinkImplOneProcInt::destroy (const CreateInfoExt& _info, const TypeDestroyLink& _type)
{
  const std::string _name_subsys = _info.id2val_[::libs::link::consts::text::id_subsys_name];
  const bool        _force       = TypeDestroyLink::force == _type;
  bool              _res_unload  = false;
  XULOG_INFO ("LinkImplOneProcInt::destroy: beg, " << _name_subsys);

  {
    guard_type _grd (mtx_);
    UASSERTM (counter_ref_ > 0, "count ref less or equal 0");
    --counter_ref_;
    if (counter_ref_ > 0 && !_force)
      {
        XULOG_INFO ("LinkImplOneProcInt::destroy: exist refs, skip unload, " << _name_subsys);
        return true;
      }
  }

  int _counter_unload = 0;
  do
    {
      XULOG_INFO ("LinkImplOneProcInt::destroy: unload dll, " << _counter_unload << ", " << _name_subsys);
      guard_type _grd (mtx_);
      _res_unload = loader_.unload (_force);
      if (_res_unload || !_force)
        {
          _info.id2val_.clear ();
        }
      ++_counter_unload;
    }
  while (!_res_unload && !_force);
  XULOG_INFO ("LinkImplOneProcInt::destroy: end, " << _name_subsys);
  return true;
}


bool
LinkImplOneProcInt::is_connected () const
{
  return counter_ref_ > 1 ? true : false;
}


IEvent::ptr
LinkImplOneProcInt::received_msg (const CreateInfoExt& _info)
{
  guard_type        _grd (mtx_);
  list_events_type* _plist = _info.server_side_ ? &cmd_recv_msgs_ : &cmd_send_msgs_;

  if (_plist->empty ())
    {
      return IEvent::ptr ();
    }

  IEvent::ptr _ret = _plist->back ();
  _plist->pop_back ();
  XULOG_TRACE ("received_msg, " << to_str (_info) << " size=" << _plist->size () << " list=0x" << std::hex << _plist);
  return _ret;
}


IEvent::ptr
LinkImplOneProcInt::send_msg (
  const CreateInfoExt&      _info,
  IEvent::ptr               _msg,
  const TypeSyncCall&       _sync,
  const TypeRequestCall&    _req,
  const ISeqEvent::id_type& _id)
{
  TSyncStack _sync_block;

  {
    guard_type        _grd (mtx_);
    list_events_type* _plist = _info.server_side_ ? &cmd_send_msgs_ : &cmd_recv_msgs_;
    const auto        _size  = _plist->size ();
    XULOG_TRACE ("send_msg " << to_str (_info, _msg, _sync, _req, _id) << " size=" << _size << " list=0x" << std::hex << _plist);
    if (_size > consts::max_count_unsend_msg)
      {
        XULOG_WARNING ("send_msg, failed: list full" << to_str (_info, _msg, _sync, _req, _id) << " size=" << _size << " list=0x" << std::hex << _plist);
        /*
        for (auto& _dumpmsg : *_plist)
          {
            XULOG_WARNING ("msg, " << _dumpmsg->get_mid ());
          }
          */
        return IEvent::ptr ();
      }

    if (TypeRequestCall::request == _req)
      {
        _msg = ::libs::events::helpers::wrap_request_msg (_msg);
      }
    if (TypeRequestCall::answer == _req)
      {
        _msg = ::libs::events::helpers::wrap_answer_msg (_msg);
      }
    if (TypeSyncCall::sync == _sync)
      {
        _msg = ::libs::events::helpers::wrap_sync_msg (_msg);
      }
    if (!_id.empty ())
      {
        _msg = ::libs::events::helpers::wrap_seq_msg (_msg, _id);
      }

    _plist->push_front (_msg);

    if (TypeSyncCall::async == _sync)
      {
        //пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
        return IEvent::ptr ();
      }

    IEvent::ptr _base_msg = ::libs::events::helpers::get_base_msg (_msg);
    UASSERT (wait_sync_msgs_.end () == wait_sync_msgs_.find (_base_msg));
    UASSERT (wait_sync_msgs_.size () < 100);
    wait_sync_msgs_[_base_msg] = &_sync_block;
  }
  //пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ. пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ complite_msg пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
  //пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ).
  {
    std::unique_lock<TSyncStack::sync_type> _intgrd (_sync_block.mtx_);
    _sync_block.evnt_.wait (_intgrd);
  }
#if 0
    //пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
    {
      guard_type  _intgrd (mtx_);
      IEvent::ptr _base_msg = ::libs::events::helpers::get_base_msg( _msg );
      UASSERT( wait_sync_msgs_.end() != wait_sync_msgs_.find( _base_msg ) );
      wait_sync_msgs_.erase( _base_msg );
    }
#endif
  return _sync_block.msg_;
}


void
LinkImplOneProcInt::complite_msg (
  const CreateInfoExt&     _info,
  IEvent::ptr              _msg,
  const StateProcessEvent& _state)
{
  XULOG_TRACE ("complite_msg, " << ::libs::events::helpers::get_base_msg (_msg)->get_mid ());
  {
    guard_type  _grd (mtx_);
    IEvent::ptr _base_ret = ::libs::events::helpers::get_base_msg (_msg);
    auto        _it_ret   = wait_sync_msgs_.find (_base_ret);

    //пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅ пїЅпїЅ, пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅ.
    if (wait_sync_msgs_.end () != _it_ret)
      {
        TSyncStack::guard_type _intgrd (_it_ret->second->mtx_);

        _it_ret->second->msg_ = _base_ret;
        _it_ret->second->evnt_.notify_all ();
        //пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
        wait_sync_msgs_.erase (_it_ret);
        //пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅ.пїЅ. пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
        //_ret.reset();
        return;
      }
  }

  auto _ret = send_msg (_info, _msg, TypeSyncCall::async, TypeRequestCall::answer, _state.id_seq_);
  UASSERT (!_ret);
  return;
}

}}}}      // namespace libs::ilink::impl::oneproc
