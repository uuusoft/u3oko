#pragma once
/**
\file       video-driver-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::driver
{
class VideoDriverProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (VideoDriverProp)
  U3_ADD_MAKE_SHARED_THIS (VideoDriverProp)
  U3_ADD_DELETE_MOVE_COPY (VideoDriverProp)

  using ext_vals_storage_type = boost::unordered_flat_map< std::string, std::string >;

  explicit VideoDriverProp (const Acessor& = Acessor (0));
  virtual ~VideoDriverProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/videos/generic/driver/video-driver-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  std::string                   name_impl_dll_;     //< Имя DLL реализации захвата данных из источника
  ::libs::utility::utils::cuuid cat_dshow_;         //< Идентификатор каталога dshow DEPRECATED
  std::string                   device_name_;       //< Имя устройства
  std::int32_t                  device_indx_ = 0;   //< Индекс устройства в каталоге dshow DEPRECATED
  ext_vals_storage_type         ext_vals_;          //<

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  void sync_data ();
};
}   // namespace libs::events_base::props::videos::generic::driver

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::driver::VideoDriverProp);
