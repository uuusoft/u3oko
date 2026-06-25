#pragma once
/**
\brief      Filter for corrected image
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_all2rgb
*/

namespace dlls::convertors::all2rgb
{
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ()          = default;
  virtual ~Filter () = default;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo& info) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;

  auto init_pts (syn::ConnectInfo*) -> void;
  auto itransform () -> void;
  auto alloc_temp_bufs () -> void;
  auto convert_bufs () -> void;

  auto get_func_for_format (const ::libs::helpers::uids::minor::id_val& format) -> ::libs::optim::io::hioptim*;
  auto get_out_format_from_format (const ::libs::helpers::uids::minor::id_val& format) -> ::libs::helpers::uids::minor::id_val;
  auto is_result_mono (const ::libs::helpers::uids::minor::id_val& format) const -> bool;

  ::libs::optim::io::hioptim rgb32_to_rgb24_;   //<
  ::libs::optim::io::hioptim yuy2_to_rgb24_;    //<
  ::libs::optim::io::hioptim yuy2_to_y16_;      //<
  ::libs::optim::io::hioptim uyvy_to_rgb24_;    //<
  ::libs::optim::io::hioptim uyvy_to_y16_;      //<
  ::libs::optim::io::hioptim nv21_to_rgb24_;    //<
  ::libs::optim::io::hioptim nv21_to_y16_;      //<
  ::libs::optim::io::hioptim ycb_to_rgb24_;     //<
  ::libs::optim::io::hioptim i420_to_rgb24_;    //<
  ::libs::optim::io::hioptim scale_func_;       //<
};
}   // namespace dlls::convertors::all2rgb
