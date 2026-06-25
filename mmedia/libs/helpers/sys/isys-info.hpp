#pragma once
/**
\file       isys-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::sys
{
/// Перечисления типов различных частей аппаратного обеспечения
enum class TypeInfo : std::uint32_t
{
  os      = 0x00,   //< Общая информация о ОС
  memory  = 0x01,   //< Колиество ОП в системе
  display = 0x02,   //< Параметры дисплея в системе
  cpu     = 0x03,   //< Параметры процессоров системы
  unknown = 0xFF    //< Не определенно для общности
  // cpu_speed   = 0x04, //< Параметры скорости процессоров в системе
};

/// Интерфейс для получения информации об аппаратном обеспечении системы и его возможностях
class ISysInfo
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ISysInfo)

  virtual ~ISysInfo () = default;

  /// Получить текстовое описание к подсистеме
  virtual std::string get (const TypeInfo& type) const = 0;

  /// Получить количество процессоров в системе
  virtual std::int16_t count_cpu () const = 0;
};
}   // namespace libs::helpers::sys
