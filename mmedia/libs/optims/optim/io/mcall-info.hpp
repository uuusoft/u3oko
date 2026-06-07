#pragma once
/**
\file       mcall-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::io
{
/// Структрура для группировки параметров, которые передаются функции при вызове в рабочем потоке
struct MCallInfo final {
  //  ext types
  using sources_type = std::vector< ::libs::optim::io::ProxyBuf >;
  using dests_type   = std::vector< ::libs::optim::io::ProxyBuf >;

  MCallInfo ()
  {
    srcs_.reserve (4);
    dsts_.reserve (4);
  }

  ~MCallInfo () = default;

  std::uint32_t indx_thread_     = 0;   //< Индекс потока, которому принадлежит данная копия структуры
  std::uint32_t count_threads_   = 0;   //< Количество рабочих потоков, используемых при данном вызове
  std::uint32_t full_height_src_ = 0;   //< Полная высота буфера источника, не может быть получена простым перемножением количества потоков на высоту части, т.к. высоты разные
  std::uint32_t full_height_dst_ = 0;   //< Полная высота буфера назначения, не может быть получена простым перемножением количества потоков на высоту части, т.к. высоты разные
  sources_type  srcs_;                  //< Список буферов-источников данного потока
  dests_type    dsts_;                  //< Список буферов-назначений данного потока
  MTFuncParams  params_;                //< Дополнительные произвольные параметры к функции
};

/// Тип функции для вызова алгоритма в рабочем потоке
using mtcall_func = void (*) (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::io
