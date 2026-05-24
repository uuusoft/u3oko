#pragma once
/**
\file       links-video-driver-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::driver
{
class LinksVideoDriverProp final : public ievents::Event
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (LinksVideoDriverProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (LinksVideoDriverProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (LinksVideoDriverProp)

  explicit LinksVideoDriverProp (const Acessor& = Acessor (0));
  virtual ~LinksVideoDriverProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/driver/links-video-driver-prop";
    return ret;
  }

  ::utils::dbufs::allocator::BufAllocatorProxy::raw_ptr     pdriver2buf_;   //<
  ::utils::mem_funcs::impl::BlockMemAllocatorProxy::raw_ptr pdriver2mem_;   //<

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::props::videos::generic::driver

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::driver::LinksVideoDriverProp);
