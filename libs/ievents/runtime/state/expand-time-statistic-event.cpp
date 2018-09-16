//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       expand-time-statistic-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "expand-time-statistic-event.hpp"


namespace libs { namespace ievents { namespace runtime { namespace state {

ExpandTimeStatisticEvent::ExpandTimeStatisticEvent (const Acessor& _ph, const ExpandedTimeStatistic::infos_type& _infos, const TypeStatisticSource& _source) :
  action_ (TypeStatisticAction::get),
  source_ (_source),
  infos_ (_infos)
{
  property_name_ = gen_get_mid ();
}


ExpandTimeStatisticEvent::~ExpandTimeStatisticEvent ()
{}


const ExpandedTimeStatistic::infos_type&
ExpandTimeStatisticEvent::get_stat () const
{
  return infos_;
}


void
ExpandTimeStatisticEvent::set_stat (const ExpandedTimeStatistic::infos_type& _infos)
{
  infos_ = _infos;
  return;
}


const TypeStatisticSource&
ExpandTimeStatisticEvent::get_source () const
{
  return source_;
}


void
ExpandTimeStatisticEvent::set_source (const TypeStatisticSource& _source)
{
  source_ = _source;
  return;
}


const TypeStatisticAction&
ExpandTimeStatisticEvent::get_action () const
{
  return action_;
}


void
ExpandTimeStatisticEvent::set_action (const TypeStatisticAction& _action)
{
  action_ = _action;
  return;
}


::libs::events::IEvent::ptr
ExpandTimeStatisticEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<ExpandTimeStatisticEvent> (this, _deep);
}


void
ExpandTimeStatisticEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ExpandTimeStatisticEvent);
  super::copy_int (_src);
  action_ = _dsrc->action_;
  source_ = _dsrc->source_;
  infos_  = _dsrc->infos_;
  return;
}


template <class Archive>
void
ExpandTimeStatisticEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (action_);
  ar& BOOST_SERIALIZATION_NVP (source_);
  ar& BOOST_SERIALIZATION_NVP (infos_);
  return;
}

}}}}      // namespace libs::ievents::runtime::state

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::state::ExpandTimeStatisticEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::runtime::state::ExpandTimeStatisticEvent);
