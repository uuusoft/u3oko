#pragma once
/**
\file       call-interf-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.10.2016
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj::dll
{
/// Тип для группировки параметров функции-вызова в dll объекте
struct CallInterfInfo final {
  /// Конструктор по умолчанию
  CallInterfInfo () :
    finfo_ (nullptr)
  {
  }

  /// Рабочий конструктор
  /// \param[in]  event  событие, которое пересылается объекту в dll
  /// \param[in]  finfo  информация о фильтре, которому принадлежит данный объект
  CallInterfInfo (::libs::events::IEvent::ptr& event, FilterInfo* finfo) :
    event_ (event),
    finfo_ (finfo)
  {
  }

  ~CallInterfInfo ()
  {
  }

  /// Функция самотестирования экземляра
  /// \return true, если поля заполнены верно
  bool
  check () const
  {
    if (!finfo_ || !event_)
    {
      return false;
    }
    return true;
  }

  FilterInfo*                 finfo_;   //< Указатель на фильтр, которому принадлежит данный объект
  ::libs::events::IEvent::ptr event_;   //< Событие, которое пересылается объекту
};
}   // namespace libs::icore::impl::var1::obj::dll
