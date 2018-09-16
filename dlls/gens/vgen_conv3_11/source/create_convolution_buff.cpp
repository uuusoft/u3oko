//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       create_convolution_buff.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_core
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace gens { namespace vgen_conv3_11 {

short
get_mul_koeff_for_conv (const BuffVideoConvolutionProp& _ibuff, ::libs::optim::io::MCallInfo& _cinfo)
{
  short _ret = 1;

  if (_ibuff.size_ <= 3)
    {
      _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<TCore3x3> (*boost::any_cast<const TCore3x3*> (_cinfo.params_.evals_[0]), _ibuff.koeff_);
      return _ret;
    }

  if (_ibuff.size_ <= 5)
    {
      _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<TCore5x5> (*boost::any_cast<const TCore5x5*> (_cinfo.params_.evals_[0]), _ibuff.koeff_);
      return _ret;
    }

  if (_ibuff.size_ <= 7)
    {
      _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<TCore7x7> (*boost::any_cast<const TCore7x7*> (_cinfo.params_.evals_[0]), _ibuff.koeff_);
      return _ret;
    }

  if (_ibuff.size_ <= 9)
    {
      _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<TCore9x9> (*boost::any_cast<const TCore9x9*> (_cinfo.params_.evals_[0]), _ibuff.koeff_);
      return _ret;
    }

  _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<TCore11x11> (*boost::any_cast<const TCore11x11*> (_cinfo.params_.evals_[0]), _ibuff.koeff_);
  return _ret;
}


void
Filter::fill_koeffs_for_conv (
  const BuffVideoConvolutionProp&    _ibuff,
  ::libs::optim::io::MCallInfo&      _cinfo,
  ::libs::optim::mcalls::InfoMFunct& _tfunct)
{
  if (_ibuff.size_ <= 3)
    {
      icore_3x3_ = &core_3x3_;
      ::libs::optim::s16bit::conv::base::c3x3::cores::copy (_ibuff.vals_, core_3x3_);

      if ("gaus1" == _ibuff.name_)
        {
          icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::gaus1;
        }
      else if ("laplas1" == _ibuff.name_)
        {
          icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::laplas1;
        }
      else if ("all_1" == _ibuff.name_)
        {
          icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::all_1;
        }

      _tfunct.pfunct_ = &conv_mod_3x3_;
      _cinfo.params_.evals_.push_back (boost::any (const_cast<const TCore3x3*> (icore_3x3_)));
    }
  else if (_ibuff.size_ <= 5)
    {
      icore_5x5_ = &core_5x5_;
      ::libs::optim::s16bit::conv::base::c5x5::cores::copy (_ibuff.vals_, core_5x5_);

      if ("gaus1" == _ibuff.name_)
        {
          icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::gaus1;
        }
      else if ("laplas1" == _ibuff.name_)
        {
          icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::laplas1;
        }
      else if ("all_1" == _ibuff.name_)
        {
          icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::all_1;
        }

      _tfunct.pfunct_ = &conv_mod_5x5_;
      _cinfo.params_.evals_.push_back (boost::any (const_cast<const TCore5x5*> (icore_5x5_)));
    }
  else if (_ibuff.size_ <= 7)
    {
      icore_7x7_ = &core_7x7_;
      ::libs::optim::s16bit::conv::base::c7x7::cores::copy (_ibuff.vals_, core_7x7_);

      if ("gaus1" == _ibuff.name_)
        {
          icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::gaus1;
        }
      else if ("laplas1" == _ibuff.name_)
        {
          icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::laplas1;
        }
      else if ("all_1" == _ibuff.name_)
        {
          icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::all_1;
        }

      _tfunct.pfunct_ = &conv_mod_7x7_;
      _cinfo.params_.evals_.push_back (boost::any (const_cast<const TCore7x7*> (icore_7x7_)));
    }
  else if (_ibuff.size_ <= 9)
    {
      icore_9x9_ = &core_9x9_;
      ::libs::optim::s16bit::conv::base::c9x9::cores::copy (_ibuff.vals_, core_9x9_);

      if ("gaus1" == _ibuff.name_)
        {
          icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::gaus1;
        }
      else if ("laplas1" == _ibuff.name_)
        {
          icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::laplas1;
        }
      else if ("all_1" == _ibuff.name_)
        {
          icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::all_1;
        }

      _tfunct.pfunct_ = &conv_mod_9x9_;
      _cinfo.params_.evals_.push_back (boost::any (const_cast<const TCore9x9*> (icore_9x9_)));
    }
  else
    {
      icore_11x11_ = &core_11x11_;
      ::libs::optim::s16bit::conv::base::c11x11::cores::copy (_ibuff.vals_, core_11x11_);

      if ("gaus1" == _ibuff.name_)
        {
          icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::gaus1;
        }
      else if ("laplas1" == _ibuff.name_)
        {
          icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::laplas1;
        }
      else if ("all_1" == _ibuff.name_)
        {
          icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::all_1;
        }

      _tfunct.pfunct_ = &conv_mod_11x11_;
      _cinfo.params_.evals_.push_back (boost::any (const_cast<const TCore11x11*> (icore_11x11_)));
    }

  const short _mull_koeff = get_mul_koeff_for_conv (_ibuff, _cinfo);
  _cinfo.params_.evals_.push_back (boost::any (_mull_koeff));
  return;
}


void
Filter::convolution_buff ()
{
  for (BuffVideoConvolutionProp& _buff : finfo_.rprops_->buffs_)
    {
      _buff.check ();

      IVideoBuff::raw_ptr _src = (*pbuff_)[_buff.indx_sbuff_];

      if (!_src || _src->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
        {
          continue;
        }

      ::libs::buffs::alloc_buff_by_indx (pbuff_, _buff.indx_dbuff_, _src);

      IVideoBuff::raw_ptr _dst           = (*pbuff_)[_buff.indx_dbuff_];
      const bool          _req_temp_buff = (_buff.indx_dbuff_ == _buff.indx_sbuff_) ? true : false;
      IVideoBuff::raw_ptr _tbuff         = (*pbuff_)[utils::dbuffs::video::consts::offs::temp1];

      //bin_buff( _b2b, 0, 1, _pdst );

      if (_req_temp_buff)
        {
          _tbuff->clone (_src, 0.0f);
          //utils::dbuffs::video::helpers::fill_convolution_edges( &_tbuff );
        }

      ::libs::optim::io::MCallInfo _cinfo;

      _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_src));
      _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_req_temp_buff ? _tbuff : _dst));

      ::libs::optim::mcalls::InfoMFunct _tfunct;

      fill_koeffs_for_conv (_buff, _cinfo, _tfunct);

      pthreads_->mcall (_tfunct, _cinfo);

      if (_req_temp_buff)
        {
          _tbuff->set_mem_var (::utils::dbuffs::TypeMemVar::size_data, (*_src)[::utils::dbuffs::TypeMemVar::size_data]);
          _dst->clone (_tbuff, 100.0f);
        }

      _dst->set_mem_var (::utils::dbuffs::TypeMemVar::size_data, (*_src)[::utils::dbuffs::TypeMemVar::size_data]);
    }

  return;
}

}}}      // namespace dlls::gens::vgen_conv3_11
