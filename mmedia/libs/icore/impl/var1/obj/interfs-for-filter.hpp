#pragma once
/**
\file       interfs-for-filter.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj
{
struct InterfsForFilter final {
  InterfsForFilter ()
  {
  }

  ~InterfsForFilter ()
  {
  }

  void
  check () const
  {
    U3_CHECK (!lib_name_.empty (), "failed, lib name empty");
  }

  std::string lib_name_;   //<
};
}   // namespace libs::icore::impl::var1::obj
