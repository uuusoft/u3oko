//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       link-impl-one-proc.cpp
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
#include "link-impl-one-proc.hpp"

namespace libs { namespace ilink { namespace impl { namespace oneproc { namespace consts {

const std::size_t max_count_unsend_msg = 1 * 1024;      //<максимальное количество сообщений в очереди, ожидающих передачи.

}}}}}      // namespace libs::ilink::impl::oneproc::consts


namespace libs { namespace ilink { namespace impl { namespace oneproc {

LinkImplOneProc::LinkImplOneProc (LinkImplOneProcInt::weak_ptr& _helper) :
  phelper_ (_helper)
{
  UASSERT (_helper.lock ());
}


LinkImplOneProc::~LinkImplOneProc ()
{
  CHECK_CALL_NO_THROW (destroy_int (TypeDestroyLink::force));
}

#if 0
bool
LinkImplOneProc::close_int ()
{
  guard_type _grd (mtx_);
  auto       _phelper = get_shared_impl ();
  return _phelper->destroy (info_);
}
#endif

bool
LinkImplOneProc::is_connected_int () const
{
  guard_type _grd (mtx_);
  auto       _phelper = get_shared_impl ();
  return _phelper->is_connected ();
}


bool
LinkImplOneProc::connect_int (const CreateInfo& _info)
{
  guard_type _grd (mtx_);

  info_              = _info;
  info_.server_side_ = false;
  info_.run_as_      = TypeRunCode::dll;

  auto _phelper = get_shared_impl ();
  return _phelper->connect (info_);
}


bool
LinkImplOneProc::listen_int (const CreateInfo& _info)
{
  guard_type _grd (mtx_);

  info_              = _info;
  info_.server_side_ = true;
  info_.run_as_      = TypeRunCode::dll;

  auto _phelper = get_shared_impl ();
  return _phelper->listen (info_);
}


bool
LinkImplOneProc::destroy_int (const TypeDestroyLink& _type)
{
  guard_type _grd (mtx_);
  auto       _phelper = phelper_.lock ();

  if (!_phelper)
    {
      //UASSERT_SIGNAL( "failed" );
      return true;
    }
  return _phelper->destroy (info_, _type);
}


IEvent::ptr
LinkImplOneProc::received_msg_int ()
{
  guard_type _grd (mtx_);
  auto       _phelper = get_shared_impl ();
  return _phelper->received_msg (info_);
}


IEvent::ptr
LinkImplOneProc::send_msg_int (
  IEvent::ptr               _msg,
  const TypeSyncCall&       _sync,
  const TypeRequestCall&    _req,
  const ISeqEvent::id_type& _id)
{
  guard_type _grd (mtx_);
  auto       _phelper = get_shared_impl ();
  return _phelper->send_msg (info_, _msg, _sync, _req, _id);
}


void
LinkImplOneProc::complite_msg_int (IEvent::ptr _msg, const StateProcessEvent& _state)
{
  guard_type _grd (mtx_);
  auto       _phelper = get_shared_impl ();
  return _phelper->complite_msg (info_, _msg, _state);
}


::libs::link::mem::IMem::raw_ptr
LinkImplOneProc::get_imem_int ()
{
  return nullptr;
}


LinkImplOneProcInt::ptr
LinkImplOneProc::get_shared_impl () const
{
  auto _ret = phelper_.lock ();
  CHECK_STATE (_ret, "empty impl LinkImplOneProcInt");
  return _ret;
}

}}}}      // namespace libs::ilink::impl::oneproc
