//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       frame-done.cpp
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "frame-done.hpp"

namespace libs { namespace ievents { namespace runtime { namespace video {

FrameDone::FrameDone (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


FrameDone::~FrameDone ()
{}


::libs::events::IEvent::ptr
FrameDone::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<FrameDone> (this, _deep);
}


void
FrameDone::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (FrameDone);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
FrameDone::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}}      // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::video::FrameDone);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::runtime::video::FrameDone);
