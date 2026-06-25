#pragma once
/**
\file       iincludes.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::io
{
/// Структура для группировки параметров инициализации интерфейса по управлению оптимизированными алгоритмами
struct TInit final {
  explicit TInit (const syn::CpuExts& ext = syn::CpuExts::usual) :
    ext_ (ext)
  {
  }

  syn::CpuExts ext_ = syn::CpuExts::usual;
};

/// Интерфейс для управления всеми доступными в системе оптимизированными алгоритмами
class IOptim
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IOptim)

  /// Функция возвращает по запросу реализацию оптимизированного алгоритма
  virtual hioptim get (const qoptim& info) = 0;

  /// Функция обновляет реализацию оптимизированного алгоритма
  virtual void sync_impl (const TInit& iinfo) = 0;

  protected:
  IOptim ()          = default;
  virtual ~IOptim () = default;
};
}   // namespace libs::optim::io
