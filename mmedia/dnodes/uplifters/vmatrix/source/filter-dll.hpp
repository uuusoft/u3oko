#pragma once
/**
\brief      Filter for corrected image
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
U3_COMMERCIAL_PART
*/

namespace dnodes::uplifters::vmatrix
{
class Filter final :
  public ::libs::icore::impl::base::obj::dll::IFilter,
  protected ::libs::icore::impl::base::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ()          = default;
  virtual ~Filter () = default;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::icore::impl::base::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo&) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;

  auto init_pts (syn::ConnectInfo*) -> void;
  void load_images (InfoFilter* finfo);

  //  internal function
  auto itransform () -> void;
};
}   // namespace dnodes::uplifters::vmatrix
