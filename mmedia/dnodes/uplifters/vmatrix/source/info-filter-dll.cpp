/**
\file ???
\brief  Filter for correct image
\author Erashov Anton erashov2026@proton.me
\date 26.07.2016
*/
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dnodes::uplifters::vmatrix
{
InfoFilter::InfoFilter () :
  // y16_meffects_ (256),
  // uv16_meffects_ (256),
  m_array_stride_bufs_matrix_effect (0, 256),
  // ext_y16_meffects_ (256),
  // ext_uv16_meffects_ (256),
  m_array_stride_extended_bufs_matrix_effect (0, 256)
{
  init ();
}


void
InfoFilter::init ()
{
  ::libs::utility::checks::throw_exception ("failed");
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // parent_ = 0;
  // controller_ = 0;
  count_update_correction_value_ = 0;
  m_preSin_hue_correction.resize (256);
  m_preCos_hue_correction.resize (256);

  m_preSinCos_hue_corretion.resize (8);

  // m_enable_correct = true;
  // simd_ = ::libs::utility::sys::cpu::CpuExts::usual;
  m_enable_send  = false;
  id_            = ::libs::utility::consts::uinvalid;
  use_ext_files_ = false;

  //    count_cpu = 1;

#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  ::libs::utility::checks::throw_ifn (pfuncs_.set_cpu_ext (simd_));
  ::libs::utility::checks::throw_ifn (pfuncs2_.set_cpu_ext (simd_));

  pfunc_matrix_ = ::libs::optim::s16bit::gen::matrix::matrix_mmx;
#  endif

  rprops_ = ::libs::iproperties::helpers::create_event< props_type > (props_);
  str2props_.insert (str2prop_type::value_type (props_->get_mid (), rprops_));
#endif
}
}   // namespace dnodes::uplifters::vmatrix
