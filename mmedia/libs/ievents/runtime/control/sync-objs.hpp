#pragma once
/**
\file       sync-objs.hpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::control
{
/// Событие для синхронизации состояния объектов (камеры/микрофон/пр.) для клиента
class SyncObjs : public RuntimeEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  constexpr static std::uint32_t max_group_count = 6;   //< с учетом количество действия 4 достаточно для всех случаев синхронизации
  //  ext types
  using obj_id_type = std::string;
  using groups_type = std::array< SyncObjsGroup, max_group_count >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (SyncObjs)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (SyncObjs)
  U3_HELPER_DISABLE_ACOPY_TYPE (SyncObjs)

  explicit SyncObjs (const Acessor& = Acessor (0));
  explicit SyncObjs (const groups_type& groups);
  virtual ~SyncObjs () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/control/sync-objs";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const groups_type& get_groups () const;
  groups_type&       update_groups ();
  const std::string& get_client_id () const;
  std::string&       update_client_id ();

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::RuntimeEvent)

  std::string client_id_;    //<
  groups_type obj_groups_;   //<

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::control

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::control::SyncObjs);
