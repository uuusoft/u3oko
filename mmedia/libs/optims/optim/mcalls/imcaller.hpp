#pragma once
/**
\file       imcaller.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2016
\project    u3_optim_lib
*/

namespace libs::optim::mcalls
{
class IMCaller
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IMCaller)

  virtual ~IMCaller ()
  {
  }

  IMCaller (const IMCaller& src)            = delete;
  IMCaller& operator= (const IMCaller& src) = delete;

  /// Функция установки количества рабочих потоков
  /// \param[in]  count  количество рабочих потоков
  virtual void set_count_threads (std::uint16_t) = 0;
  /// Функция возращает количество рабочих потоков
  /// \return количество рабочих потоков
  virtual std::uint16_t get_count_threads () const = 0;
  /// Функция для вызова алгоритма, с использованием нескольких потоков исполнения одновременно
  virtual void mthreads_call (const ::libs::core::graph::NodeID&, const InfoMFunct&, ::libs::optim::io::MCallInfo&, syn::ExpandedTimes&, const std::uint16_t = 0) = 0;

  protected:
  IMCaller () = default;
};
}   // namespace libs::optim::mcalls
