#pragma once
/**
\file       ioptim-proxy.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_proxy_libs
*/

namespace libs::proxy
{
/// Тип для доступа к реализации интерфейса по управлению оптимизированными алгоритмами
/// Реализован через шаблон проектирования "одиночка в строго смысле слова в пределах процесса"
class IOptimProxy final
{
  public:
  //  ext types
  using create_ioptim_func_type = ::libs::optim::io::IOptim::raw_ptr ();

  U3_ADD_POINTERS_TO_SELF (IOptimProxy)
  U3_ADD_DELETE_MOVE_COPY (IOptimProxy)

  static IOptimProxy::raw_ptr        instance (const std::string& dll_path);
  ::libs::optim::io::IOptim::raw_ptr impl ();

  private:
  explicit IOptimProxy (const std::string& dll_path);
  ~IOptimProxy () = default;

  std::function< create_ioptim_func_type > creator_;   //<
  ::libs::utility::dlls::dll_type          lib_;       //<
};
}   // namespace libs::proxy
