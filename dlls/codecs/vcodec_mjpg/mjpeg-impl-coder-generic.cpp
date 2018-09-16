//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mjpeg-impl-coder-generic.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_vcodec_mjpg
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "mjpeg-impl.hpp"

namespace dlls { namespace codecs { namespace vcodec_mjpg {

bool
MjpegImpl::code_int (const Buffs* _src, Buffs* _dst, events_type* _events)
{
  XULOG_TRACE ("MjpegImpl::code_int: beg");
  XULOG_TRACE ("MjpegImpl::code_int: begin software compress frame");
  const IVideoBuff::raw_ptr  _obuff = (*_dst)[cinfo_.buffs_.indx_dbuff_];
  const IVideoBuff::craw_ptr _hbuff = (*_src)[utils::dbuffs::video::consts::offs::hue];
  const IVideoBuff::craw_ptr _sbuff = (*_src)[utils::dbuffs::video::consts::offs::sat];
  const IVideoBuff::craw_ptr _lbuff = (*_src)[cinfo_.buffs_.indx_sbuff_];
  UASSERT (_lbuff);

  XULOG_TRACE ("MjpegImpl::code_int: alloc buff");
  _obuff->balloc (
    ::utils::dbuffs::video::AllocBuffInfo (
      _lbuff->get_dim_var (::utils::dbuffs::video::TypeDimVar::width),
      _lbuff->get_dim_var (::utils::dbuffs::video::TypeDimVar::height),
      _lbuff->get_dim_var (::utils::dbuffs::video::TypeDimVar::stride),
      ::libs::helpers::uids::minor::rgb32));

  ::utils::dbuffs::video::helpers::override_data (*_obuff, 0, 0);

  XULOG_TRACE ("MjpegImpl::code_int: init proxy");
  ProxyBuff  _thbuff (_hbuff && (*_hbuff)[::utils::dbuffs::TypeMemVar::size_data] ? _hbuff : nullptr);
  ProxyBuff  _tsbuff (_sbuff && (*_sbuff)[::utils::dbuffs::TypeMemVar::size_data] ? _sbuff : nullptr);
  ProxyBuff  _tlbuff (_lbuff);
  ProxyBuff  _tout_buff (_obuff);
  int        _out_size    = 0;
  const bool _exist_color = _thbuff.self_test () && _tsbuff.self_test ();
  const bool _use_color   = _exist_color && !cinfo_.plane_.monochrome_;

  if (_use_color)
    {
      XULOG_TRACE ("MjpegImpl::code_int: mcall color");
      temp_buff_->balloc (
        ::utils::dbuffs::video::AllocBuffInfo (
          _lbuff->get_dim_var (::utils::dbuffs::video::TypeDimVar::width),
          _lbuff->get_dim_var (::utils::dbuffs::video::TypeDimVar::height),
          0,
          ::libs::helpers::uids::minor::rgb24));

      int        _stride_rgb24 = 0;
      MCallInfo  _cinfo;
      InfoMFunct _tfunct (&fhsl_to_rgb24_);

      _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (temp_buff_.get ()));
      _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_hbuff));
      _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_sbuff));
      _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (_lbuff));

      _cinfo.params_.pints_.push_back (&_stride_rgb24);

      pthreads_->mcall (_tfunct, _cinfo, 0);
      UASSERT (_stride_rgb24 == UUU_ICAST_INT (temp_buff_->get_dim_var (utils::dbuffs::video::TypeDimVar::stride)));
    }
  else
    {
      XULOG_TRACE ("MjpegImpl::code_int: mcall mono");
      temp_buff_->balloc (
        ::utils::dbuffs::video::AllocBuffInfo (
          _lbuff->get_dim_var (::utils::dbuffs::video::TypeDimVar::width),
          _lbuff->get_dim_var (::utils::dbuffs::video::TypeDimVar::height),
          _lbuff->get_dim_var (::utils::dbuffs::video::TypeDimVar::stride),
          ::libs::helpers::uids::minor::y8));

      MCallInfo _cinfo;

      _cinfo.srcs_.push_back (ProxyBuff (_lbuff));
      _cinfo.dsts_.push_back (ProxyBuff (temp_buff_.get ()));

      InfoMFunct _tfunct (&fx16_x8_);

      pthreads_->mcall (_tfunct, _cinfo);
    }

  const bool _ret = comp_iframe (_use_color, _tout_buff, _out_size);

  UASSERT (_out_size > 0);
  _obuff->set_mem_var (::utils::dbuffs::TypeMemVar::size_data, _out_size);
  XULOG_TRACE ("MjpegImpl::code_int: end");
  return _ret;
}

}}}      // namespace dlls::codecs::vcodec_mjpg
