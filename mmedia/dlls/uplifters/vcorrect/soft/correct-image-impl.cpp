/**
\file       correct-image-impl.cpp
\date       01.01.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_vcorrect_vdd
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../vcorrect-includes_int.hpp"
#include "correct-image-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::uplifters::vcorrect::soft
{
CorrectImageImpl::CorrectImageImpl ()
{
  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  pthreads_        = ::libs::iproperties::helpers::get_shared_prop_os ()->get_mcalls_lockfree ();
  mfunc_const_add_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CAddConstAlg::val_key));
  mfunc_sat2byte_  = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CSat2ByteAlg::val_key));
  mfunc_grad_func_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CGraduent1Alg::val_key));

  std::int32_t cindx = 0;
  std::generate (
    contrasts_.begin (),
    contrasts_.end (),
    [&cindx] () { return cindx++; });

  cindx = 0;
  std::generate (
    saturations_.begin (),
    saturations_.end (),
    [&cindx] () { return cindx++; });

  cindx = 0;
  std::generate (
    hues_.begin (),
    hues_.end (),
    [&cindx] () { return cindx++; });
}


void
CorrectImageImpl::change_state_int (bool enable)
{
}


void
CorrectImageImpl::update_correction_property_int (const syn::VideoCorrectProp::raw_ptr info)
{
  U3_LOG_DATA_DATA ("update correction properties:" + STOLOG (syn::VideoCorrectProp::gen_get_mid ()));
  props_ = info;

  const float sval = ::libs::helpers::utils::ret_check_bound (props_->saturation_.first, -1.0F, 1.0F);
  if (0.0F != sval)
  {
    auto updatefunc = [sval] (std::int32_t i) -> std::int16_t {
      auto val = sval > 0.0F ? U3_CAST_INT16 (i + (consts::bound_gradient_val * sval) * ((consts::bound_gradient_val - i) / consts::bound_gradient_val)) :
                               U3_CAST_INT16 (i + (consts::bound_gradient_val * sval) * (i / consts::bound_gradient_val));
      ::libs::helpers::utils::check_bound< std::int16_t > (val, 0, consts::max_graduent_val);
      return val;
    };

    for (std::int32_t i = 0; i < U3_CAST_INT32 (saturations_.size ()); ++i)
    {
      saturations_[i] = updatefunc (i);
    }
  }

  const auto cval = ::libs::helpers::utils::ret_check_bound (props_->contrast_.first, -1.0F, 1.0F);
  if (0.0F != cval)
  {
    for (std::int32_t i = 0; i < U3_CAST_INT32 (contrasts_.size ()); ++i)
    {
      auto val = U3_CAST_INT16 (i * std::pow (U3_CAST_FLOAT (i), props_->contrast_.first / 30.0F));
      ::libs::helpers::utils::check_bound< std::int16_t > (val, 0, consts::max_graduent_val);
      contrasts_[i] = val;
    }
  }

  const auto hval = ::libs::helpers::utils::ret_check_bound (props_->hue_.first, -1.0F, 1.0F);
  if (0.0F != hval)
  {
    const std::int16_t off_val = props_->hue_.first * 127;
    for (std::int32_t i = 0; i < U3_CAST_INT32 (hues_.size ()); ++i)
    {
      std::int16_t val = i + off_val;
      val              = val < 0 ? 255 + val : (val > 255 ? val - 255 : val);
      ::libs::helpers::utils::check_bound< std::int16_t > (val, 0, consts::max_graduent_val);
      hues_[i] = val;
    }
  }
}


bool
CorrectImageImpl::process_int (
  syn::IVideoBuf::raw_ptr h16s,
  syn::IVideoBuf::raw_ptr s16s,
  syn::IVideoBuf::raw_ptr l16s)
{
  if (!l16s || l16s->get_flag (::utils::dbufs::BufFlags::empty))
  {
    U3_LOG_DATA_WRN ("skip software correction, empty light buf");
    return false;
  }
  // correct contrast
  if (0.0F != props_->contrast_.first)
  {
    graduent_correct (*l16s, contrasts_);
  }
  // correct hue
  if (0.0F != props_->hue_.first && h16s && !h16s->get_flag (::utils::dbufs::BufFlags::empty))
  {
    graduent_correct (*h16s, hues_);
  }
  // correct saturation
  if (0.0F != props_->saturation_.first && s16s && !s16s->get_flag (::utils::dbufs::BufFlags::empty))
  {
    graduent_correct (*s16s, saturations_);
  }
  // correct bright
  if (0.0F != props_->bright_.first)
  {
    bright_correct (*l16s);
  }

  if (props_->short2byte_)
  {
    syn::IVideoBuf::raw_ptr bufs[] = {
      h16s,
      s16s,
      l16s
    };

    for (auto cbuf : bufs)
    {
      if (!cbuf || cbuf->get_flag (::utils::dbufs::BufFlags::empty))
      {
        continue;
      }
      sat2byte_correct (*cbuf);
    }
  }
  return true;
}


void
CorrectImageImpl::bright_correct (syn::IVideoBuf& y16s)
{
  //  Если нужно корректируем смещение освещености в соотвествии со средним значением в кадре
  //  т.е. если яркость отлична от заданное более чем на указанный парог изменяем коррекцию освещенности
  auto bright = U3_CAST_INT16 (255 * props_->bright_.first);
  U3_LOG_DATA_DATA (VTOLOG (bright) + VTOLOG (props_->bright_.first));
  if (0 == bright)
  {
    return;
  }

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  if (finfo->int_uints_[consts::tivciAdaptiveCorrection])
  {
    float loc_diff_correction     = finfo->props_.adaptive_ - finfo->m_now_average_frame;
    float loc_abs_diff_correction = loc_diff_correction < 0.0F ? -loc_diff_correction : loc_diff_correction;

    if (loc_abs_diff_correction > 0.001f)
    {
      // 21.09.2016 - add speed koeff
      const float loc_speed_change = 1.0F;

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

  cinfo.dsts_.emplace_back (&y16s, "y16s dlls::uplifters::vcorrect::soft");
  cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;
  cinfo.params_.consts_.push_back (brights);

  ::libs::optim::mcalls::MTFuncInfo tfunc (&mfunc_const_add_);

  pthreads_->mthreads_call (
    *id_node_graph_,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}


void
CorrectImageImpl::graduent_correct (syn::IVideoBuf& buf, const graduent_array_type& vals2vals)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.emplace_back (&buf, "buf dlls::uplifters::vcorrect::soft");
  cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;
  cinfo.params_.consts_.emplace_back (&vals2vals[0]);
  cinfo.params_.ints_.emplace_back (U3_CAST_INT32 (vals2vals.size ()));
  // U3_XLOG_DEV (VTOLOG (cinfo.params_.ints_[0]) + VTOLOG (U3_CAST_INT32 (vals2vals.size ())));

  ::libs::optim::mcalls::MTFuncInfo tfunc (&mfunc_grad_func_);

  pthreads_->mthreads_call (
    *id_node_graph_,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}


void
CorrectImageImpl::sat2byte_correct (syn::IVideoBuf& buf)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.emplace_back (&buf, "buf dlls::uplifters::vcorrect::soft");
  cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;

  ::libs::optim::mcalls::MTFuncInfo tfunc (&mfunc_sat2byte_);
  pthreads_->mthreads_call (
    *id_node_graph_,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::uplifters::vcorrect::soft
