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

/// Структура для группировки свойств фильтра захвата данных из источника (ipcam/webcam/ect)
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  using sync_type = std::timed_mutex;

  friend class dlls::sources::gen_vgen::Filter;

  InfoFilter ();
  virtual ~InfoFilter ();

  private:
  // internal types
  using list_keys2bufs_type = std::list< ::dlls::sources::gen_lib::syn::pkeys2bufs_type >;

  U3_ADD_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::BaseInfoFilter)

  //  BaseInfoFilter overrides
  virtual auto load_int (const ::pugi::xml_named_node_iterator&) -> bool override;
  virtual auto sync_int (bool force) -> void override;

  syn::VideoDriverProp::raw_ptr          rprops_        = nullptr;                                       //< Настроенный указатель на свойства (для удобства)
  syn::VideoDriverCaptureProp::raw_ptr   capture_props_ = nullptr;                                       //< Загружаемые из xml файла свойства захвата
  syn::SystemSpecificDriverProp::raw_ptr system_props_  = nullptr;                                       //< Свойства источника, зависимые от ОС
  syn::LinksVideoDriverProp              links_props_;                                                   //< Cвойства различных интерфейсов
  ObjSourceImplProxy                     proxy2hardware_;                                                //< Реализация интерфейса для захвата с устройства
  ::libs::utility::fps::FpsController    capture_fps_;                                                   //< Поле для контроля частоты захвата
  syn::IVideoBuf::ptr                    buf_;                                                           //< Текущий буфер
  std::unique_ptr< std::thread >         recv_thread_;                                                   //< Поток захвата данных из устройства
  sync_type                              wdmtx_;                                                         //< Синхр. примитив для организации доступа к полям объекта между потоком захвата и рабочим потоком
  list_keys2bufs_type                    impl_frames_;                                                   //< Список готовых буферов
  bool                                   stop_req_     = false;                                          //< Флаг-требование, остановить захват кадров
  ICaptureImageNullImpl::ptr             null_impl_    = std::make_shared< ICaptureImageNullImpl > ();   //<
  syn::ICaptureImage::weak_ptr           capture_impl_ = null_impl_;                                     //< Реализация захвата изображения, полученная от нижелижащего драйвера. Опционально
  bool                                   synced_       = false;                                          //< Флаг требования синхронизации
};
}   // namespace dlls::sources::gen_vgen
