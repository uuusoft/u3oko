#pragma once
/**
\file       expand-times-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
\brief      Объявление типа для хранения и передачи статистики по затраченному времени
*/

namespace libs::ievents::runtime::state
{
#ifdef U3_FAKE_DISABLE
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
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using key_storage_type   = std::string;
  using storages_type      = ::libs::helpers::statistic::ExpandedTimes::storages_type;
  using full_storages_type = std::unordered_map< key_storage_type, storages_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ExpandTimesEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ExpandTimesEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ExpandTimesEvent)

  explicit ExpandTimesEvent (
    const Acessor&                  = Acessor (0),
    const full_storages_type& infos = full_storages_type ());

  virtual ~ExpandTimesEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/runtime/state/expand-times-event";
    return ret;
  }

  const full_storages_type& get_stats () const;
  const storages_type&      get_stat (const key_storage_type& key) const;
  void                      set_stat (const key_storage_type& key, const storages_type& infos);
  const Actions&            get_action () const;
  void                      set_action (const Actions& source);
  // const StatSources& get_source () const;
  // void set_source (const StatSources& source);

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::RuntimeEvent)

  Actions                    action_;      //< тип действия с данными источника
  std::string                source_id_;   //< идентификатор источника, если пусто - все идентификаторы в системе ::libs::core::graph::NodeID::name_id_type
  mutable full_storages_type infos_;       //< собственно список с затраченном временем по агентам
  // StatSources                source_;      //< Тип источника данных (по алгоритмам/по объектам пути/etc)

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

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::state::ExpandTimesEvent);
