#pragma once
/**
\file       ipath.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_core
\brief      Объявление интерфейса графа обработки данных.
*/

namespace libs { namespace core { namespace path {
/// Тип для функции-параметра, передающимся при посылки события в граф.
typedef std::function<bool(const PathObjID& _obj_info, IPathObj::craw_ptr)> send_funct_type;
/**
\brief  Интерфейс графа обработки данных. 
        Все функции интерфейса потокобезопасны.
*/
class IPath
{
  friend class ::libs::icore::impl::var1::path::Path;

  public:
  //  ext types
  typedef std::set<PathObjID> array_id_objs_type;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IPath);

  IPath (const IPath& _src) = delete;
  IPath& operator= (const IPath& _src) = delete;
  /**
  \brief      Функция конструирования графа из xml файла.
  \param[in]  _file путь к xml файлу с описанием графа.
  */
  void
  load (const std::string& _file)
  {
    return load_int (_file);
  }
  /**
  \brief    Функция получения идентификаторов всех объектов в графе.
  \return   список идентификаторов объектов в графе.
  */
  const array_id_objs_type&
  get_objs () const
  {
    return get_objs_int ();
  }
  /**
  \brief          Функция посылки события в граф его объектам.
  \param[in]      _id_obj   идентфикатор объекта.
  \param[in, out] _evnt     указатель на сообщение.
  */
  void
  send_event2obj (const PathObjID& _id_obj, events::IEvent::ptr& _evnt)
  {
    return send_event2obj_int (_id_obj, _evnt);
  }
  /**
  \brief      Функция установки интерфейса для отправки сообщений в лог системы.
  \param[in]  _ptr
  */
  void
  set_logger (::libs::link::ILink::weak_ptr _ptr)
  {
    UASSERT (_ptr.lock ());
    set_logger_int (_ptr);
    return;
  }


  private:
  /// Конструктор, закрытый для определенности, т.к. базовый класс с чисто виртуальными функциями.
  IPath ()
  {}
  /// Деструктор. Закрываем, удалить граф может только само ядро. Клиент может только попросить ядро удалить данный граф.
  virtual ~IPath ()
  {}

  //  IPath interface
  virtual void                      load_int (const std::string& _file)                                       = 0;
  virtual const array_id_objs_type& get_objs_int () const                                                     = 0;
  virtual void                      send_event2obj_int (const PathObjID& _id_obj, events::IEvent::ptr& _evnt) = 0;
  virtual void                      set_logger_int (::libs::link::ILink::weak_ptr _ptr)                       = 0;
};

}}}      // namespace libs::core::path
