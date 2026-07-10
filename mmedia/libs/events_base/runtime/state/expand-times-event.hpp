#pragma once
/**
\file       expand-times-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
\brief      Объявление типа для хранения и передачи статистики по затраченному времени
*/

namespace libs::events_base::runtime::state
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
/// Тип источника времени работы
enum class StatSources : std::uint32_t
{
  alg      = 0x00,   //< Источником данных является конкретный алгогитм
  path_obj = 0x01,   //< Источником данных является объект пути
  unknown  = 0xFF    //< Не определенно для общности
};
#endif

/// Тип действия, которое надо произвести над источником
enum class Actions : std::uint32_t
{
  get     = 0x00,   //< Получить статистику источника
  reset   = 0x01,   //< Сбросить статистику источника
  unknown = 0xFF    //< Не определенно для общности
};

/// Событие со статистикой по затраченному времени по агентам
class ExpandTimesEvent : public RuntimeEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using key_storage_type   = std::string;
  using storages_type      = ::libs::utility::statistic::ExpandedTimes::storages_type;
  using full_storages_type = boost::unordered_flat_map< key_storage_type, storages_type >;

  U3_ADD_POINTERS_TO_SELF (ExpandTimesEvent)
  U3_ADD_MAKE_SHARED_THIS (ExpandTimesEvent)
  U3_ADD_DELETE_MOVE_COPY (ExpandTimesEvent)

  explicit ExpandTimesEvent (
    const Acessor&           = Acessor (0),
    full_storages_type infos = full_storages_type ());

  virtual ~ExpandTimesEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/runtime/state/expand-times-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const full_storages_type& get_stats () const;
  const storages_type&      get_stat (const key_storage_type& key) const;
  void                      set_stat (const key_storage_type& key, const storages_type& infos);
  const Actions&            get_action () const;
  void                      set_action (const Actions& source);

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::runtime::RuntimeEvent)

  Actions                    action_ = Actions::get;   //< тип действия с данными источника
  std::string                source_id_;               //< идентификатор источника, если пусто - все идентификаторы в системе ::libs::core::graph::NodeID::id_name_type
  mutable full_storages_type infos_;                   //< собственно список с затраченном временем по агентам

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

BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::state::ExpandTimesEvent);
