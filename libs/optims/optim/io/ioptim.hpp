#pragma once
/**
\file       iincludes.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      Внешний интерфейс включения модуля.
*/

namespace libs { namespace optim { namespace io {
/**
\brief  Структура для группировки параметров инициализации интерфейса по управлению оптимизированными алгоритмами.
*/
struct TInit
{
  TInit () :
    ext_ (::libs::helpers::sys::cpu::TypeExtCpu::usual)
  {}


  ::libs::helpers::sys::cpu::TypeExtCpu ext_;
};
/**
\brief  Интерфейс для управления всеми доступными в системе оптимизированными алгоритмами.
*/
class IOptim
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IOptim);
  /**
  \brief  Функция возвращает по запросу реализацию оптимизированного алгоритма.
  */
  virtual hioptim get (const qoptim& _info) = 0;
  /**
  \brief  Функция обновляет реализацию оптимизированного алгоритма.
  */
  virtual void update (const TInit& _iinfo) = 0;


  protected:
  IOptim ()
  {}

  virtual ~IOptim ()
  {}
};

}}}      // namespace libs::optim::io
