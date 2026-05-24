/**
\file       correct-image-impl.cpp
\date       01.01.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcorrect_vdd
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../vcorrect-includes_int.hpp"
#include "correct-image-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::uplifters::vcorrect::soft
{
CorrectImageImpl::CorrectImageImpl () :
  props_ (nullptr)
{
  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  pthreads_        = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
  mfunc_const_add_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CAddConstAlg::val_key));
  mfunc_sat2byte_  = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CSat2ByteAlg::val_key));
  mfunc_grad_func_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CGraduent1Alg::val_key));

  std::int16_t cindx = 0;
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


CorrectImageImpl::~CorrectImageImpl ()
{
}


void
CorrectImageImpl::change_state_int (bool enable)
{
}


void
CorrectImageImpl::update_correction_property_int (const syn::VideoCorrectProp::raw_ptr info)
{
  U3_LOG_DATA_DATA ("update correction properties:" + syn::VideoCorrectProp::gen_get_mid ());
  props_ = info;

  const float sval = ::libs::helpers::utils::ret_check_bound (props_->saturation_.first, -1.0f, 1.0f);
  if (0.0f != sval)
  {
    auto updatefunc = [sval] (std::int32_t i) -> std::int16_t {
      auto val = sval > 0.0f ? U3_CAST_INT16 (i + (255.0f * sval) * ((255.0f - i) / 255.0f)) :
                               U3_CAST_INT16 (i + (255.0f * sval) * (i / 255.0f));
      ::libs::helpers::utils::check_bound< std::int16_t > (val, 0, 255);
      return val;
    };

    for (std::int32_t i = 0; i < U3_CAST_INT32 (saturations_.size ()); ++i)
    {
      saturations_[i] = updatefunc (i);
    }
  }

  const auto cval = ::libs::helpers::utils::ret_check_bound (props_->contrast_.first, -1.0f, 1.0f);
  if (0.0f != cval)
  {
    for (std::int32_t i = 0; i < U3_CAST_INT32 (contrasts_.size ()); ++i)
    {
      std::int16_t val = U3_CAST_INT16 (i * std::pow (U3_CAST_FLOAT (i), props_->contrast_.first / 30.0f));
      ::libs::helpers::utils::check_bound< std::int16_t > (val, 0, 255);
      contrasts_[i] = val;
    }
  }

  const auto hval = ::libs::helpers::utils::ret_check_bound (props_->hue_.first, -1.0f, 1.0f);
  if (0.0f != hval)
  {
    const std::int16_t off_val = props_->hue_.first * 127;
    for (std::int32_t i = 0; i < U3_CAST_INT32 (hues_.size ()); ++i)
    {
      std::int16_t val = i + off_val;
      val              = val < 0 ? 255 + val : (val > 255 ? val - 255 : val);
      ::libs::helpers::utils::check_bound< std::int16_t > (val, 0, 255);
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
  // correct bright
  if (0.0f != props_->bright_.first)
  {
    bright_correct (*l16s);
  }
  // correct contrast
  if (0.0f != props_->contrast_.first)
  {
    graduent_correct (*l16s, contrasts_);
  }
  // correct hue
  if (0.0f != props_->hue_.first && h16s && !h16s->get_flag (::utils::dbufs::BufFlags::empty))
  {
    graduent_correct (*h16s, hues_);
  }
  // correct saturation
  if (0.0f != props_->saturation_.first && s16s && !s16s->get_flag (::utils::dbufs::BufFlags::empty))
  {
    graduent_correct (*s16s, saturations_);
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
}   // namespace dlls::uplifters::vcorrect::soft
