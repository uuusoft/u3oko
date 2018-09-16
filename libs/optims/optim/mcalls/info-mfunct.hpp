#pragma once
/**
\file       info-mfunct.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

namespace libs { namespace optim { namespace mcalls {
/**
\brief  Структура для группировки параметров распределенного вызова.
*/
struct InfoMFunct
{
  explicit InfoMFunct (io::hioptim* _pfunct = nullptr)
  {
    pfunct_          = _pfunct;
    dest_div_koeffy_ = 1;
    dest_mul_koeffy_ = 1;
  }

  ~InfoMFunct ()
  {}

  void
  reset ()
  {
    pfunct_          = nullptr;
    dest_div_koeffy_ = 1;
    dest_mul_koeffy_ = 1;

    src_align_.reset ();
    dst_align_.reset ();
    return;
  }

  bool
  is_empty () const
  {
    return nullptr == pfunct_ || !pfunct_->self_test () ? true : false;
  }

  bool
  self_test () const
  {
    if (!src_align_.self_test () || !dst_align_.self_test ())
      {
        return false;
      }

    return true;
  }

  io::hioptim*  pfunct_;               //< Собственно рабочая функция
  AlignProperty src_align_;            //< Выравнивание  по горизонтали в пикселях для всех буферов.
  AlignProperty dst_align_;            //< Выравнивание по горизонтали в пикселях для всех буферов.
  std::size_t   dest_div_koeffy_;      //< Коэффициент деления по вертикали буфера назначения.
  std::size_t   dest_mul_koeffy_;      //< Коэффициент умножения по вертикали буфера назначения.
};

}}}      // namespace libs::optim::mcalls
