#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      empty brief
*/

namespace dlls { namespace sources { namespace gen_vgen {
/**
\brief  Структура для группировки свойств фильтра захвата данных из источника (ipcam/webcam/ect).
*/
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  using props_type = gen_lib::VideoDriverProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  void init ();

  ::libs::events::IEvent::ptr     props_;              //< Загружаемые из xml файла общие свойства.
  props_type::raw_ptr             rprops_;             //< Настроенный указатель на свойства (для удобства).
  gen_lib::VideoDriverCaptureProp capture_props_;      //< Загружаемые из xml файла свойства захвата.
  gen_lib::LinksVideoDriverProp   links_props_;        //< Cвойства различных интерфейсов.
  ObjSourceImplProxy              rdriver_;            //< Реализация интерфейса для захвата с устройства.
  FpsController                   capture_fps_;        //< Поле для контроля частоты захвата.
  IVideoBuff::ptr                 buff_;               //< Текущий буфер.
  std::unique_ptr<std::thread>    recv_thread_;        //< Поток захвата данных из устройства.
  std::mutex                      src_mtx_;            //< Синхр. примитив для организации доступа к полям объекта между потоком захвата и рабочим потоком.
  bool                            stop_recv_;          //< Флаг-требование, остановить захват кадров.
  std::list<keys2buffs_ptr_type>  lframes_;            //< Список готовых буферов.
  ICaptureImageNullImpl::ptr      null_impl_;          //< ???
  ICaptureImage::weak_ptr         active_impl_;        //< Реализация захвата изображения, полученная от нижелижащего драйвера. Опционально.
  bool                            sync_ok_;            //< Флаг требования синхронизации.


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::BaseInfoFilter);
  //  BaseInfoFilter overrides
  virtual bool load_int (const base_functs::xml::itn& _node) override;
  virtual void sync_int (bool _force) override;
};

}}}      // namespace dlls::sources::gen_vgen
