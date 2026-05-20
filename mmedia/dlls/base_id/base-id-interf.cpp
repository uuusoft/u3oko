/**
\file       base-id-interf.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.03.2022
\project    u3_base_id_dll
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "base_id-includes_int.hpp"
#include "base-id-interf.hpp"

namespace dlls::base_id
{
BaseIdInterf::BaseIdInterf () :
  update_ (false)
{
}


BaseIdInterf::~BaseIdInterf ()
{
}


bool
BaseIdInterf::is_correction_property_update () const
{
  return update_;
}


syn::BaseIdProp::craw_ptr
BaseIdInterf::get_base_property () const
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


BaseIdInterf::buf2module_infos_type
BaseIdInterf::get_module_infos_int (const syn::off_buf_type& indx_buf) const
{
  buf2module_infos_type ret;

  for (const auto& info : props_.buf2modules_)
  {
    if (indx_buf == info.indx_buf_)
    {
      ret.push_back (&info);
    }
  }
  return ret;
}


const syn::source_name_type&
BaseIdInterf::get_source_name_int () const
{
  return props_.source_name_;
}
}   // namespace dlls::base_id
