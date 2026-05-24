#pragma once
/**
\file       info-cpu-event.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::hardware
{
/// События для хранения и передачи свойств, связанных с CPU
/// Тип используемого расширения, количество процессоров etc
class InfoCPUEvent : public ievents::Event
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (InfoCPUEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (InfoCPUEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (InfoCPUEvent)

  explicit InfoCPUEvent (
    const Acessor&                                      = Acessor (0),
    const ::libs::helpers::sys::cpu::CpuExts& simd      = ::libs::helpers::sys::cpu::CpuExts::usual,
    const std::uint32_t                       count_cpu = 0);

  virtual ~InfoCPUEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/hardware/info-cpu-event";
    return ret;
  }

  ::libs::helpers::sys::cpu::CpuExts get_cpu_type () const;
  void                               set_cpu_type (const ::libs::helpers::sys::cpu::CpuExts& type);
  std::uint32_t                      get_cpu_count () const;
  void                               set_cpu_count (const std::uint32_t count_cpu);

  protected:
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        sync_txt2val_int () override;
  virtual void                        sync_val2txt_int () override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  std::string                        text_simd_;   //< Текстовое представление simd
  ::libs::helpers::sys::cpu::CpuExts simd_;        //< Тип simd, который будет использоваться
  std::uint32_t                      count_cpu_;   //< Количество потоков, которое будет использовано в пуле для обработки данных
};
}   // namespace libs::ievents::props::hardware

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::hardware::InfoCPUEvent);
