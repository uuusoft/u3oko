#pragma once
/**
\file       info-cpu-event.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::hardware::syn
{
using CpuExts = ::libs::utility::sys::cpu::CpuExts;
}

namespace libs::events_base::props::hardware
{
/// События для хранения и передачи свойств, связанных с CPU
/// Тип используемого расширения, количество процессоров etc
class InfoCPUEvent : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (InfoCPUEvent)
  U3_ADD_MAKE_SHARED_THIS (InfoCPUEvent)
  U3_ADD_DELETE_MOVE_COPY (InfoCPUEvent)

  explicit InfoCPUEvent (
    const Acessor&                = Acessor (0),
    const syn::CpuExts& simd      = syn::CpuExts::usual,
    const std::uint32_t count_cpu = 0);

  virtual ~InfoCPUEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/hardware/info-cpu-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_cpu_type () const -> syn::CpuExts;
  auto set_cpu_type (const syn::CpuExts& type) -> void;
  auto get_cpu_count () const -> std::uint32_t;
  auto set_cpu_count (const std::uint32_t count_cpu) -> void;

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual void sync_txt2val_int () override;
  virtual void sync_val2txt_int () override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  std::string   text_simd_;                         //< Текстовое представление simd
  syn::CpuExts  simd_      = syn::CpuExts::usual;   //< Тип simd, который будет использоваться
  std::uint32_t count_cpu_ = 0;                     //< Количество потоков, которое будет использовано в пуле для обработки данных
};
}   // namespace libs::events_base::props::hardware

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::hardware::InfoCPUEvent);
