/**
\file       correct-image-impl-bright-funct.cpp
\brief      Filter for correct image
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vcorrect_vdd
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../vcorrect-includes_int.hpp"
#include "correct-image-impl.hpp"

namespace dlls::uplifters::vcorrect::soft
{
void
CorrectImageImpl::bright_correct (syn::IVideoBuf& y16s)
{
  //  Если нужно корректируем смещение освещености в соотвествии со средним значением в кадре
  //  т.е. если яркость отлична от заданное более чем на указанный парог изменяем коррекцию освещенности
  std::int16_t bright = U3_CAST_INT16 (255 * props_->bright_.first);
  U3_LOG_DATA_DATA (VTOLOG (bright) + VTOLOG (props_->bright_.first));
  if (0 == bright)
  {
    return;
  }

#if 0
  if (finfo->int_uints_[consts::tivciAdaptiveCorrection])
  {
    float loc_diff_correction     = finfo->props_.adaptive_ - finfo->m_now_average_frame;
    float loc_abs_diff_correction = loc_diff_correction < 0.0f ? -loc_diff_correction : loc_diff_correction;

    if (loc_abs_diff_correction > 0.001f)
    {
      // 21.09.2016 - add speed koeff
      const float loc_speed_change = 1.0f;

      finfo->m_add_brights_now = ::libs::helpers::utils::ret_check_bound (finfo->m_add_brights_now + (loc_speed_change * loc_diff_correction) / loc_abs_diff_correction, -255, 255);
    }

    if (!finfo->m_temp_disabled_adaptive_correction)
    {
      bright = s1tatic_cast< short > (bright + finfo->m_add_brights_now);
      base_funcs::c1heck_bound< short > (bright, -255, 255);
    }
  }
#endif

  U3_ALIGN_DEFAULT
  const std::int16_t brights[16] = {
    bright, bright, bright, bright, bright, bright, bright, bright, bright, bright, bright, bright, bright, bright, bright, bright
  };

  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (&y16s, "y16s dlls::uplifters::vcorrect::soft"));
  cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;
  cinfo.params_.consts_.push_back (brights);

  ::libs::optim::mcalls::InfoMFunct tfunct (&mfunc_const_add_);

  pthreads_->mthreads_call (
    *id_node_graph_,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::uplifters::vcorrect::soft
