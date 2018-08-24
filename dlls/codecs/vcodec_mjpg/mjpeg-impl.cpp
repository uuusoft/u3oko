//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mjpeg-impl.cpp
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
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace codecs { namespace vcodec_mjpg {

MjpegImpl::MjpegImpl () :
  jpeg_buff_ (nullptr),
  size_jpeg_buff_ (0),
  hjpeg_ (nullptr)
{
  pthreads_ = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();
  simd_     = ::libs::helpers::sys::cpu::TypeExtCpu::usual;
}


MjpegImpl::~MjpegImpl ()
{
  if (jpeg_buff_)
    {
      tjFree (jpeg_buff_);
      jpeg_buff_ = nullptr;
    }

  if (hjpeg_)
    {
      tjDestroy (hjpeg_);
      hjpeg_ = nullptr;
    }
}


void
MjpegImpl::set_codec_info_int (const VideoCodecProp* _cinfo)
{
  cinfo_.copy (_cinfo);
  return;
}


void
MjpegImpl::get_codec_info_int (VideoCodecProp* ret_info)
{
  ret_info->copy (&cinfo_);
  return;
}


void
MjpegImpl::set_cpu_int (::libs::helpers::sys::cpu::TypeExtCpu optim)
{
  return;
}


void
MjpegImpl::init_int (const codec_gen::InfoGenCodec& _info)
{
  _info.check ();
  iinfo_ = _info;

  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  fx16_x8_       = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX16_X8Alg::val_key));
  fx8_x16_       = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX8_X16Alg::val_key));
  fhsl_to_rgb24_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CHSL2RgbAlg::val_key));

  auto _ibuff = ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ()->impl ();
  temp_buff_  = _ibuff->get ();
  return;
}


const StatisticInfo&
MjpegImpl::get_statistic_info_int () const
{
  return statistic_;
}


void
MjpegImpl::reset_statistic_info_int ()
{
  statistic_.reset ();
  return;
}

}}}      // namespace dlls::codecs::vcodec_mjpg
