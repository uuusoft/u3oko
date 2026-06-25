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
bool
ILink::connect (const CreateInfo& info)
{
  return connect_int (info);
}


bool
ILink::listen (const CreateInfo& info)
{
  return listen_int (info);
}


bool
ILink::destroy (const LinkDestroys& type)
{
  return destroy_int (type);
}


bool
ILink::is_connected () const
{
  return is_connected_int ();
}


::libs::events::IEvent::ptr
ILink::received_msg ()
{
  return received_msg_int ();
}


::libs::events::IEvent::ptr
ILink::send_msg (
  const syn::IEvent::ptr&        msg,
  const details::CallSyncs&      sync,
  const details::Calls&          req,
  const syn::ISeqEvent::id_type& id)
{
  return send_msg_int (msg, sync, req, id);
}


void
ILink::complite_msg (const syn::IEvent::ptr& msg, const StateProcessEvent& state)
{
  complite_msg_int (msg, state);
}


mem::IMem::raw_ptr
ILink::get_imem ()
{
  return get_imem_int ();
}
}   // namespace libs::link
