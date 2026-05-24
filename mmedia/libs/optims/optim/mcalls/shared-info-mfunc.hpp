#pragma once
/**
\file       shared-info-mfunc.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::mcalls
{
/// Данные, которые разделяются между всеми рабочими потоками при вызове
class SharedInfoMFunct final
{
  public:
  //  ext types
  using barier_type     = std::barrier<>;
  using barier_ptr_type = std::unique_ptr< barier_type >;

  SharedInfoMFunct () :
    exit_request_ (false)
  {
  }

  ~SharedInfoMFunct ()
  {
  }

  SharedInfoMFunct (const SharedInfoMFunct& src)            = delete;
  SharedInfoMFunct& operator= (const SharedInfoMFunct& src) = delete;

  std::atomic_bool exit_request_;   //< Флаг запроса на выход
  barier_ptr_type  bstart_;         //< Барьер старта
};
}   // namespace libs::optim::mcalls
