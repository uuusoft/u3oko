/**
\file       link-impl-one-proc.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_ilink
*/
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


auto
LinkImplOneProc::is_connected_int () const -> bool
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  return phelper->is_connected ();
}


auto
LinkImplOneProc::connect_int (const ::libs::link::CreateInfo& info) -> bool
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


auto
LinkImplOneProc::listen_int (const ::libs::link::CreateInfo& info) -> bool
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


auto
LinkImplOneProc::destroy_int (const ::libs::link::LinkDestroys& type) -> bool
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  if (!phelper)
  {
    U3_XLOG_DBG ("LinkImplOneProc::destroy_int: allready destroy");
    return true;
  }
  return phelper->destroy (info_, type);
}


auto
LinkImplOneProc::received_msg_int () -> syn::IEvent::ptr
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  return phelper->received_msg (info_);
}


auto
LinkImplOneProc::send_msg_int (
  const syn::IEvent::ptr&                   msg,
  const syn::CallSyncs&                     sync,
  const syn::Calls&                         req,
  const ::libs::events::ISeqEvent::id_type& id) -> syn::IEvent::ptr
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  return phelper->send_msg (info_, msg, sync, req, id);
}


void
LinkImplOneProc::complite_msg_int (const syn::IEvent::ptr& msg, const ::libs::link::StateProcessEvent& state)
{
  LinkImplOneProcInt::ptr phelper;
  {
    lock_type lock (mtx_);
    phelper = get_shared_impl ();
  }
  phelper->complite_msg (info_, msg, state);
}


auto
LinkImplOneProc::get_imem_int () -> syn::IMem::raw_ptr
{
  return nullptr;
}


auto
LinkImplOneProc::get_shared_impl () const -> LinkImplOneProcInt::ptr
{
  auto ret = phelper_.lock ();
  U3_CHECK (ret, "empty impl LinkImplOneProcInt");
  return ret;
}
}   // namespace libs::ilink::impl::oneproc
