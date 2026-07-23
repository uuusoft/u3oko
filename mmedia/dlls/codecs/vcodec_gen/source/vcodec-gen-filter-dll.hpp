#pragma once
/**
\file       vcodec-gen-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vcodec_gen
*/

namespace dlls::codecs::vcodec_gen
{
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter ();

  protected:
  virtual void sync_by_events (bool update) override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo&) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;

  // internals
  auto init_pts (syn::ConnectInfo*) -> void;
  auto log_statistic () -> void;
  auto process_frame (syn::TransformInfo&) -> void;
  auto prepare_process_frame (syn::TransformInfo&) -> bool;
  auto process_events (syn::TransformInfo&) -> void;
  auto update_int () -> void;
  auto free_impl_lib () noexcept -> void;
  auto sync_props2int () -> void;
  auto flip_y (syn::IVideoBuf::raw_ptr) -> void;

  static browser::CodecBrowser              codec_browser_;   //< Для инфомации о доступных видеокодеках
  static ::libs::utility::dlls::FreezerDlls frozen_dlls_;     //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы

  syn::IMCaller::ptr         mtcaller_;                                      //<
  ::libs::optim::io::hioptim flip_y_;                                        //<
  bool                       external_codec_ { false };                      //<
  std::string                active_dll_name_ { "u3-dll-name-undefined" };   //< U3-REFACT
};
}   // namespace dlls::codecs::vcodec_gen
