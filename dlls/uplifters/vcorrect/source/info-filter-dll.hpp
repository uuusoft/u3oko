#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcorrect_vdd
\brief      empty brief
*/

namespace dlls { namespace uplifters { namespace vcorrect {
/**
  \brief  Параметры модуля коррекции изображения.
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  using props_type = VideoCorrectProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  void init ();

  ::libs::events::IEvent::ptr props_;            //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr         rprops_;           //< Настроенный указатель на свойства (для удобства).
  ICorrectImage::weak_ptr     active_impl_;      //< Выбранная на данный момент реализация коррекции изображения. Может например прийти вместе с сообщением ::libs::ievents::runtime::interf::InterfCorrectImageEvent
  bool                        sync_ok_;          //< Флаг требования синхронизации.


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::BaseInfoFilter);
  //  BaseInfoFilter overrides
  virtual bool load_int (const base_functs::xml::itn& _node) override;
  virtual void sync_int (bool _force) override;
};

}}}      // namespace dlls::uplifters::vcorrect
