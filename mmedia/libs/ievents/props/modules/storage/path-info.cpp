/**
\file       path-info.cpp
\date       18.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../includes_int.hpp"
#include "path-info.hpp"

namespace libs::ievents::props::modules::storage
{
bool
PathInfo::check () const
{
  return path2data_.empty () || 0 == max_data_size_ ? false : true;
}


template< class Archive >
void
PathInfo::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (path2data_);
  arh& BOOST_SERIALIZATION_NVP (impl_storage_name_);
  arh& BOOST_SERIALIZATION_NVP (impl_indexer_name_);
  arh& BOOST_SERIALIZATION_NVP (state_);
  arh& BOOST_SERIALIZATION_NVP (max_data_size_);
}

void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const PathInfo& src)
{
  U3_ASSERT_NT (0, "???");
}


PathInfo
tag_invoke (::boost::json::value_to_tag< PathInfo >, const ::boost::json::value& jvs)
{
  U3_ASSERT_NT (0, "???");
  return PathInfo ();
}
}   // namespace libs::ievents::props::modules::storage

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::modules::storage::PathInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::modules::storage::PathInfo);
