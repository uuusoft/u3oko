#pragma once
/**
\file       ievent.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_events
*/

#ifndef CHECK_STATE_COPY_EVENT
#define CHECK_STATE_COPY_EVENT(event_type)                                        \
  UASSERT (this != _src);                                                         \
  const auto _dsrc = ::libs::iproperties::helpers::cast_event<event_type> (_src); \
  UASSERT (_dsrc);
#endif


#ifndef UUU_DISABLE_ACOPY_TYPE
#define UUU_DISABLE_ACOPY_TYPE(type) \
  type (const type& _src) = delete;  \
  type& operator= (const type& _src) = delete;
#endif

namespace dlls { namespace devents { namespace impl {
//  forward
class EventsImpl;

}}}      // namespace dlls::devents::impl

namespace libs { namespace events {
//  syn
using ::utils::dbuffs::video::consts::offs::off_buff_type;
/**
  \brief  Базовый класс (интерфейс) всех событий системы.
          Под "событиями" подразумевается сохраняемые свойства фильтров, собственно события графа обработки данных, объекты обмена между модулями и прочее.
  */
class IEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;


  public:
  //  ext types
  using text_id_type = std::string;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IEvent);
  UUU_DISABLE_ACOPY_TYPE (IEvent);

  virtual ~IEvent ();
  /**
    \brief  Виртуальное копирование объекта через указатель на базовый класс.
    \param[in]  _src  указатель на объект-источник, должен быть того же типа, что и назначение.
    */
  void copy (const IEvent::craw_ptr _src);
  /**
    \brief      Функция проверки на возможность загрузки объекта из xml узла.
    \param[in]  _prop узел.
    \return     true, если узел содержит свойства типа, к которому принадлежит объект, иначе false.
    */
  bool check_node (const base_functs::xml::itn& _node);
  /**
    \brief      Функция загрузки объекта из xml узла.
    \param[in]  _prop узел.
    */
  void load (const base_functs::xml::itn& _prop);
  /**
    \brief    Функция возращает состояние объекта класса, с точки зрения возможности использования его свойств на данный момент.
    \return   состояние события.
    */
  const UsingStateEvent& get_using_state () const;
  /**
    \brief    Функция возращает текстовый идентификатор типа для использоваения в файлах, которые могут формироваться в том числе и пользователем системы.
              Обычно это просто путь к файлу с реализацией, что гарантирует его уникальность по определению.
    \return   идентификатор типа события.
    */
  const text_id_type& get_mid () const;
  /**
    \brief  Вспомогательная функция для синронизации текстового поля и значения используемого расширения CPU.
            Нужна для работы с HTTP сервером, который работает только с текстовым полем.
    */
  void sync_txt2val ();
  /**
    \brief  Вспомогательная функция для синронизации текстового поля и значения используемого расширения CPU.
            Нужна для работы с HTTP сервером, который работает только с текстовым полем.
    */
  void sync_val2txt ();
  /**
    \brief  Корректировка внутренних переменных структуры.
    */
  void self_correct ();
  /**
  \brief  
  */
  bool
  is_failed () const
  {
    return is_failed_int ();
  }


  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };
  /**
  \brief  
  */
  template <typename T>
  IEvent::ptr
  helper_impl_clone_funct (typename T::craw_ptr _src, const TypeCloneEvent& _deep) const
  {
    auto _res = T::make_shared_this ();
    if (TypeCloneEvent::full == _deep)
      {
        _res->copy (_src);
      }
    return _res;
  }
  IEvent ();
  /**
    \brief      Функция клонирования объекта.
    \param[in]  _deep параметр задает глубину копирования (полное/только создание объекта по умолчанию).
    \return     копия объекта.
    */
  IEvent::ptr clone (const ::libs::events::TypeCloneEvent& _deep = TypeCloneEvent::full) const;

  //  IEvent interface
  virtual IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const = 0;
  virtual bool        check_node_int (const base_functs::xml::itn& _node)           = 0;
  virtual void        load_int (const base_functs::xml::itn& _prop)                 = 0;
  virtual void        copy_int (const IEvent::craw_ptr _src);
  virtual void        self_correct_int ();
  virtual void        sync_txt2val_int ();
  virtual void        sync_val2txt_int ();
  virtual bool        is_failed_int () const;

  text_id_type    property_name_;      //< Имя свойства (события), переопределяется классом-потомком. Используется при загрузке из xml.
  UsingStateEvent state_;              //< Общее состояние свойства (события). Отключено, включено и прочее.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}      // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IEvent);
