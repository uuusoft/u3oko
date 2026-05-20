#pragma once
/**
\file       base_id-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
\project    u3_base_id_dll
*/

namespace dlls::base_id
{
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual void load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (syn::TransformInfo& info) override;
  virtual void call_int (syn::CallInterfInfo& info) override;
  virtual void run_int () override;
  virtual void stop_int () override;

  // internals
  void init_pts (syn::ConnectInfo* info);

  BaseIdInterf::ptr base_interf_;        //<
  std::int64_t      counter_frames_;     //<
  bool              send_base_interf_;   //<
};
}   // namespace dlls::base_id
