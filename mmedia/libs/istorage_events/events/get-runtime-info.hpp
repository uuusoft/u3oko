#pragma once
/**
\file       get-runtime-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
struct RuntimeStreamInfo {
  RuntimeStreamInfo ()
  {
  }

  void
  reset ()
  {
    stream_id_         = consts::empty_stream_id;
    count_write_bytes_ = 0;
    count_read_bytes_  = 0;
    count_errors_      = 0;
  }

  stream_id_type stream_id_         = consts::empty_stream_id;   //<
  std::uint64_t  count_write_bytes_ = 0;                         //<
  std::uint64_t  count_read_bytes_  = 0;                         //<
  std::uint64_t  count_errors_      = 0;                         //<

  private:
  friend class boost::serialization::access;

  // REFACT
  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (stream_id_);
    ar& BOOST_SERIALIZATION_NVP (count_write_bytes_);
    ar& BOOST_SERIALIZATION_NVP (count_read_bytes_);
    ar& BOOST_SERIALIZATION_NVP (count_errors_);
  }
};


class GetRuntimeInfo : public BaseStorageEvent
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
  using runtime_storage_type = std::vector< RuntimeStreamInfo >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (GetRuntimeInfo)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetRuntimeInfo)
  U3_HELPER_DISABLE_ACOPY_TYPE (GetRuntimeInfo)

  explicit GetRuntimeInfo (const Acessor& = Acessor (0));
  virtual ~GetRuntimeInfo ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/istorage_events/events/get-runtime-info";
    return ret;
  }

  path_id_type         id_path_;        //<
  runtime_storage_type stream_infos_;   //<

  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::GetRuntimeInfo);
