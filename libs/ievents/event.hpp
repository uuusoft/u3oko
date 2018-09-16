#pragma once
/**
\file       event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
*/

namespace libs { namespace ievents {
//  syn
using ::utils::dbuffs::video::consts::offs::off_buff_type;
using ::libs::events::UsingStateEvent;
/**
\brief  Реализация базового интерфейса всех событий системы.
*/
class Event : public ::libs::events::IEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (Event);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (Event);
  UUU_DISABLE_ACOPY_TYPE (Event);

  explicit Event (const Acessor& = Acessor (0));

  virtual ~Event ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/event";
    return _ret;
  }


  protected:
  virtual bool check_node_int (const base_functs::xml::itn& _node) override;
  virtual void load_int (const base_functs::xml::itn& _prop) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::IEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
};

}}      // namespace libs::ievents

BOOST_CLASS_EXPORT_KEY (::libs::ievents::Event);
