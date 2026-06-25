#pragma once
/**
\file       end-point-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::terminals
{
/// Свойство конечной точки графа обработки данных Определяет дальнейший путь данных (http server, gui etc)
class EndPointProp final : public Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (EndPointProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (EndPointProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (EndPointProp)

  explicit EndPointProp (const Acessor& = Acessor (0));
  virtual ~EndPointProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/terminals/end-point-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool is_send () const;
  bool is_notify () const;

  protected:
  //  Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  bool enable_send_   = true;    //< Флаг, глобальный для данной камеры, управляет включением передачи данных в другие модули
  bool enable_notify_ = false;   //< Флаг включения посылки сообщения о передаче данных
};
}   // namespace libs::ievents::props::terminals

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::terminals::EndPointProp);
