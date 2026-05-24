/**
\file       cuuid.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "cuuid.hpp"

namespace libs::helpers::utils
{
cuuid::cuuid () :
  id_ (boost::uuids::nil_uuid ())
{
}


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
  std::copy (val_array.begin (), val_array.end (), id_.begin ());
  U3_ASSERT (!id_.is_nil () || 0 == *val_array.begin ());
}

#if defined(U3_OS_WIN32_DESKTOP)
cuuid::cuuid (const GUID& guid)
{
  std::copy (
    U3_CAST_REINTERPRET< const std::uint8_t* > (&guid),
    U3_CAST_REINTERPRET< const std::uint8_t* > (&guid) + sizeof (GUID),
    id_.begin ());
}


const GUID*
cuuid::get_guid () const
{
  return U3_CAST_REINTERPRET< const GUID* > (&id_.data[0]);
}
#endif

cuuid::~cuuid ()
{
}


cuuid&
cuuid::operator= (const boost::uuids::uuid& left)
{
  id_ = left;
  return *this;
}


cuuid&
cuuid::operator= (const cuuid& left)
{
  if (this != &left)
  {
    id_ = left.id_;
  }
  return *this;
}


const boost::uuids::uuid&
cuuid::get_raw_uuid_vals () const
{
  return id_;
}


void
cuuid::reset ()
{
  id_ = boost::uuids::nil_uuid ();
}


bool
cuuid::empty () const
{
  return id_.is_nil ();
}


bool
operator< (const cuuid& l, const cuuid& r)
{
  return l.get_raw_uuid_vals () < r.get_raw_uuid_vals ();
}


bool
operator== (const cuuid& l, const cuuid& r)
{
  return l.get_raw_uuid_vals () == r.get_raw_uuid_vals ();
}


bool
operator!= (const cuuid& l, const cuuid& r)
{
  return l == r ? false : true;
}


template< class Archive >
void
cuuid::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (id_);
}


std::string
to_string (const cuuid& val)
{
  return ::boost::lexical_cast< std::string > (val.get_raw_uuid_vals ());
}


cuuid
cuuid_from_string (const std::string& src)
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
}   // namespace libs::helpers::utils

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::helpers::utils::cuuid);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::helpers::utils::cuuid);
