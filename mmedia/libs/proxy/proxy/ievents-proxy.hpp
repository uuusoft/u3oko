#pragma once
/**
\file       ievents-proxy.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::proxy
{
/// Тип для доступа к реализации интерфейса для хранения событий системы
/// Реализован через шаблон проектирования "одиночка в строго смысле слова в пределах процесса"
class IEventsProxy final
{
  public:
  //  ext types
  using create_func_type       = ::libs::events::io::IEvents::raw_ptr ();
  using boost_create_func_type = std::function< create_func_type >;

  U3_ADD_POINTERS_TO_SELF (IEventsProxy)
  U3_ADD_DELETE_MOVE_COPY (IEventsProxy)

  static auto instance (const std::string& dll_path) -> IEventsProxy::raw_ptr;
  auto        impl () -> ::libs::events::io::IEvents::raw_ptr;

  private:
  explicit IEventsProxy (const std::string& dll_path);
  ~IEventsProxy () = default;

  boost_create_func_type          creator_;   //< Функция создания релизации через dll
  ::libs::utility::dlls::dll_type lib_;       //<
};
}   // namespace libs::proxy
