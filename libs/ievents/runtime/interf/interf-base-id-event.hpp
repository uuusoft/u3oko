//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       interf-base-id-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       19.07.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/

namespace libs { namespace ievents { namespace runtime { namespace interf {
/**
  \brief  Сообщение с интерфейсом для идентификации источника данных.
  */
class InterfBaseIdEvent : public BaseInterfEvent
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
  using impl_ptr_type = IBaseId::weak_ptr;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (InterfBaseIdEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InterfBaseIdEvent);
  UUU_DISABLE_ACOPY_TYPE (InterfBaseIdEvent);

  explicit InterfBaseIdEvent (const Acessor& = Acessor (0), const impl_ptr_type& = impl_ptr_type ());

  virtual ~InterfBaseIdEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/runtime/interf/interf-base-id-event";
    return _ret;
  }

  impl_ptr_type get_interface ();

  void set_interface (const impl_ptr_type&);


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseInterfEvent);

  impl_ptr_type impl_;      //< ���������� ���������� ���������� �� ��������� ����������.
#if 0
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */);
#endif
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;
};

}}}}      // namespace libs::ievents::runtime::interf

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::interf::InterfBaseIdEvent);
