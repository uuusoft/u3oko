/**
\file       path-info.cpp
\date       18.05.2022
\author     Erashov Anton erashov2026@proton.me
*/
#include "../../../events-base-includes_int.hpp"
#include "path-info.hpp"

namespace libs::events_base::props::modules::storage
{
auto
PathInfo::check () const -> bool
{
  return path2data_.empty () || 0 == max_data_size_ ? false : true;
}

#if (U3_USE_BOOST_SERIALIZTION)
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
#endif

void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const PathInfo& src)
{
  ::libs::utility::checks::assert_soft (0, "???");
}


auto
tag_invoke (::boost::json::value_to_tag< PathInfo >, const ::boost::json::value& jvs) -> PathInfo
{
  ::libs::utility::checks::assert_soft (0, "???");
  return {};
}
}   // namespace libs::events_base::props::modules::storage

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::modules::storage::PathInfo);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::modules::storage::PathInfo);
