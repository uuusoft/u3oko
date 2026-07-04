#pragma once
/**
\file       change-state-event.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::state
{
/// Событие-увеводмление об изменении состояния подсистемы с точки зрения активности
class ChangeStateProcessEvent final : public RuntimeEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (ChangeStateProcessEvent)
  U3_ADD_MAKE_SHARED_THIS (ChangeStateProcessEvent)
  U3_ADD_DELETE_MOVE_COPY (ChangeStateProcessEvent)

  explicit ChangeStateProcessEvent (const Acessor& = Acessor (0), bool start = true);
  virtual ~ChangeStateProcessEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/runtime/state/change-state-process-type-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool is_start () const;
  void set_start (bool val);

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::runtime::RuntimeEvent)

  bool start_ = false;   //< Флаг старта подсистемы

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::runtime::state

BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::state::ChangeStateProcessEvent);
