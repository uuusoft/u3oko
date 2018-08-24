//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ILink.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "ilink.hpp"

namespace libs { namespace link {

ILink::ILink ()
{}


ILink::~ILink ()
{}


bool
ILink::connect (const CreateInfo& _info)
{
  return connect_int (_info);
}


bool
ILink::listen (const CreateInfo& _info)
{
  return listen_int (_info);
}


bool
ILink::destroy (const TypeDestroyLink& _type)
{
  return destroy_int (_type);
}


bool
ILink::is_connected () const
{
  return is_connected_int ();
}


IEvent::ptr
ILink::received_msg ()
{
  return received_msg_int ();
}

IEvent::ptr
ILink::send_msg (
  IEvent::ptr                     _msg,
  const details::TypeSyncCall&    _sync,
  const details::TypeRequestCall& _req,
  const ISeqEvent::id_type&       _id)
{
  return send_msg_int (_msg, _sync, _req, _id);
}


void
ILink::complite_msg (IEvent::ptr _msg, const StateProcessEvent& _state)
{
  return complite_msg_int (_msg, _state);
}


mem::IMem::raw_ptr
ILink::get_imem ()
{
  return get_imem_int ();
}

}}      // namespace libs::link
