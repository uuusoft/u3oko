#pragma once
/**
\file       obj-source-impl-proxy.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.05.2017
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen
{
/// Обеспечивает загрузку выбранной реализации захвата данных в память процесса
class ObjSourceImplProxy final
{
  public:
  ObjSourceImplProxy () = default;
  ~ObjSourceImplProxy ();

  ObjSourceImplProxy (const ObjSourceImplProxy& src)            = delete;
  ObjSourceImplProxy& operator= (const ObjSourceImplProxy& src) = delete;

  void                            init (const std::string& name_impl);
  void                            clear ();
  gen_lib::ISourceImpl::raw_ptr   get_source_impl ();
  ::libs::helpers::dlls::dll_type get_source_impl_lib ();

  private:
  //  internal typess
  ::libs::helpers::dlls::dll_type   capture_lib_;           //< Библиотека с выбранной реализацией захвата данных из видеоустройства
  gen_lib::ISourceImpl::raw_ptr     impl_      = nullptr;   //< Реализация захвата, полученная из библиотеки
  gen_lib::bcreate_source_func_type func_get_  = 0;         //< Функция создания реализации из библиотеки
  gen_lib::bfree_source_func_type   func_free_ = 0;         //< Функция удаления реализации из библиотеки
};
}   // namespace dlls::sources::gen_vgen
