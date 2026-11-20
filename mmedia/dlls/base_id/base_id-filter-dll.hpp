#pragma once
/**
\file       base_id-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
*/

namespace dlls::base_id
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
  virtual auto run_int () -> void override;
  virtual auto stop_int () -> void override;

  // internals
  void init_pts (syn::ConnectInfo* info);

  BaseIdInterf::ptr base_interf_ { std::make_shared< BaseIdInterf > () };   //<
  std::int64_t      frame_counter_ { 0 };                                   //<
  bool              send_base_interf_ { false };                            //<
};
}   // namespace dlls::base_id
