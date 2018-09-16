#pragma once
/**
\file       get-runtime-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events { namespace events {
/**
\brief  
*/
struct RuntimeStreamInfo
{
  RuntimeStreamInfo () :
    stream_id_ (consts::empty_stream_id),
    count_write_bytes_ (0),
    count_read_bytes_ (0),
    count_errors_ (0)
  {}

  void
  reset ()
  {
    stream_id_         = consts::empty_stream_id;
    count_write_bytes_ = 0;
    count_read_bytes_  = 0;
    count_errors_      = 0;
    return;
  }

  stream_id_type   stream_id_;              //< Идентификатор потока.
  signed long long count_write_bytes_;      //< Количества байт на запись.
  signed long long count_read_bytes_;       //< Количества байт на запись.
  signed long long count_errors_;           //< Счетчик ошибок записи/чтения.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (stream_id_);
    ar& BOOST_SERIALIZATION_NVP (count_write_bytes_);
    ar& BOOST_SERIALIZATION_NVP (count_read_bytes_);
    ar& BOOST_SERIALIZATION_NVP (count_errors_);
    return;
  }
};
/**
\brief  Событие для получения статистики использования по идентификатору пути (открытые хендлы передачи данных, количество байт и по ним и прочее). Быстро.
*/
class GetRuntimeInfo : public BaseStorageEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (GetRuntimeInfo);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetRuntimeInfo);
  UUU_DISABLE_ACOPY_TYPE (GetRuntimeInfo);
  using runtime_storage_type = std::vector<RuntimeStreamInfo>;

  explicit GetRuntimeInfo (const Acessor& = Acessor (0));

  virtual ~GetRuntimeInfo ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/istorage_events/events/get-runtime-info";
    return _ret;
  }

  path_id_type         id_path_;           //< Идентификатор пути.
  runtime_storage_type stream_infos_;      //< Список открытых поток на данный момент.


  protected:
  //  ievents::Event overrides
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseStorageEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
};

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::GetRuntimeInfo);
