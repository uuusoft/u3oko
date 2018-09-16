#pragma once
/**
\file       call-interf-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.10.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj { namespace dll {
/**
\brief  Тип для группировки параметров функции-вызова в dll объекте.
*/
struct CallInterfInfo
{
  /// Конструктор по умолчанию.
  CallInterfInfo () :
    finfo_ (nullptr)
  {}
  /**
  \brief      Рабочий конструктор.
  \param[in]  _event  событие, которое пересылается объекту в dll.
  \param[in]  _finfo  информация о фильтре, которому принадлежит данный объект.
  */
  CallInterfInfo (::libs::events::IEvent::ptr& _event, FilterInfo* _finfo) :
    event_ (_event),
    finfo_ (_finfo)
  {}
  /// Деструктор.
  ~CallInterfInfo ()
  {}
  /**
  \brief  Функция самотестирования экземляра.
  \return true, если поля заполнены верно.
  */
  bool
  check () const
  {
    if (!finfo_ || !event_)
      {
        return false;
      }
    return true;
  }

  FilterInfo*                 finfo_;      //< Указатель на фильтр, которому принадлжеит данный объект.
  ::libs::events::IEvent::ptr event_;      //< Событие, которое пересылается объекту.
};

}}}}}}      // namespace libs::icore::impl::var1::obj::dll
