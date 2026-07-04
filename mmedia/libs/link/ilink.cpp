/**
\file       ILink.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
*/
#include "libs-link-includes_int.hpp"
#include "ilink.hpp"

namespace libs::link
{
auto
ILink::connect (const CreateInfo& info) -> bool
{
  return connect_int (info);
}


auto
ILink::listen (const CreateInfo& info) -> bool
{
  return listen_int (info);
}


auto
ILink::destroy (const LinkDestroys& type) -> bool
{
  return destroy_int (type);
}


auto
ILink::is_connected () const -> bool
{
  return is_connected_int ();
}


auto
ILink::received_msg () -> ::libs::events::IEvent::ptr
{
  return received_msg_int ();
}


auto
ILink::send_msg (
  const syn::IEvent::ptr&        msg,
  const details::CallSyncs&      sync,
  const details::Calls&          req,
  const syn::ISeqEvent::id_type& id) -> ::libs::events::IEvent::ptr
{
  return send_msg_int (msg, sync, req, id);
}


void
ILink::complite_msg (const syn::IEvent::ptr& msg, const StateProcessEvent& state)
{
  complite_msg_int (msg, state);
}


auto
ILink::get_imem () -> mem::IMem::raw_ptr
{
  return get_imem_int ();
}
}   // namespace libs::link
