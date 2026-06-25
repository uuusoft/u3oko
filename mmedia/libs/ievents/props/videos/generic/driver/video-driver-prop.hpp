#pragma once
/**
\file       video-driver-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::driver
{
class VideoDriverProp final : virtual public ievents::Event
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoDriverProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoDriverProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoDriverProp)

  explicit VideoDriverProp (const Acessor& = Acessor (0));
  virtual ~VideoDriverProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/videos/generic/driver/video-driver-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  std::string                                    name_impl_dll_;     //< Имя DLL реализации захвата данных из источника
  ::libs::helpers::utils::cuuid                  cat_dshow_;         //< Идентификатор каталога dshow. DEPRECATED
  std::string                                    device_name_;       //< Имя устройства
  std::int32_t                                   device_indx_ = 0;   //< Индекс устройства в каталоге dshow. DEPRECATED
  std::unordered_map< std::string, std::string > ext_vals_;          //<

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  void sync_data ();
};
}   // namespace libs::ievents::props::videos::generic::driver

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::driver::VideoDriverProp);
