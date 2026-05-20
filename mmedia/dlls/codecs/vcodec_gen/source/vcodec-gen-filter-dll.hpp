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
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (syn::TransformInfo& info) override;
  virtual void call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info) override;

  // internals
  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);
  void log_statistic ();
  void process_frame (syn::TransformInfo& info);
  bool prepare_process_frame (syn::TransformInfo& info);
  void process_events (syn::TransformInfo& info);
  void update_int ();
  void free_impl_lib ();
  void sync_props2int ();
  void flip_y (syn::IVideoBuf::raw_ptr buf);

  static browser::CodecBrower                   codec_browser_;            //< Для инфомации о доступных видеокодеках
  static ::libs::helpers::dlls::ForeverLoadDlls frozen_dlls_;              //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы
  bool                                          external_codec_ = false;   //<
  ::libs::optim::io::hioptim                    flip_y_;                   //<
  ::libs::optim::mcalls::IMCaller::ptr          pthreads_;                 //< Пул рабочих потоков
  std::string                                   active_dll_name_;          //< U3-REFACT
};
}   // namespace dlls::codecs::vcodec_gen
