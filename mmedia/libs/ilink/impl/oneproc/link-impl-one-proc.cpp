/**
\file       link-impl-one-proc.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "link-impl-one-proc.hpp"

namespace libs::ilink::impl::oneproc
{
LinkImplOneProc::LinkImplOneProc (LinkImplOneProcInt::weak_ptr& helper) :
  phelper_ (helper)
{
  U3_ASSERT (helper.lock ());
}


LinkImplOneProc::~LinkImplOneProc ()
{
  U3_CHECK_NT (destroy_int (::libs::link::LinkDestroys::force), "LinkImplOneProc::~LinkImplOneProc");
}


bool
LinkImplOneProc::is_connected_int () const
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  return phelper->is_connected ();
}


bool
LinkImplOneProc::connect_int (const ::libs::link::CreateInfo& info)
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);

    info_              = info;
    info_.server_side_ = false;
    info_.run_as_      = ::libs::link::details::CodeRuns::dll;
    phelper            = get_shared_impl ();
  }
  return phelper->connect (info_);
}


bool
LinkImplOneProc::listen_int (const ::libs::link::CreateInfo& info)
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);

    info_              = info;
    info_.server_side_ = true;
    info_.run_as_      = ::libs::link::details::CodeRuns::dll;
    phelper            = get_shared_impl ();
  }
  return phelper->listen (info_);
}


bool
LinkImplOneProc::destroy_int (const ::libs::link::LinkDestroys& type)
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  if (!phelper)
  {
    U3_XLOG_DEV ("LinkImplOneProc::destroy_int: allready destroy");
    return true;
  }
  return phelper->destroy (info_, type);
}


::libs::events::IEvent::ptr
LinkImplOneProc::received_msg_int ()
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  return phelper->received_msg (info_);
}


::libs::events::IEvent::ptr
LinkImplOneProc::send_msg_int (
  const ::libs::events::IEvent::ptr&        msg,
  const ::libs::link::details::CallSyncs&   sync,
  const ::libs::link::details::Calls&       req,
  const ::libs::events::ISeqEvent::id_type& id)
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  return phelper->send_msg (info_, msg, sync, req, id);
}


void
LinkImplOneProc::complite_msg_int (
  const ::libs::events::IEvent::ptr&     msg,
  const ::libs::link::StateProcessEvent& state)
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  phelper->complite_msg (info_, msg, state);
}


::libs::link::mem::IMem::raw_ptr
LinkImplOneProc::get_imem_int ()
{
  return nullptr;
}


LinkImplOneProcInt::ptr
LinkImplOneProc::get_shared_impl () const
{
  auto ret = phelper_.lock ();
  U3_CHECK (ret, "empty impl LinkImplOneProcInt");
  return ret;
}
}   // namespace libs::ilink::impl::oneproc
