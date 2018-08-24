#pragma once
/**
\file       info-cpu-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace hardware {
//  syn
using ::libs::helpers::sys::cpu::TypeExtCpu;
using ::libs::helpers::sys::cpu::TextExtCpu;
/**
  \brief  События для хранения и передачи свойств, связанных с CPU. Тип используемого расширения, количество процессоров и т.п.
  */
class InfoCPUEvent : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (InfoCPUEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InfoCPUEvent);
  UUU_DISABLE_ACOPY_TYPE (InfoCPUEvent);

  explicit InfoCPUEvent (const Acessor& = Acessor (0), const TypeExtCpu& _simd = TypeExtCpu::usual, const unsigned short _count_cpu = UUU_ICAST_USHORT (0));

  virtual ~InfoCPUEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/hardware/info-cpu-event";
    return _ret;
  }

  TypeExtCpu get_type () const;

  void set_type (const TypeExtCpu& _type);

  unsigned short get_count () const;

  void set_count (const unsigned short _count_cpu);


  protected:
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        sync_txt2val_int () override;
  virtual void                        sync_val2txt_int () override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  std::string    text_simd_;      //< Текстовое представление simd
  TypeExtCpu     simd_;           //< Тип simd, который будет использоваться.
  unsigned short count_cpu_;      //< Количество потоков, которое будет использоно в пуле для обработки данных.
};

}}}}      // namespace libs::ievents::props::hardware

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::hardware::InfoCPUEvent);
