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
  void log_statistic ();
  void process_frame (syn::TransformInfo& info);
  bool prepare_process_frame (syn::TransformInfo& info);
  void process_events (syn::TransformInfo& info);
  void update_int ();
  void free_impl_lib () noexcept;
  void sync_props2int ();
  void flip_y (syn::IVideoBuf::raw_ptr buf);

  static browser::CodecBrower               codec_browser_;   //< Для инфомации о доступных видеокодеках
  static ::libs::utility::dlls::FreezerDlls frozen_dlls_;     //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы

  bool                       external_codec_ = false;   //<
  ::libs::optim::io::hioptim flip_y_;                   //<
  syn::IMCaller::ptr         pthreads_;                 //< Пул рабочих потоков
  std::string                active_dll_name_;          //< U3-REFACT
};
}   // namespace dlls::codecs::vcodec_gen
