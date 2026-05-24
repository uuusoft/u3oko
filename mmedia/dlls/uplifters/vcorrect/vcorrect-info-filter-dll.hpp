#pragma once
/**
\file       vcorrect-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vcorrect_vdd
*/

namespace dlls::uplifters::vcorrect
{
/// Параметры модуля коррекции изображения
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter ();

  void init ();

  syn::VideoCorrectProp::raw_ptr rprops_;          //< Настроенный указатель на свойства (для удобства)
  syn::ICorrectImage::weak_ptr   active_impl_;     //< Выбранная на данный момент реализация коррекции изображения Может например прийти вместе с сообщением ::libs::ievents::runtime::interf::InterfCorrectImageEvent
  syn::ICorrectImage::ptr        soft_impl_;       //< Програмная реализация, которая присутствует всегда
  syn::ICorrectImage::weak_ptr   hardware_impl_;   //< Аппаратная реализация коррекции изображения Может например прийти вместе с сообщением ::libs::ievents::runtime::interf::InterfCorrectImageEvent
  bool                           synced_;          //< Флаг требования синхронизации

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::BaseInfoFilter)
  //  BaseInfoFilter overrides
  virtual bool load_int (const ::pugi::xml_named_node_iterator& node) override;
  virtual void sync_int (bool force) override;
};
}   // namespace dlls::uplifters::vcorrect
