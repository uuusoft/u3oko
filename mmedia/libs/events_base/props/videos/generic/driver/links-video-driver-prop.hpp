#pragma once
/**
\file       links-video-driver-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::driver
{
class LinksVideoDriverProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (LinksVideoDriverProp)
  U3_ADD_MAKE_SHARED_THIS (LinksVideoDriverProp)
  U3_ADD_DELETE_MOVE_COPY (LinksVideoDriverProp)

  explicit LinksVideoDriverProp (const Acessor& = Acessor (0));
  virtual ~LinksVideoDriverProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/videos/generic/driver/links-video-driver-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  ::utils::dbufs::allocator::BufAllocatorProxy::raw_ptr pdriver2buf_ = nullptr;   //<
  ::utils::mems::impl::BlockMemAllocatorProxy::raw_ptr  pdriver2mem_ = nullptr;   //<

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
};
}   // namespace libs::events_base::props::videos::generic::driver

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::driver::LinksVideoDriverProp);
