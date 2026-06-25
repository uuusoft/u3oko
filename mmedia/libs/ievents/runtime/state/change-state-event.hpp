#pragma once
/**
\file       change-state-event.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::state
{
/// Событие-увеводмление об изменении состояния подсистемы с точки зрения активности
class ChangeStateProcessEvent final : public RuntimeEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ChangeStateProcessEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ChangeStateProcessEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ChangeStateProcessEvent)

  explicit ChangeStateProcessEvent (const Acessor& = Acessor (0), bool start = true);
  virtual ~ChangeStateProcessEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/state/change-state-process-type-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool is_start () const;
  void set_start (bool val);

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::RuntimeEvent)

  bool start_;   //< Флаг старта подсистемы

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::state

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::state::ChangeStateProcessEvent);
