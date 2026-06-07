#pragma once
/**
\file       get-objects.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
class GetObjects : public BaseStorageEvent
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (GetObjects)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetObjects)
  U3_HELPER_DISABLE_ACOPY_TYPE (GetObjects)

  explicit GetObjects (const Acessor& = Acessor (0));
  virtual ~GetObjects () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/istorage_events/events/get-objects";
    return ret;
  }

  path_id_type                path_id_;   //<
  std::vector< TypeObjectId > objs_;      //<

  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::GetObjects);
