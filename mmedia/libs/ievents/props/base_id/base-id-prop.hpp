#pragma once
/**
\file       base-id-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       18.07.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::props::base_id
{
/// Свойства фильтра графа обработк данных для идентификации объекта данных.
class BaseIdProp final : virtual public ievents::Event
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
  using buf2module_infos_type = std::list< Buff2ModuleInfo >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseIdProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseIdProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (BaseIdProp)

  explicit BaseIdProp (const Acessor& = Acessor (0));
  virtual ~BaseIdProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/base_id/base-id-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  source_name_type      source_name_;   //< Имя источника-объекта (камеры, микрофон etc)
  buf2module_infos_type buf2modules_;   //< Информация о маршрутизации данных от этого источника

  protected:
  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  void load_buf2module (const ::pugi::xml_named_node_iterator& node, Buff2ModuleInfo* prop);

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::ievents::props::base_id

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::base_id::BaseIdProp);
