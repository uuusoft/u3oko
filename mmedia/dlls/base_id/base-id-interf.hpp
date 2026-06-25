#pragma once
/**
\file       base-id-interf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       19.07.2018
\project    u3_base_id_dll
*/

namespace dlls::base_id
{
/// Реализация интерфейса фильтра "базовый идентификатор" для взаимодействия с другими фильтрами в графе
class BaseIdInterf final : public ::libs::ievents::runtime::interf::interfaces::IBaseId
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseIdInterf)

  BaseIdInterf ()          = default;
  virtual ~BaseIdInterf () = default;

  bool                      is_correction_property_update () const;
  syn::BaseIdProp::craw_ptr get_base_property () const;

  private:
  virtual void                         change_state_int (bool enable) override;
  virtual void                         update_property_int (const syn::IEvent::craw_ptr info) override;
  virtual buf2module_infos_type        get_module_infos_int (const syn::off_buf_type& indx_buf) const override;
  virtual const syn::source_name_type& get_source_name_int () const override;

  mutable bool    update_ = false;   //<
  syn::BaseIdProp props_;            //<
};
}   // namespace dlls::base_id
