#pragma once
/**
\file       isys-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace sys {
/**
  \brief  Перечисления типов различных частей аппаратного обеспечения.
  */
enum struct TypeInfo
{
  os      = 0,      //< Общая информация о ОС.
  memory  = 1,      //< Колиество ОП в системе.
  display = 2,      //< Параметры дисплея в системе.
  cpu     = 3       //< Параметры процессоров системы.
  //cpu_speed   = 4 //< Параметры скорости процессоров в системе.
};
/**
  \brief  Интерфейс для получения информации об аппаратном обеспечении системы и его возможностях.
  */
class ISysInfo
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ISysInfo);

  virtual ~ISysInfo ()
  {}

  /// Получить текстовое описание к подсистеме.
  virtual std::string get (const TypeInfo& _type) const = 0;
  /// Получить количество процессоров в системе.
  virtual short count_cpu () const = 0;
};

}}}      // namespace libs::helpers::sys
