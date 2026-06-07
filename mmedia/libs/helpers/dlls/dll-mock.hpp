#pragma once
/**
\file       dll-mock.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
namespace libs::helpers::dlls
{
/// Тип для гарантированного удеражания в памяти всех загруженных модулей, даже если они уже не нужны
/// Количество расхода памяти при этом незначительно (несколько десятков мегабайт в худшем случае)
/// И при этом мы избегаем сбоев при работе с объектами, порожденными различными модулями
struct DllMock final {
  bool
  is_loaded () const
  {
    return true;
  }

  void
  load (const std::string& path, int)
  {
  }

  void
  unload ()
  {
  }

  operator bool () const
  {
    return true;
  }
};

#if (U3_BUILD_MODULES_AS_LIBS == 1)
using dll_type = DllMock;
#else
using dll_type = boost::dll::shared_library;
#endif
}   // namespace libs::helpers::dlls
