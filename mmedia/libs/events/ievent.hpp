#pragma once
/**
\file       ievent.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mevents
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

  protected:
  struct Acessor;

  public:
  //  ext types
  using hid_type = std::string_view;

  U3_ADD_POINTERS_TO_SELF (IEvent)
  U3_ADD_DELETE_MOVE_COPY (IEvent)

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events/ievent";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  virtual ~IEvent () = default;

  auto
  sync_event_props () -> void
  {
    // empty ok
  }

  auto get_mid () const -> const IEvent::hid_type&;

  /// Виртуальное копирование объекта через указатель на базовый класс
  /// \param[in]  src  указатель на объект-источник, должен быть того же типа, что и назначение
  void copy (const IEvent::craw_ptr);

  /// Функция загрузки объекта из json
  /// \param[in]  prop узел
  void load_json (const std::string&);

  /// Функция загрузки объекта из json
  /// \param[in]  prop узел
  std::string save_json () const;

  /// Функция возращает состояние объекта класса, с точки зрения возможности использования его свойств на данный момент
  /// \return   состояние события
  const PropertyUsings& get_using_state () const;
#if 0
  /// Функция возращает текстовый идентификатор типа для использоваения в файлах, которые могут формироваться в том числе и пользователем системы
  /// Обычно это просто путь к файлу с реализацией, что гарантирует его уникальность по определению
  /// \return   идентификатор типа события
  hid_type get_mid () const;
#endif
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
  virtual auto get_mid_int () const -> const IEvent::hid_type&               = 0;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> IEvent::ptr = 0;
  virtual auto load_json_int (const ::boost::json::object&) -> void          = 0;
  virtual auto save_json_int (::boost::json::object&) const -> void          = 0;
  virtual auto copy_int (const IEvent::craw_ptr) -> void;
  virtual auto self_correct_int () -> void;
  virtual auto sync_txt2val_int () -> void;
  virtual auto sync_val2txt_int () -> void;
  virtual auto is_failed_int () const -> bool;

  PropertyUsings state_ = PropertyUsings::disabled;   //< Общее состояние свойства (события) [отключено, включено и прочее]

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
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
BOOST_CLASS_TRACKING (::libs::events::IEvent, boost::serialization::track_always);
