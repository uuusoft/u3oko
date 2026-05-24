#pragma once
/**
\file       qoptim.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::io
{
/// Структура для запроса алгоритма из библиотеки по идентификатору
struct qoptim final {
  explicit qoptim (const std::string& id = "") :
    id_ (id)
  {
  }

  ~qoptim ()
  {
  }

  void
  check () const
  {
    U3_CHECK (!id_.empty (), "empty id");
  }

  std::string id_;   //<
};
}   // namespace libs::optim::io
