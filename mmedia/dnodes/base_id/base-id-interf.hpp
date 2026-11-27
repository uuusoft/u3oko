#pragma once
/**
\file       base-id-interf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       19.07.2018
*/

namespace dnodes::base_id
{
/// Реализация интерфейса фильтра "базовый идентификатор" для взаимодействия с другими фильтрами в графе
class BaseIdInterf final : public ::libs::events_base::runtime::interf::interfaces::IBaseId
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (BaseIdInterf)

  BaseIdInterf ()          = default;
  virtual ~BaseIdInterf () = default;

  auto is_correction_property_update () const -> bool;
  auto get_base_property () const -> syn::BaseIdProp::craw_ptr;

  private:
  virtual auto change_state_int (bool) -> void override;
  virtual auto update_property_int (const ::libs::events::IEvent::craw_ptr) -> void override;
  virtual auto get_module_infos_int (const syn::off_buf_type indx_buf) const -> buf_infos_type override;
  virtual auto get_source_name_int () const -> const syn::source_name_type& override;

  mutable bool    update_ { false };   //<
  syn::BaseIdProp props_;              //<
};
}   // namespace dnodes::base_id
