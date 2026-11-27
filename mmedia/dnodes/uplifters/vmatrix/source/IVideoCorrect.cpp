/**
\file ???
\brief  Filter for correct image
\author Erashov Anton erashov2026@proton.me
\date 26.07.2016
*/
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

// old shit
namespace dnodes::uplifters::vmatrix
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
Filter::EnableCorrect (InfoFilter* finfo, bool enable_process)
{
  ::libs::utility::checks::throw_exception ("failed");
  return false;
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  finfo->m_enable_correct = enable_process;
  // finfo->m_enable_correct = false;
#  endif
}

bool
Filter::SetDirForMatrixEffect (
  InfoFilter* finfo,
  const char* dir)
{
  ::libs::utility::checks::throw_exception ("failed");
  return false;
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // bool  loc_need_refresh_files = false;

#    ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  if ((0 == dir) && !finfo->m_dir_files_matrix_effect.empty ())
  {
    finfo->m_dir_files_matrix_effect.clear ();
    loc_need_refresh_files = true;
  }
  else if (dir && (finfo->m_dir_files_matrix_effect != dir))
  {
    finfo->m_dir_files_matrix_effect = dir;
    loc_need_refresh_files           = true;
  }
#    endif
  // if ( loc_need_refresh_files)
  {
    load_images (finfo);
  }
#  endif
}
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
Filter::GetCorrectValueFromIndex (
  InfoFilter*                 finfo,
  consts::TCorrectionImageVal index_value,
  float*                      value)
{
  *value = finfo->m_array_correction_values[index_value];
}
#  endif
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
Filter::GetNowAverageLevel (
  InfoFilter* finfo,
  float*      average_level)
{
  *average_level = finfo->m_now_average_frame;
}
#  endif
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
Filter::SetInternalValue (
  InfoFilter*                finfo,
  consts::TIntlValitransform index_value,
  unsigned long              int_value,
  float                      float_value)
{
  bool loc_required_clear_noise_buf = false;

#    ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  if ((consts::tivciUserYAndUVCorrection == index_value) &&
      (finfo->int_uints_[index_value] != int_value))
  {
    finfo->m_required_init_graduent_buf = true;
    // 29.01.2016 при изменении типа граф. преобразования сбрасываем текущее смещение в буфере
    finfo->m_current_offset_graduent_transform = 0.0F;
  }
#    endif
#    ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // 26.01.2016
  if ((consts::tivciFlagEnableNoiseRemove2 == index_value) ||
      (consts::active_ForColor == index_value) ||
      (consts::active_ForColor == index_value) ||
      (consts::tivciFlagEnableCycleCountureNoisemove2 == index_value) ||
      (consts::tivciFlagEnableGeneralNoiseRemove == index_value) ||
      (consts::tivciFlagEnableCoditionBufferForNoiseRemove == index_value) ||
      //( consts::tivciAdaptiveHistogramCorrection == index_value ) ||
      // 27.01.2016
      (consts::tivciAdaptiveCorrection == index_value))
  {
    loc_required_clear_noise_buf = true;
  }
#    endif
#    ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  if ((loc_required_clear_noise_buf) &&
      ((finfo->int_floats_[index_value] != float_value) ||
       (finfo->int_uints_[index_value] != int_value)))
  {
    finfo->m_add_noise_remove_var2_Ybuf.set_flag (::utils::dbufs::BufFlags::empty, true);
    finfo->m_add_noise_remove_var2_UVbuf.set_flag (::utils::dbufs::BufFlags::empty, true);

    finfo->m_add_noise_remove_before_correction_var2_Ybuf.set_flag (::utils::dbufs::BufFlags::empty, true);
    finfo->m_add_noise_remove_before_correction_var2_UVbuf.set_flag (::utils::dbufs::BufFlags::empty, true);
    finfo->m_prevoise_for_noise_remove_Ybuf.set_flag (::utils::dbufs::BufFlags::empty, true);

    // 10.01.2016
    for (utils::dbufs::video::IVideoBuf& current_buf : finfo->bufs_var2_)
    {
      current_buf.set_flag (::utils::dbufs::BufFlags::empty, true);
    }
    for (utils::dbufs::video::IVideoBuf& current_buf : finfo->bufs_before_var2_)
    {
      current_buf.set_flag (::utils::dbufs::BufFlags::empty, true);
    }
    for (utils::dbufs::video::IVideoBuf& current_buf : finfo->bufs_prev_)
    {
      current_buf.set_flag (::utils::dbufs::BufFlags::empty, true);
    }
  }
#    endif
#    ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  if (consts::tivciRequestResetInternalBuffers == index_value)
  {
    finfo->m_add_noise_remove_var2_Ybuf.u1pdate_dim (16, 1);
    finfo->m_add_noise_remove_var2_UVbuf.u1pdate_dim (16, 1);

    finfo->m_add_noise_remove_before_correction_var2_Ybuf.u1pdate_dim (16, 1);
    finfo->m_add_noise_remove_before_correction_var2_UVbuf.u1pdate_dim (16, 1);

    finfo->m_prevoise_for_noise_remove_Ybuf.u1pdate_dim (16, 1);

    // 10.01.2016
    for (utils::dbufs::video::IVideoBuf& current_buf : finfo->bufs_var2_)
    {
      current_buf.u1pdate_dim (16, 1);
    }
    for (utils::dbufs::video::IVideoBuf& current_buf : finfo->bufs_before_var2_)
    {
      current_buf.u1pdate_dim (16, 1);
    }
    for (utils::dbufs::video::IVideoBuf& current_buf : finfo->bufs_prev_)
    {
      current_buf.u1pdate_dim (16, 1);
    }
  }
#    endif
  finfo->int_uints_[index_value]  = int_value;
  finfo->int_floats_[index_value] = float_value;
  return hr;
}
#  endif
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
Filter::GetInternalValue (
  InfoFilter*                finfo,
  consts::TIntlValitransform index_value,
  unsigned long*             int_value,
  float*                     float_value)
{
  *int_value   = finfo->int_uints_[index_value];
  *float_value = finfo->int_floats_[index_value];
}
#  endif
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
Filter::SetTempDisabledAdaptiveCorrection (
  InfoFilter* finfo,
  bool        temp)
{
  finfo->m_temp_disabled_adaptive_correction = temp;
}
#  endif
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
Filter::NeedRecivingEventAboutFirstAverageValue (InfoFilter* finfo)
{
  finfo->m_need_setting_average_level        = true;
  finfo->m_temp_disabled_adaptive_correction = true;
}
#  endif
bool
Filter::SendCorrectMessage (
  InfoFilter* finfo,
  bool        enable_send)
{
  finfo->m_enable_send = enable_send;
  return true;
}

bool
Filter::SetParentObject (
  InfoFilter*                    finfo,
  core::graph::controller::CObj* object)
{
  finfo->controller_ = object;
  return true;
}

bool
Filter::SetIdCamera (
  InfoFilter*   finfo,
  unsigned long cid,
  unsigned long type_camera)
{
  finfo->id_ = cid;
  return true;
}
#endif
}   // namespace dnodes::uplifters::vmatrix
