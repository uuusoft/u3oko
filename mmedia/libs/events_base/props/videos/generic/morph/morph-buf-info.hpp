#pragma once
/**
\file       morph-buf-info.hpp
\date       10.09.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::morph
{
struct MorphBuffInfo final {
  //  ext types
  using morph_operations_type = std::vector< MorphOperationParams >;

  explicit MorphBuffInfo (
    syn::off_buf_type     sindx_diff = ::utils::dbufs::video::consts::offs::invalid,
    syn::off_buf_type     bindx_diff = ::utils::dbufs::video::consts::offs::invalid,
    morph_operations_type ops        = morph_operations_type ());

  virtual ~MorphBuffInfo () = default;

  syn::off_buf_type     sindx_diff_;         //<
  syn::off_buf_type     bindx_diff_;         //<
  morph_operations_type morph_operations_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void          tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const MorphBuffInfo& src);
MorphBuffInfo tag_invoke (::boost::json::value_to_tag< MorphBuffInfo >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::generic::morph

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::morph::MorphBuffInfo);