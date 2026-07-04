/**
\file       buf2module-info.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.03.2022
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "buf2module-info.hpp"

namespace libs::events_base::props::base_id
{
Buff2ModuleInfo::Buff2ModuleInfo (
  float             fps,
  syn::off_buf_type indx_buf,
  id_link_type      dest_module_id) :
  fps_ (fps),
  indx_buf_ (std::move (indx_buf)),
  dest_module_id_ (std::move (dest_module_id))
{
}


template< class Archive >
void
Buff2ModuleInfo::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (fps_);
  arh& BOOST_SERIALIZATION_NVP (indx_buf_);
  arh& BOOST_SERIALIZATION_NVP (dest_module_id_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Buff2ModuleInfo& src)
{
  jvs = {
    { "fps", src.fps_ },
    { "indx_buf", src.indx_buf_ },
    { "dest_module_id", src.dest_module_id_ }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< Buff2ModuleInfo >, const ::boost::json::value& jvs) -> Buff2ModuleInfo
{
  Buff2ModuleInfo              ret;
  const ::boost::json::object& obj = jvs.as_object ();
  ::libs::utility::json::extract (obj, ret.fps_, "fps");
  ::libs::utility::json::extract (obj, ret.indx_buf_, "indx_buf");
  ::libs::utility::json::extract (obj, ret.dest_module_id_, "dest_module_id");
  return ret;
}
}   // namespace libs::events_base::props::base_id

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::base_id::Buff2ModuleInfo);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::base_id::Buff2ModuleInfo);
