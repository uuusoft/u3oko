//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       ievents.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events { namespace io {
/**
  \brief  Интерфейс для генерации, сериализации, конверсии всех доступных событий в системе.
  */
class IEvents
{
  public:
  // ext types
  using text_id_type = IEvent::text_id_type;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IEvents);
  /**
    \brief      Функция возвращает событие по идентификатору.
    \param[in]  _id идентификатор события.
    \return     событие.
    */
  virtual IEvent::ptr get (const text_id_type& _id) = 0;
  /**
  \brief      Функция клонирует событие, гарантируя ему базовый модуль.
  \param[in]  _src  входное событие.
  \param[in]  _type тип клонирования.
  \return     копия события.
  */
  virtual IEvent::ptr clone (const IEvent::craw_ptr _src, const TypeCloneEvent& _type) = 0;
  /**
  \brief      Функция преобразования типа события, внтури базового модуля.
  \param[in]  _src  входное событие.
  \param[in]  _id   идентификатор типа выходного события.
  \return     выходное событие или null, если преобразование невозможно.
  */
  virtual void* dcast (IEvent::craw_ptr _src, const text_id_type& _id) = 0;
  /**
  \brief      Функция преобразования события в xml, внтури базового модуля.
  \param[in]  _src  входное событие.
  \param[in]  _xml   строка xml в формате boost::serialization.
  \return     true, при успехе.
  */
  virtual bool event2xml (IEvent::ptr& _src, std::string& _xml) = 0;
  /**
  \brief      Функция преобразования xml в событие, внтури базового модуля.
  \param[in]  _xml  строка xml в формате boost::serialization.
  \param[in]  _dst  восстановленное выходное событие.
  \return     true, при успехе.
  */
  virtual bool xml2event (const std::string& _xml, IEvent::ptr& _dst) = 0;


  protected:
  IEvents ()
  {}

  virtual ~IEvents ()
  {}
};

}}}      // namespace libs::events::io
