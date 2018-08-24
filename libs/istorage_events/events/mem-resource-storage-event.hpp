#pragma once
/**
\file       mem-resource-http-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events { namespace events {
/**
  \brief  empty brief
  */
class MemResourceStorageEvent : public BaseStorageEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  // ext types
  using id_mem_type          = std::string;
  using number_mem_buff_type = long long;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (MemResourceStorageEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MemResourceStorageEvent);
  UUU_DISABLE_ACOPY_TYPE (MemResourceStorageEvent);

  explicit MemResourceStorageEvent (const Acessor& = Acessor (0), const id_mem_type& _id = "", const number_mem_buff_type& _number = 0);

  virtual ~MemResourceStorageEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/istorage_events/events/mem-resource-storage-event";
    return _ret;
  }

  const id_mem_type& get_id () const;

  void set_id (const id_mem_type& _id);

  const number_mem_buff_type& get_numder () const;

  void set_number (const number_mem_buff_type& _number);

  bool get_request () const;

  void set_request (bool _request);


  protected:
  id_mem_type          id_;                        //< Идентификатор ресурса. Например см. ZipDataEvent::id_buff_type.
  number_mem_buff_type number_;                    //< Порядковый номер ресурса.
  bool                 request_for_transmit_;      //< Флаг требование - пометить буфер для передачи. Т.е. web клиент обязуется забрать данный буфер.


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseStorageEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::MemResourceStorageEvent);
