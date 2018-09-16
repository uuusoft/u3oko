//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       buff-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace runtime { namespace mem {
//  syn
using ::utils::dbuffs::video::IVideoBuff;
/**
\brief  Событие-уведомление с буферами под/c данными.
*/
class BuffEvent : public RuntimeEvent
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
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BuffEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BuffEvent);
  UUU_DISABLE_ACOPY_TYPE (BuffEvent);

  BuffEvent (const Acessor& = Acessor (0));

  explicit BuffEvent (IVideoBuff::cptr& _buff);

  virtual ~BuffEvent ()
  {}

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/runtime/mem/buff-event";
    return _ret;
  }

  IVideoBuff::ptr& get_buff ();


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent);

  IVideoBuff::ptr buff_;      //< Буфер с данными, связанный с событием.

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;
};

}}}}      // namespace libs::ievents::runtime::mem

//BOOST_CLASS_EXPORT_KEY( ::libs::ievents::runtime::mem::BuffEvent );
