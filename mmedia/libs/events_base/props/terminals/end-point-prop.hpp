#pragma once
/**
\file       end-point-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::terminals
{
/// Свойство конечной точки графа обработки данных Определяет дальнейший путь данных (http server, gui etc)
class EndPointProp final : public Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (EndPointProp)
  U3_ADD_MAKE_SHARED_THIS (EndPointProp)
  U3_ADD_DELETE_MOVE_COPY (EndPointProp)

  explicit EndPointProp (const Acessor& = Acessor (0));
  virtual ~EndPointProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/terminals/end-point-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool is_send () const;
  bool is_notify () const;

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  bool enable_send_   = true;    //< Флаг, глобальный для данной камеры, управляет включением передачи данных в другие модули
  bool enable_notify_ = false;   //< Флаг включения посылки сообщения о передаче данных
};
}   // namespace libs::events_base::props::terminals

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::terminals::EndPointProp);
