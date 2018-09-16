#pragma once
/**
\file       filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace vcodec_gen {
/**
\brief  empty brief
*/
class Filter final : public ::libs::icore::impl::var1::obj::dll::IFilter,
                     protected ::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>
{
  public:
  Filter ();

  virtual ~Filter ();


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter overrides
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  void log_statistic ();

  void process_frame (TransformInfo& _info);

  bool prepare_process_frame (TransformInfo& _info);

  void process_events (TransformInfo& _info);

  void update_int ();

  void free_impl_lib ();

  void sync_props2int ();

  void flip_y (IVideoBuff::raw_ptr _buff);

  static browser::CodecBrower codec_browser_;       //< Для инфомации о доступных видеокодеках.
  static ForeverLoadDlls      freez_impls_;         //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы.
  bool                        external_codec_;      //< debug
  ::libs::optim::io::hioptim  flip_y_;              //< ???
  CallerImpl::ptr             pthreads_;            //< Пул рабочих потоков
};

}}}      // namespace dlls::codecs::vcodec_gen
