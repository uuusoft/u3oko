#pragma once
/**
\file       gen-vgen-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen
{
class Filter;
/// Структура для группировки свойств фильтра захвата данных из источника (ipcam/webcam/ect).
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  using sync_type = std::timed_mutex;

  friend class dlls::sources::gen_vgen::Filter;

  InfoFilter ();
  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& src)            = delete;
  InfoFilter& operator= (const InfoFilter& src) = delete;

  private:
  // internal types
  using list_keys2bufs_type = std::list< ::dlls::sources::gen_lib::syn::pkeys2bufs_type >;
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::BaseInfoFilter)
  //  BaseInfoFilter overrides
  virtual bool load_int (const ::pugi::xml_named_node_iterator& node) override;
  virtual void sync_int (bool force) override;

  syn::VideoDriverProp::raw_ptr          rprops_;           //< Настроенный указатель на свойства (для удобства)
  syn::VideoDriverCaptureProp::raw_ptr   capture_props_;    //< Загружаемые из xml файла свойства захвата
  syn::LinksVideoDriverProp              links_props_;      //< Cвойства различных интерфейсов
  syn::SystemSpecificDriverProp::raw_ptr system_props_;     //< Свойства источника, зависимые от ОС
  ObjSourceImplProxy                     proxy2hardware_;   //< Реализация интерфейса для захвата с устройства
  ::libs::helpers::fps::FpsController    capture_fps_;      //< Поле для контроля частоты захвата
  syn::IVideoBuf::ptr                    buf_;              //< Текущий буфер
  std::unique_ptr< std::thread >         recv_thread_;      //< Поток захвата данных из устройства
  sync_type                              wdmtx_;            //< Синхр. примитив для организации доступа к полям объекта между потоком захвата и рабочим потоком
  bool                                   stop_req_;         //< Флаг-требование, остановить захват кадров
  list_keys2bufs_type                    impl_frames_;      //< Список готовых буферов
  ICaptureImageNullImpl::ptr             null_impl_;        //<
  syn::ICaptureImage::weak_ptr           capture_impl_;     //< Реализация захвата изображения, полученная от нижелижащего драйвера. Опционально
  bool                                   synced_;           //< Флаг требования синхронизации
};
}   // namespace dlls::sources::gen_vgen
