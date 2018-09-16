/**
\file       impl.cpp
\date       01.01.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vcorrect_vdd
\brief      ���������� ���������� ��������� �����������.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace uplifters { namespace vcorrect { namespace soft {

Impl::Impl () :
  props_ (nullptr)
{
  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  pthreads_   = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();
  const_add_  = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CAddConstAlg::val_key));
  sat2byte_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CSat2ByteAlg::val_key));
  grad_funct_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CGraduent1Alg::val_key));

  short _cindx = 0;
  std::generate (contrast_hsl_.begin (), contrast_hsl_.end (), [&_cindx]() { return _cindx++; });

  _cindx = 0;
  std::generate (saturation_hsl_.begin (), saturation_hsl_.end (), [&_cindx]() { return _cindx++; });
}


Impl::~Impl ()
{}


void
Impl::change_state_int (bool _enable)
{
  return;
}


void
Impl::update_property_int (const VideoCorrectProp::raw_ptr _info)
{
  UASSERT (_info);
  props_ = _info;

  float _raw_val = ::libs::helpers::utils::ret_check_bound (props_->saturation_, -1.0f, 1.0f);

  if (_raw_val >= 0.0f)
    {
      short _indx = 0;

      std::generate (
        saturation_hsl_.begin (),
        saturation_hsl_.end (),
        [&]() {
          short _val = UUU_ICAST_SHORT (_indx + (255.0f * _raw_val) * ((255.0f - _indx) / 255.0f));
          ++_indx;
          ::libs::helpers::utils::check_bound<short> (_val, 0, 255);
          return _val;
        });
    }
  else
    {
      short _indx = 0;

      std::generate (
        saturation_hsl_.begin (),
        saturation_hsl_.end (),
        [&]() {
          short _val = UUU_ICAST_SHORT (_indx + (255.0f * _raw_val) * (_indx / 255.0f));
          ++_indx;
          ::libs::helpers::utils::check_bound<short> (_val, 0, 255);
          return _val;
        });
    }

  _raw_val = ::libs::helpers::utils::ret_check_bound (props_->contrast_, -1.0f, 1.0f);

  if (_raw_val <= 0.0f)
    {
      _raw_val = 0.65f + 0.35f * _raw_val;
    }
  else
    {
      _raw_val = 1.0f + (_raw_val - 1.0f) / 150.0f;
    }

  //  ��������� ������ ��� ��������� ���������
  {
    short _indx = 0;

    std::generate (
      contrast_hsl_.begin (),
      contrast_hsl_.end (),
      [&]() {
        short _val = UUU_ICAST_SHORT (std::pow (UUU_ICAST_FLOAT (_indx), props_->contrast_));
        ++_indx;
        ::libs::helpers::utils::check_bound<short> (_val, 0, 255);
        return _val;
      });
  }
  return;
}


bool
Impl::process_int (IVideoBuff::raw_ptr _h16_buff, IVideoBuff::raw_ptr _s16_buff, IVideoBuff::raw_ptr _l16_buff)
{
  XULOG_TRACE ("start software correction image");
  UASSERT (props_);

  if (!_l16_buff || _l16_buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      XULOG_WARNING ("skip software correction, empty light buff");
      return false;
    }

  bright_correct (*_l16_buff);

  if (0.0f != props_->contrast_)
    {
      XULOG_TRACE ("start graduent correction image");
      graduent_correct (*_l16_buff, contrast_hsl_);
    }

  /*correct hue -180.0f 0.0f 180.0f*/
  if (0.0f != props_->hue_ && _h16_buff && !_h16_buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
#if 0
      float koeff_hue = (finfo_.props_.hue_ + 0.0f) / 180.0f;
      base_functs::c1heck_bound (koeff_hue, -1.0f, 1.0f);
      const short loc_hue = s1tatic_cast<short> (koeff_hue * 127);

      UUU_DEFAULT_ALIGNED
      const short loc_array_hue[8] = {
        loc_hue, loc_hue, loc_hue, loc_hue, loc_hue, loc_hue, loc_hue, loc_hue
      };

      ::libs::optim::MCallInfo _cinfo1 (
        ::libs::optim::MCallInfo::dests_type{ { _h16_buff.get_data (), 0, 0 } },
        ::libs::optim::MCallInfo::sources_type{ { 0, 0, 0 } },
        _h16_buff.get_stride (),
        0,
        _h16_buff.get_dim_var (::utils::dbuffs::video::TypeDimVar::width),
        _h16_buff.get_dim_var (::utils::dbuffs::video::TypeDimVar::height),
        0,
        loc_array_hue,
        0,
        0);

      C1HECK_CALLS (finfo->pfuncts_[::libs::optim::helpers::ofc1AddConst](_cinfo1));
#endif
    }

  // correct saturation image
  if (0.0f != props_->saturation_ && _s16_buff && !_s16_buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      XULOG_TRACE ("start saturation correction image");
      graduent_correct (*_s16_buff, saturation_hsl_);
    }

  //  ����� ���� ��������������, �� �������������������� ������������ ��������� �����.
  if (props_->short2byte_)
    {
      XULOG_TRACE ("start saturate2short correction image");

      IVideoBuff::raw_ptr _buffs[] = {
        _h16_buff,
        _s16_buff,
        _l16_buff
      };

      for (IVideoBuff::raw_ptr _cbuff : _buffs)
        {
          if (!_cbuff || _cbuff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
            {
              continue;
            }

          sat2byte_correct (*_cbuff);
        }
    }
  return true;
}

}}}}      // namespace dlls::uplifters::vcorrect::soft
