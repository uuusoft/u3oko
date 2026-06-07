#pragma once
/**
\file       mem-resource-http-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.07.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events::events
{
class MemResourceStorageEvent : public BaseStorageEvent
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
  using id_mem_type         = std::string;
  using number_mem_buf_type = long long;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (MemResourceStorageEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MemResourceStorageEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (MemResourceStorageEvent)

  explicit MemResourceStorageEvent (
    const Acessor&                    = Acessor (0),
    const id_mem_type&         id     = "",
    const number_mem_buf_type& number = 0);

  virtual ~MemResourceStorageEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/istorage_events/events/mem-resource-storage-event";
    return ret;
  }

  const id_mem_type&         get_id () const;
  void                       set_id (const id_mem_type& id);
  const number_mem_buf_type& get_numder () const;
  void                       set_number (const number_mem_buf_type& number);
  bool                       get_request () const;
  void                       set_request (bool request);

  protected:
  id_mem_type         id_;                     //< Идентификатор ресурса. Например см. ZipDataEvent::id_buf_type
  number_mem_buf_type number_;                 //< Порядковый номер ресурса
  bool                request_for_transmit_;   //< Флаг требование - пометить буфер для передачи. Т.е. http клиент обязуется забрать данный буфер

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::MemResourceStorageEvent);
