/**
\file       cuuid.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"
#include "cuuid.hpp"

namespace libs::utility::utils
{
cuuid::cuuid (const cuuid& left) :
  cuuid (left.get_raw_uuid_vals ())
{
}


cuuid::cuuid (const ::boost::uuids::uuid& base) :
  id_ (base)
{
}


cuuid::cuuid (const data_type val_array)
{
  std::copy (val_array, val_array + 16, id_.begin ());
  U3_ASSERT (!id_.is_nil () || 0 == val_array[0]);
}


cuuid::cuuid (const std::initializer_list< value_type > val_array)
{
  U3_ASSERT (16 == val_array.size ());
  std::ranges::copy (val_array, id_.begin ());
  U3_ASSERT (!id_.is_nil () || 0 == *val_array.begin ());
}

#ifdef U3_OS_WIN32_DESKTOP
cuuid::cuuid (const GUID& guid)
{
  std::copy (
    ::libs::utility::casts::reinterpret_cast_helper< const std::uint8_t* > (&guid),
    ::libs::utility::casts::reinterpret_cast_helper< const std::uint8_t* > (&guid) + sizeof (GUID),
    id_.begin ());
}


const GUID*
cuuid::get_guid () const
{
  return ::libs::utility::casts::reinterpret_cast_helper< const GUID* > (&id_.data[0]);
}
#endif

auto
cuuid::operator= (const boost::uuids::uuid& left) -> cuuid&
{
  id_ = left;
  return *this;
}


auto
cuuid::operator= (const cuuid& left) -> cuuid&
{
  if (this != &left)
  {
    id_ = left.id_;
  }
  return *this;
}


auto
cuuid::get_raw_uuid_vals () const -> const boost::uuids::uuid&
{
  return id_;
}


void
cuuid::reset ()
{
  id_ = boost::uuids::nil_uuid ();
}


auto
cuuid::empty () const -> bool
{
  return id_.is_nil ();
}


auto
operator< (const cuuid& lph, const cuuid& rph) -> bool
{
  return lph.get_raw_uuid_vals () < rph.get_raw_uuid_vals ();
}


auto
operator== (const cuuid& lph, const cuuid& rph) -> bool
{
  return lph.get_raw_uuid_vals () == rph.get_raw_uuid_vals ();
}


auto
operator!= (const cuuid& lph, const cuuid& rph) -> bool
{
  return lph == rph ? false : true;
}


template< class Archive >
void
cuuid::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (id_);
}


auto
to_string (const cuuid& val) -> std::string
{
  return boost::uuids::to_string (val.get_raw_uuid_vals ());
  //  return ::boost::lexical_cast< std::string > (val.get_raw_uuid_vals ());
}


auto
cuuid_from_string (const std::string& src) -> cuuid
{
  return cuuid (::boost::lexical_cast< boost::uuids::uuid > (src));
}

void
cuuid_to_buf (const cuuid& val, std::uint8_t buf[16])
{
  std::copy (val.get_raw_uuid_vals ().begin (),
             val.get_raw_uuid_vals ().end (),
             buf);
}
}   // namespace libs::utility::utils

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::utility::utils::cuuid);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::utility::utils::cuuid);
