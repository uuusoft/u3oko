//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       cuuid.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "cuuid.hpp"
#include "mmedia/libs/events/serialize_type_to_archive_define.hpp"

namespace libs { namespace helpers { namespace utils {

cuuid::cuuid () :
  id_ (boost::uuids::nil_uuid ())
{}


cuuid::cuuid (const boost::uuids::uuid& _base) :
  id_ (_base)
{}


cuuid::cuuid (const value_type val_array[16])
{
  std::copy (val_array, val_array + 16, id_.begin ());
  UASSERT (!id_.is_nil () || 0 == val_array[0]);
  return;
}


cuuid&
cuuid::operator= (const boost::uuids::uuid& _left)
{
  id_ = _left;
  return *this;
}


cuuid&
cuuid::operator= (const cuuid& _left)
{
  if (this != &_left)
    {
      id_ = _left.id_;
    }
  return *this;
}


const boost::uuids::uuid&
cuuid::get_vals () const
{
  return id_;
}


void
cuuid::reset ()
{
  id_ = boost::uuids::nil_uuid ();
  return;
}


std::string
cuuid::name () const
{
  std::stringstream _stemp;
  _stemp << "0x";
  for (auto _val : id_)
    {
      _stemp << std::hex << static_cast<unsigned int> (_val);
    }
  return _stemp.str ();
}


bool
cuuid::empty () const
{
  return id_.is_nil ();
}


bool
operator< (const cuuid& _l, const cuuid& _r)
{
  return _l.get_vals () < _r.get_vals ();
}


bool
operator== (const cuuid& _l, const cuuid& _r)
{
  return _l.get_vals () == _r.get_vals ();
}


bool
operator!= (const cuuid& _l, const cuuid& _r)
{
  return _l == _r ? false : true;
}


template <class Archive>
void
cuuid::serialize (Archive& ar, const unsigned int /* file_version */)
{
  //ar & id_;
  return;
}

}}}      // namespace libs::helpers::utils

//BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::helpers::utils::cuuid );
SERIALIZE_TYPE_TO_ARCHIVES (::libs::helpers::utils::cuuid);
