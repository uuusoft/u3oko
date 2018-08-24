#pragma once
/**
\file       ipath-obj.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_core
\brief      Объявление интерфейса объекта графа по обработке данных.
*/

namespace libs { namespace core { namespace path {
/**
  \brief  Интерфейс объекта в графе по обработке данных.
  */
class IPathObj
{
  friend class ::libs::icore::impl::var1::path::Path;
  friend class ::libs::icore::impl::var1::obj::ObjPath;
  friend class ::libs::icore::impl::var1::obj::IPathObjExt;

  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IPathObj);

  IPathObj (const IPathObj& _src) = delete;
  IPathObj& operator= (const IPathObj& _src) = delete;

  protected:
  /**
    \brief      Функция запроса поддержки интерфейса объектом.
    \param[in]  _id   идентификатор интерфейса.
    \return     не 0, при успехе.
    */
  IInterfPathObj::raw_ptr
  query (const ::libs::helpers::utils::cuuid& _id)
  {
    return query_int (_id);
  }
  /**
    \brief          Функция посылки события в граф.
    \param[in, out] _evnt   указатель на сообщение.
    \param[in]      _funct  функция, определяет применимость события к данному объекту графа.
    */
  void
  send_event2me (events::IEvent::ptr& _evnt)
  {
    return send_event2me_int (_evnt);
  }
  /// Функция запуска объекта.
  void
  run ()
  {
    return run_int ();
  }
  /// Функция остановки объекта.
  void
  stop ()
  {
    return stop_int ();
  }


  private:
  /// Конструктор, закрытый, базовый класс с чисто виртуальными функциями.
  IPathObj ()
  {}
  /// Деструктор. Закрываем, удалить объект может только сам граф или реализации, а не клиент (пусть и по его требованию).
  virtual ~IPathObj ()
  {}

  virtual IInterfPathObj::raw_ptr query_int (const ::libs::helpers::utils::cuuid& _id) = 0;
  virtual void                    send_event2me_int (events::IEvent::ptr& _evnt)       = 0;
  virtual void                    run_int ()                                           = 0;
  virtual void                    stop_int ()                                          = 0;
};

}}}      // namespace libs::core::path
