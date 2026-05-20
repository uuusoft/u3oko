#pragma once
/**
\file       ievents.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_events
*/

namespace libs::events::io
{
/// Интерфейс для генерации, сериализации, конверсии всех доступных событий в системе. Введен в первую очередь для нивилирования различий в реализациях ABI
/// Также используется для кеширования, сбора статистики и прочего
class IEvents
{
  public:
  // ext types
  using hid_type = IEvent::hid_type;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IEvents)
  /// Функция возвращает событие по идентификатору
  /// \param[in]  id идентификатор события
  /// \return     событие
  virtual IEvent::ptr get (const hid_type& id, const char* debid = nullptr) = 0;
  /// Функция клонирует событие, гарантируя ему базовый модуль
  /// \param[in]  src  входное событие
  /// \param[in]  type тип клонирования
  /// \return     копия события
  virtual IEvent::ptr clone (const IEvent::craw_ptr src, const Deeps& type) = 0;
  /// Функция преобразования типа события, внтури базового модуля
  /// \param[in]  src  входное событие
  /// \param[in]  id   идентификатор типа выходного события
  /// \return     выходное событие или null, если преобразование невозможно
  virtual void* dcast (IEvent::craw_ptr src, const hid_type& id) = 0;
  /// Функция преобразования события в xml, внтури базового модуля
  /// \param[in]  src  входное событие
  /// \param[in]  xml   строка xml в формате boost::serialization
  /// \return     true, при успехе
  virtual bool event2xml (IEvent::ptr& src, std::string& xml) = 0;
  /// Функция преобразования xml в событие, внтури базового модуля
  /// \param[in]  xml  строка xml в формате boost::serialization
  /// \param[in]  dst  восстановленное выходное событие
  /// \return     true, при успехе
  virtual bool xml2event (const std::string& xml, IEvent::ptr& dst) = 0;
  /// Функция преобразования события в xml, внтури базового модуля
  /// \param[in]  src  входное событие
  /// \param[in]  xml   строка xml в формате boost::serialization
  /// \return     true, при успехе
  virtual bool event2bin (IEvent::ptr& src, std::ostream& bin) = 0;
  /// Функция преобразования xml в событие, внтури базового модуля
  /// \param[in]  xml  строка xml в формате boost::serialization
  /// \param[in]  dst  восстановленное выходное событие
  /// \return     true, при успехе
  virtual bool bin2event (std::istream& bin, IEvent::ptr& dst) = 0;

  protected:
  IEvents ()
  {
  }

  virtual ~IEvents ()
  {
  }
};
}   // namespace libs::events::io
