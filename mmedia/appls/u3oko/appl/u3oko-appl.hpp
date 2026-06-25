#pragma once
/**
\file       u3oko-appl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3oko
*/

namespace appls::u3oko::appl
{
/// Реализация модуля приложения для тестирования производительности системы
class U3OkoAppl final : public ::libs::ilink::appl::root::RootModule
{
  public:
  U3OkoAppl ();
  virtual ~U3OkoAppl () = default;

  private:
  //  internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::root::RootModule)

  // RootModule override
  virtual void appl_init_int (const syn::InitApplication& info) override;
  virtual void init_links_int (const syn::InitApplication& info) override;
  virtual void update_catch_funcs_int () override;
  virtual bool appl_deinit_int () override;

  // BaseModule overrides
  virtual auto get_recv_link_int () -> recv_links_type override;
};
}   // namespace appls::u3oko::appl
