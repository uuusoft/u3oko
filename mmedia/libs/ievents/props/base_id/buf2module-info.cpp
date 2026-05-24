/**
\file       buf2module-info.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.03.2022
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "buf2module-info.hpp"

namespace libs::ievents::props::base_id
{
Buff2ModuleInfo::Buff2ModuleInfo (
  float                                                    fps,
  const ::utils::dbufs::video::consts::offs::off_buf_type& indx_buf,
  const id_link_type&                                      dest_module_id) :
  fps_ (fps),
  indx_buf_ (indx_buf),
  dest_module_id_ (dest_module_id)
{
}


Buff2ModuleInfo::~Buff2ModuleInfo ()
{
}


template< class Archive >
void
Buff2ModuleInfo::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (fps_);
  ar& BOOST_SERIALIZATION_NVP (indx_buf_);
  ar& BOOST_SERIALIZATION_NVP (dest_module_id_);
}


void
tag_invoke (
  ::boost::json::value_from_tag,
  ::boost::json::value&  jv,
  const Buff2ModuleInfo& src)
{
  jv = {
    { "fps", src.fps_ },
    { "indx_buf", src.indx_buf_ },
    { "dest_module_id", src.dest_module_id_ }
  };
}


Buff2ModuleInfo
tag_invoke (::boost::json::value_to_tag< Buff2ModuleInfo >, const ::boost::json::value& jv)
{
  Buff2ModuleInfo              ret;
  const ::boost::json::object& obj = jv.as_object ();
  ::libs::helpers::json::extract (obj, ret.fps_, "fps");
  ::libs::helpers::json::extract (obj, ret.indx_buf_, "indx_buf");
  ::libs::helpers::json::extract (obj, ret.dest_module_id_, "dest_module_id");
  return ret;
}
}   // namespace libs::ievents::props::base_id

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::base_id::Buff2ModuleInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::base_id::Buff2ModuleInfo);
