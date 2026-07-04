#pragma once
/**
\file       path-info.hpp
\date       22.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::modules::storage::consts
{
inline constexpr const char* default_imp_name = "default";
}

namespace libs::events_base::props::modules::storage
{
struct PathInfo final {
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (PathInfo)

  PathInfo ()          = default;
  virtual ~PathInfo () = default;

  bool check () const;

  std::string  path2data_         = ".";                        //<
  std::string  impl_storage_name_ = consts::default_imp_name;   //<
  std::string  impl_indexer_name_ = consts::default_imp_name;   //<
  PathUsings   state_             = PathUsings::disabled;       //<
  std::int64_t max_data_size_     = 0;                          //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void     tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const PathInfo& src);
PathInfo tag_invoke (::boost::json::value_to_tag< PathInfo >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::modules::storage

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::modules::storage::PathInfo);
