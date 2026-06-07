#pragma once
/**
\brief      Filter for corrected image
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info) override;
  virtual void call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info) override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);
  void itransform ();
  void alloc_bufs ();
  void alloc_temp_bufs ();
  void convert_bufs ();

  ::libs::optim::io::hioptim*          get_func_for_format (const ::libs::helpers::uids::minor::id_val& format);
  ::libs::helpers::uids::minor::id_val get_out_format_from_format (const ::libs::helpers::uids::minor::id_val& format);
  bool                                 is_result_mono (const ::libs::helpers::uids::minor::id_val& format) const;

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
