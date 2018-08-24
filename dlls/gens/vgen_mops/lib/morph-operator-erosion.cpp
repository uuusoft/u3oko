//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       morph-operator-erosion.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_vgen_mops_lib
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "morph-operator.hpp"

namespace dlls { namespace gens { namespace vgen_mops { namespace lib { namespace helpers {

short
get_mkoeff_for_erosion_operation (const short _size_spot)
{
  short _ret = 1;

  if (_size_spot <= 1)
    {
      short     _mval      = ::libs::optim::s16bit::conv::base::c3x3::cores::spot1.center_val ();
      const int _summ_spot = _mval * _size_spot * _size_spot + 1;

      _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<::libs::optim::s16bit::conv::base::c3x3::cores::TCore> (
        ::libs::optim::s16bit::conv::base::c3x3::cores::spot1, _summ_spot);
      return _ret;
    }

  if (_size_spot <= 3)
    {
      short     _mval      = ::libs::optim::s16bit::conv::base::c5x5::cores::spot1.center_val ();
      const int _summ_spot = _mval * _size_spot * _size_spot + 1;

      _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<::libs::optim::s16bit::conv::base::c5x5::cores::TCore> (
        ::libs::optim::s16bit::conv::base::c5x5::cores::spot1, _summ_spot);
      return _ret;
    }

  if (_size_spot <= 5)
    {
      short     _mval      = ::libs::optim::s16bit::conv::base::c7x7::cores::spot1.center_val ();
      const int _summ_spot = _mval * _size_spot * _size_spot + 1;

      _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<::libs::optim::s16bit::conv::base::c7x7::cores::TCore> (
        ::libs::optim::s16bit::conv::base::c7x7::cores::spot1, _summ_spot);
      return _ret;
    }

  if (_size_spot <= 7)
    {
      short     _mval      = ::libs::optim::s16bit::conv::base::c9x9::cores::spot1.center_val ();
      const int _summ_spot = _mval * _size_spot * _size_spot + 1;

      _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<::libs::optim::s16bit::conv::base::c9x9::cores::TCore> (
        ::libs::optim::s16bit::conv::base::c9x9::cores::spot1, _summ_spot);
      return _ret;
    }

  short     _mval      = ::libs::optim::s16bit::conv::base::c11x11::cores::spot1.center_val ();
  const int _summ_spot = _mval * _size_spot * _size_spot + 1;

  _ret = ::libs::optim::s16bit::conv::get_mkoeff_core<::libs::optim::s16bit::conv::base::c11x11::cores::TCore> (
    ::libs::optim::s16bit::conv::base::c11x11::cores::spot1, _summ_spot);
  return _ret;
}


void
MorphOperator::fill_koeffs_for_erosion_operation (
  const short _size_spot,
  MCallInfo&  _cinfo,
  InfoMFunct& _tfunct)
{
  short _mull_koeff = get_mkoeff_for_erosion_operation (_size_spot);

  if (_size_spot <= 1)
    {
      _tfunct.pfunct_ = &conv_mod_3x3_;
      _cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c3x3::cores::spot1));
    }
  else if (_size_spot <= 3)
    {
      _tfunct.pfunct_ = &conv_mod_5x5_;
      _cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c5x5::cores::spot1));
    }
  else if (_size_spot <= 5)
    {
      _tfunct.pfunct_ = &conv_mod_7x7_;
      _cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c7x7::cores::spot1));
    }
  else if (_size_spot <= 7)
    {
      _tfunct.pfunct_ = &conv_mod_9x9_;
      _cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c9x9::cores::spot1));
    }
  else
    {
      _tfunct.pfunct_ = &conv_mod_11x11_;
      _cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c11x11::cores::spot1));
    }

  _cinfo.params_.evals_.push_back (boost::any (_mull_koeff));
  return;
}


void
MorphOperator::erosion_buff (
  const ParamsOperation& _op,
  ::libs::buffs::Buffs*  _pbuff,
  IVideoBuff*            _pdst)
{
  auto _tbuff = (*_pbuff)[utils::dbuffs::video::consts::offs::temp1];

  _tbuff->clone (_pdst, 100.0f);

  utils::dbuffs::video::helpers::fill_convolution_edges (_tbuff);

  UASSERT (_tbuff->check ([](std::size_t _x, std::size_t _y, short _val) { if( _val > 1 ) { UASSERT_SIGNAL( "failed" ); return false; } return true; }));
  UASSERT (utils::dbuffs::video::helpers::is_equal_dim (*_tbuff, *_pdst));

  ::libs::optim::io::MCallInfo _cinfo;

  _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_tbuff));
  _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_pdst));

  ::libs::optim::mcalls::InfoMFunct _tfunct;

  fill_koeffs_for_erosion_operation (_op.size_spot_, _cinfo, _tfunct);

  pthreads_->mcall (_tfunct, _cinfo);
  return;
}

}}}}}      // namespace dlls::gens::vgen_mops::lib::helpers
