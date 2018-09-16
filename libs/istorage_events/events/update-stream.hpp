#pragma once
/**
\file       update-stream.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events { namespace events {
/**
\brief  Событие для получения или закрытия хендла на передачу данных по идентификатору пути и по идентифкатору камеры. UpdateStream /open/close/
*/
class UpdateStream : public BaseStorageEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (UpdateStream);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (UpdateStream);
  UUU_DISABLE_ACOPY_TYPE (UpdateStream);

  explicit UpdateStream (const Acessor& = Acessor (0));

  virtual ~UpdateStream ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/istorage_events/events/update-stream";
    return _ret;
  }

  TypeObjectId        obj_id_;         //< Идентификатор объекта.
  stream_id_type      stream_id_;      //< Идентификатор потока.
  TypeUpdateStream    action_;         //< Действие над потоком.
  TypeActionStream    operation_;      //< Тип затребованной операции над данными в потоке.
  TypeDirectionStream direction_;      //< Направление потока.
  TimeStream          time_;           //< Время потока.


  protected:
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseStorageEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
};

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::UpdateStream);
