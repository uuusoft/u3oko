/**
\file       base-id-interf.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.03.2022
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "base_id-includes_int.hpp"
#include "base-id-interf.hpp"

namespace dnodes::base_id
{
auto
BaseIdInterf::is_correction_property_update () const -> bool
{
  return update_;
}


auto
BaseIdInterf::get_base_property () const -> syn::BaseIdProp::craw_ptr
{
  update_ = false;
  return &props_;
}


void
BaseIdInterf::change_state_int (bool enable)
{
}


void
BaseIdInterf::update_property_int (const syn::IEvent::craw_ptr info)
{
  props_.copy (info);
  update_ = true;
}


auto
BaseIdInterf::get_module_infos_int (const syn::off_buf_type indx_buf) const -> BaseIdInterf::buf_infos_type
{
  buf_infos_type ret;

  for (const auto& info : props_.buf2modules_)
  {
    if (indx_buf == info.indx_buf_)
    {
      ret.push_back (&info);
    }
  }
  return ret;
}


auto
BaseIdInterf::get_source_name_int () const -> const syn::source_name_type&
{
  return props_.source_name_;
}
}   // namespace dnodes::base_id
