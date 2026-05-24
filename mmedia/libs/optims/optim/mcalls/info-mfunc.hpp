#pragma once
/**
\file       info-mfunc.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::mcalls
{
/// Структура для группировки параметров распределенного вызова
struct InfoMFunct final {
  explicit InfoMFunct (io::hioptim* pfunct = nullptr)
  {
    pfunc_           = pfunct;
    dest_div_koeffy_ = 1;
    dest_mul_koeffy_ = 1;
  }

  ~InfoMFunct ()
  {
  }

  void
  reset ()
  {
    pfunc_           = nullptr;
    dest_div_koeffy_ = 1;
    dest_mul_koeffy_ = 1;

    src_align_.reset ();
    dst_align_.reset ();
  }

  bool
  is_empty () const
  {
    return nullptr == pfunc_ || !pfunc_->self_test () ? true : false;
  }

  void
  self_test () const
  {
    src_align_.self_test ();
    dst_align_.self_test ();
  }

  io::hioptim*  pfunc_;             //< рабочая функция
  AlignProperty src_align_;         //< Выравнивание  по горизонтали в пикселях для всех буферов
  AlignProperty dst_align_;         //< Выравнивание по горизонтали в пикселях для всех буферов
  std::uint32_t dest_div_koeffy_;   //< Коэффициент деления по вертикали буфера назначения
  std::uint32_t dest_mul_koeffy_;   //< Коэффициент умножения по вертикали буфера назначения
};
}   // namespace libs::optim::mcalls
