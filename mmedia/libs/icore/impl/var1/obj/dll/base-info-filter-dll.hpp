#pragma once
/**
\file       base-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj::dll
{
/// Интерфейс для загружаемых из xml файла свойств фильтра графа обработки данных
struct BaseInfoFilter {
  public:
  BaseInfoFilter ();
  virtual ~BaseInfoFilter ();

  /// Функция загрузки данных из узла xml
  bool load (const ::pugi::xml_named_node_iterator& node);
  /// Функция синхронизации данных после загрузки
  void sync (bool force);

  // U3-REFACT
  std::list< ::libs::events::IEvent::ptr > ef_props_;   //< Свойства фильтра

  protected:
  //  internal typess
  using str2prop_type = std::unordered_map< std::string, ::libs::ievents::Event::raw_ptr >;

  virtual bool load_int (const ::pugi::xml_named_node_iterator& node);
  virtual void sync_int (bool force);

  str2prop_type str2props_;   //< Поле для процесса загрузки свойств из xml файла
};
}   // namespace libs::icore::impl::var1::obj::dll
