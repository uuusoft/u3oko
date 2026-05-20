#pragma once
/**
\file       ievent.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    uuu_events
*/

namespace dlls::devents::impl
{
//  forward
class EventsImpl;
}   // namespace dlls::devents::impl


namespace libs::events
{
/// Базовый класс (интерфейс) всех событий системы
/// Под "событиями" подразумевается сохраняемые свойства фильтров, собственно события графа обработки данных, объекты обмена между модулями и прочее
class IEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor;

  public:
  //  ext types
  using hid_type = std::string;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (IEvent)

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/events/ievent";
    return ret;
  }

  virtual ~IEvent ();
  /// Виртуальное копирование объекта через указатель на базовый класс
  /// \param[in]  src  указатель на объект-источник, должен быть того же типа, что и назначение
  void copy (const IEvent::craw_ptr src);
  /// Функция загрузки объекта из json. \param[in]  prop узел
  void load_json (const std::string& prop);
  /// Функция загрузки объекта из json. \param[in]  prop узел
  std::string save_json () const;
  /// Функция возращает состояние объекта класса, с точки зрения возможности использования его свойств на данный момент
  /// \return   состояние события
  const PropertyUsings& get_using_state () const;
  /// Функция возращает текстовый идентификатор типа для использоваения в файлах, которые могут формироваться в том числе и пользователем системы
  /// Обычно это просто путь к файлу с реализацией, что гарантирует его уникальность по определению
  /// \return   идентификатор типа события
  const hid_type& get_mid () const;
  /// Вспомогательная функция для синронизации текстового поля и значения используемого расширения CPU
  //// Нужна для работы с HTTP сервером, который работает только с текстовым полем
  void sync_txt2val ();
  /// Вспомогательная функция для синронизации текстового поля и значения используемого расширения CPU
  /// Нужна для работы с HTTP сервером, который работает только с текстовым полем
  void sync_val2txt ();
  /// Корректировка внутренних переменных структуры
  void self_correct ();
  ///
  bool
  is_failed () const
  {
    return is_failed_int ();
  }
  /// Функция клонирования объекта
  /// \param[in]  deep параметр задает глубину копирования (полное/только создание объекта по умолчанию)
  /// \return     копия объекта
  IEvent::ptr clone (const ::libs::events::Deeps& deep = Deeps::full) const;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  IEvent ();

  //  IEvent interface
  virtual IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const = 0;
  virtual void        load_json_int (const ::boost::json::object& obj)    = 0;
  virtual void        save_json_int (::boost::json::object& obj) const    = 0;
  virtual void        copy_int (const IEvent::craw_ptr src);
  virtual void        self_correct_int ();
  virtual void        sync_txt2val_int ();
  virtual void        sync_val2txt_int ();
  virtual bool        is_failed_int () const;

  hid_type       property_name_;   //< Имя свойства (события), переопределяется классом-потомком. Используется при загрузке из xml
  PropertyUsings state_;           //< Общее состояние свойства (события). Отключено, включено и прочее

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};
/// Вспомогательная функция для облегчения реализации клонирования в производных типах
/// \tparam     EventType тип события для которого будет реализовано клонирование
/// \param[in]  src      источник данных для клонирования
/// \param[in]  deep     глубина клонирования (только тип или еще и данные в нем)
/// \return     копия события
template< typename EventType >
IEvent::ptr
deep_clone (typename EventType::craw_ptr src, const Deeps& deep)
{
  auto res = EventType::make_shared_this ();   //  статическое создание типа.
  if (Deeps::full == deep)
  {
    res->copy (src);   //  виртуальное копирование.
  }
  return res;
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::IEvent);
