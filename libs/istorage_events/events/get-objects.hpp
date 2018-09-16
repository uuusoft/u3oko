#pragma once
/**
\file       get-objects.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events { namespace events {
/**
\brief  Событие для получения списка объектов (камер) по идентификатору пути.
*/
class GetObjects : public BaseStorageEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (GetObjects);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GetObjects);
  UUU_DISABLE_ACOPY_TYPE (GetObjects);

  explicit GetObjects (const Acessor& = Acessor (0));

  virtual ~GetObjects ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/istorage_events/events/get-objects";
    return _ret;
  }

  path_id_type                id_path_;      //< Идентификатор пути.
  std::vector<TypeObjectId> objs_;         //< Возвращаемый список объектов.


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

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::events::GetObjects);
