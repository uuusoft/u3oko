#pragma once
/**
\file       event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents
{
/// Реализация базового интерфейса всех событий системы
class Event : public ::libs::events::IEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Event)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (Event)
  U3_HELPER_DISABLE_ACOPY_TYPE (Event)

  explicit Event (const Acessor& = Acessor (0));
  virtual ~Event () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/event";
    return ret;
  }

  protected:
  virtual void load_json_int (const ::boost::json::object& obj) override;
  virtual void save_json_int (::boost::json::object& obj) const override;
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::IEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::ievents

BOOST_CLASS_EXPORT_KEY (::libs::ievents::Event);
