//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       detect-violation.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "detect-violation.hpp"

namespace libs { namespace ievents { namespace runtime { namespace video {

DetectViolation::DetectViolation (const Acessor& _ph, const StateDetectViolation& _state) :
  state_ (_state)
{
  property_name_ = gen_get_mid ();
}


DetectViolation::~DetectViolation ()
{}


void
DetectViolation::set_state (const StateDetectViolation& _state)
{
  state_ = _state;
  return;
}


StateDetectViolation
DetectViolation::get_state () const
{
  return state_;
}


::libs::events::IEvent::ptr
DetectViolation::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<DetectViolation> (this, _deep);
}


void
DetectViolation::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (DetectViolation);
  super::copy_int (_src);
  state_ = _dsrc->state_;
  return;
}


template <class Archive>
void
DetectViolation::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (state_);
  return;
}

}}}}      // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::video::DetectViolation);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::runtime::video::DetectViolation);
