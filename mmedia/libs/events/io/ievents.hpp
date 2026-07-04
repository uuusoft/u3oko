#pragma once
/**
\file       ievents.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/

namespace libs::events::io
{
/// Интерфейс для генерации, сериализации, конверсии всех доступных событий в системе
/// Введен в первую очередь для нивилирования различий в реализациях ABI
/// Также используется для кеширования, сбора статистики и прочего
class IEvents
{
  public:
  // ext types
  using hid_type = IEvent::hid_type;

  U3_ADD_POINTERS_TO_SELF (IEvents)
  U3_ADD_DELETE_MOVE_COPY (IEvents)

  /// Функция возвращает событие по идентификатору
  /// \param[in]  id идентификатор события
  /// \return     событие
  virtual auto get (const hid_type&) -> IEvent::ptr = 0;

  /// Функция клонирует событие, гарантируя ему базовый модуль
  /// \param[in]  src  входное событие
  /// \param[in]  type тип клонирования
  /// \return     копия события
  virtual auto clone (const IEvent::craw_ptr, const Deeps&) -> IEvent::ptr = 0;

  /// Функция преобразования типа события, внтури базового модуля
  /// \param[in]  src  входное событие
  /// \param[in]  id   идентификатор типа выходного события
  /// \return     выходное событие или null, если преобразование невозможно
  virtual auto dcast (IEvent::craw_ptr, const hid_type&) -> const void* = 0;

  /// Функция преобразования события в xml, внтури базового модуля
  /// \param[in]  src  входное событие
  /// \param[in]  xml   строка xml в формате boost::serialization
  /// \return     true, при успехе
  virtual auto event2xml (IEvent::ptr&, std::string&) -> bool = 0;

  /// Функция преобразования xml в событие, внтури базового модуля
  /// \param[in]  xml  строка xml в формате boost::serialization
  /// \param[in]  dst  восстановленное выходное событие
  /// \return     true, при успехе
  virtual auto xml2event (const std::string&, IEvent::ptr&) -> bool = 0;

  /// Функция преобразования события в xml, внтури базового модуля
  /// \param[in]  src  входное событие
  /// \param[in]  xml   строка xml в формате boost::serialization
  /// \return     true, при успехе
  virtual auto event2bin (IEvent::ptr&, std::ostream&) -> bool = 0;

  /// Функция преобразования xml в событие, внтури базового модуля
  /// \param[in]  xml  строка xml в формате boost::serialization
  /// \param[in]  dst  восстановленное выходное событие
  /// \return     true, при успехе
  virtual auto bin2event (std::istream&, IEvent::ptr&) -> bool = 0;

  protected:
  IEvents ()          = default;
  virtual ~IEvents () = default;
};
}   // namespace libs::events::io
