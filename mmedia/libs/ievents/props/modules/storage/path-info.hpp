#pragma once
/**
\file       path-info.hpp
\date       22.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::modules::storage::consts
{
constexpr const char* default_imp_name = "default";
}

namespace libs::ievents::props::modules::storage
{
struct PathInfo final {
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (PathInfo)

  PathInfo ();
  virtual ~PathInfo ();

  bool check () const;

  std::string  path2data_         = ".";                        //<
  std::string  impl_storage_name_ = consts::default_imp_name;   //<
  std::string  impl_indexer_name_ = consts::default_imp_name;   //<
  PathUsings   state_             = PathUsings::disabled;       //<
  std::int64_t max_data_size_     = 0;                          //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};

void     tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const PathInfo& src);
PathInfo tag_invoke (::boost::json::value_to_tag< PathInfo >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::modules::storage

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::modules::storage::PathInfo);
