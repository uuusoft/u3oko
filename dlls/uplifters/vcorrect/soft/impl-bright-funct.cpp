//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       impl-bright-funct.cpp
\brief      Filter for correct image
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcorrect_vdd
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "impl.hpp"

namespace dlls { namespace uplifters { namespace vcorrect { namespace soft {

void
Impl::bright_correct (IVideoBuff& y16_buff)
{
  //  Если нужно корректируем смещение освещености в соотвествии со средним значением в кадре
  //  т.е. если яркость отлична от заданное более чем на указанный парог изменяем коррекцию освещенности
  short _bright = UUU_ICAST_SHORT (255 * props_->bright_);

  if (0 == _bright)
    {
      return;
    }

  XULOG_TRACE ("Filter::bright_correct:: real work");
  TEMP_DISABLED_UASSERT (0);
#if 0
    if (finfo->int_uints_[consts::tivciAdaptiveCorrection] )
    {
      float loc_diff_correction = finfo->props_.adaptive_ - finfo->m_now_average_frame;
      float loc_abs_diff_correction = loc_diff_correction < 0.0f ? -loc_diff_correction : loc_diff_correction;

      if ( loc_abs_diff_correction > 0.001f )
      {
        // 21.09.2016 - add speed koeff
        const float loc_speed_change = 1.0f;

        finfo->m_add_brights_now = ::libs::helpers::utils::ret_check_bound ( finfo->m_add_brights_now + ( loc_speed_change * loc_diff_correction) / loc_abs_diff_correction, -255, 255 );
      }

      if (!finfo->m_temp_disabled_adaptive_correction)
      {
        _bright = s1tatic_cast<short>( _bright + finfo->m_add_brights_now);
        base_functs::c1heck_bound<short> ( _bright, -255, 255 );
      }
    }
#endif

  UUU_DEFAULT_ALIGNED
  const short _brights[8] = {
    _bright, _bright, _bright, _bright, _bright, _bright, _bright, _bright
  };

  MCallInfo _cinfo;

  _cinfo.dsts_.push_back (ProxyBuff (&y16_buff));
  _cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;
  _cinfo.params_.consts_.push_back (_brights);

  ::libs::optim::mcalls::InfoMFunct _tfunct (&const_add_);
  pthreads_->mcall (_tfunct, _cinfo);
  return;
}

}}}}      // namespace dlls::uplifters::vcorrect::soft
