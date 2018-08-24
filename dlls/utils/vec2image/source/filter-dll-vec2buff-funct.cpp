//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       vec2buff_funct.cpp
\brief      Filter for correct image
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_dlls_vec2image
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace utils { namespace vec2image1 {

void
Filter::make_vec2buff (const BuffEventInfo& _b2b, const IVideoBuff& _src, IVideoBuff& _dst)
{
  ::libs::optim::io::MCallInfo _cinfo;

  _cinfo.srcs_.push_back (::libs::optim::io::ProxyBuff (const_cast<IVideoBuff::raw_ptr> (&_src)));
  _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (&_dst));

  _cinfo.params_.evals_.push_back (boost::any (&_b2b));

  ::libs::optim::mcalls::InfoMFunct _tfunct (&vec2image1_);

  _tfunct.src_align_.px_x_ = _b2b.size_block_;
  _tfunct.dst_align_.px_x_ = _b2b.size_block_;
  _tfunct.src_align_.px_y_ = 1;
  _tfunct.dst_align_.px_y_ = _b2b.size_block_;
  _tfunct.dest_div_koeffy_ = 1;
  _tfunct.dest_mul_koeffy_ = 1;      //_b2b.size_block_;

  pthreads_->mcall (_tfunct, _cinfo);
  return;
}

}}}      // namespace dlls::utils::vec2image1
