#pragma once
/**
\file       obj-source-impl-proxy.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen
{
/// Обеспечивает загрузку выбранной реализации захвата данных в память процесса
class ObjSourceImplProxy final
{
  public:
  ObjSourceImplProxy (const std::string& = "");
  ~ObjSourceImplProxy ();

  U3_ADD_DELETE_MOVE_COPY (ObjSourceImplProxy)

  auto init (const std::string&) -> void;
  auto clear () -> void;
  auto get_source_impl () -> gen_lib::ISourceImpl::raw_ptr;
  auto get_source_impl_lib () -> ::libs::utility::dlls::dll_type;

  private:
  //  internal typess
  ::libs::utility::dlls::dll_type   impl_dll_;              //< Библиотека с выбранной реализацией захвата данных из устройства
  gen_lib::ISourceImpl::raw_ptr     impl_      = nullptr;   //< Реализация захвата, полученная из библиотеки
  gen_lib::bcreate_source_func_type func_get_  = 0;         //< Функция создания реализации из библиотеки
  gen_lib::bfree_source_func_type   func_free_ = 0;         //< Функция удаления реализации из библиотеки
};
}   // namespace dlls::sources::gen_vgen
