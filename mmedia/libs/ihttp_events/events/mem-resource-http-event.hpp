#pragma once
/**
\file       mem-resource-http-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.04.2018
\project    uuu_ihttp_events
*/

namespace libs::ihttp_events::events
{
class MemResourceHttpEvent : public BaseHttpEvent
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
  using number_mem_buf_type = std::int64_t;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (MemResourceHttpEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MemResourceHttpEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (MemResourceHttpEvent)

  explicit MemResourceHttpEvent (const Acessor& = Acessor (0), const id_mem_type& id = "", const number_mem_buf_type& number = 0);
  virtual ~MemResourceHttpEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ihttp_events/events/mem-resource-http-event";
    return ret;
  }

  const id_mem_type&         get_id () const;
  void                       set_id (const id_mem_type& id);
  const number_mem_buf_type& get_frame_numder () const;
  void                       set_frame_number (const number_mem_buf_type& number);
  bool                       get_request () const;
  void                       set_request (bool request);

  protected:
  id_mem_type         id_;                     //< Идентифкатор ресурса. Например см. ZipDataEvent::id_buf_type
  number_mem_buf_type number_;                 //< Порядковый номер ресурса
  bool                request_for_transmit_;   //< Флаг требование - пометить буфер для передачи. Т.е. http клиент обязуется забрать данный буфер

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ihttp_events::events::BaseHttpEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
  //  BaseHttpEvent overrides
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ihttp_events::events::MemResourceHttpEvent);
