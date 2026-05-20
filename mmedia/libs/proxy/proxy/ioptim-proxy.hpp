#pragma once
/**
\file       ioptim-proxy.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    uuu_proxy
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

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IOptimProxy)

  IOptimProxy (const IOptimProxy& src)            = delete;
  IOptimProxy& operator= (const IOptimProxy& src) = delete;

  static IOptimProxy::raw_ptr        instance (const std::string& dll_path);
  ::libs::optim::io::IOptim::raw_ptr impl ();

  private:
  explicit IOptimProxy (const std::string& dll_path);

  ~IOptimProxy ();

  boost::function< create_ioptim_func_type > creator_;   //<
  ::libs::helpers::dlls::dll_type            lib_;       //<
};
}   // namespace libs::proxy
