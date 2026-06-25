#pragma once
/**
\file       iapplication-proxy.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.05.2017
\project    u3_link
*/

namespace libs::link::appl
{
class IApplication;

/// Прокси для создания объекта "подсистема" из разделяемого кода (dll/so)
class IApplicationProxy final
{
  public:
  // ext types
  using create_obj_type  = IApplication*();
  using delete_obj_type  = void (IApplication*);
  using create_func_type = std::function< create_obj_type >;
  using delete_func_type = std::function< delete_obj_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IApplicationProxy)

  IApplicationProxy (const std::string&, const std::string&);
  ~IApplicationProxy ();

  IApplicationProxy (const IApplicationProxy&)            = delete;
  IApplicationProxy& operator= (const IApplicationProxy&) = delete;

  IApplication* impl ();

  private:
  //  internal typess
  using frozen_dlls_type = ::libs::helpers::dlls::FreezerDlls;

  ::libs::helpers::dlls::dll_type lib_;              //< Держим в памяти dll принудительно вечно, до завершения работы всего процесса
  create_func_type                creator_;          //< Указатель на функтор в dll, который собственно и создает приложение
  delete_func_type                erasor_;           //< Указатель на функтор в dll, который уменьшает ссылку на созданное приложение и при необходимости удаляет его
  IApplication*                   impl_ = nullptr;   //< Созданное приложение

  static frozen_dlls_type frozen_dlls_;   //< собственно список для хранения модулей и гарантии, что они будут выгруженны последними
};
}   // namespace libs::link::appl
