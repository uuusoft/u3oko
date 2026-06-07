#pragma once
/**
\file       change-state-event.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/state/change-state-process-type-event";
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

  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual void copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::runtime::state

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::state::ChangeStateProcessEvent);
