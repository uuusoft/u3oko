//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-codec-flat-prop.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-codec-flat-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace codec {

VideoCodecFlatProp::VideoCodecFlatProp () :
  size_ (sizeof (VideoCodecFlatProp)),
  quality_ (50),
  max_percent_pframe_ (8.0f),
  max_period_kframe_ (500),
  percent_block_ (8.0f),
  type_ (TypeCodecMode::coder),
  monochrome_ (true)
{
  memset (entropy_coders_, 0, sizeof (entropy_coders_));
}


VideoCodecFlatProp::VideoCodecFlatProp (const VideoCodecFlatProp& _op)
{
  (*this) = _op;
}


void
VideoCodecFlatProp::correct ()
{
  size_ = sizeof (VideoCodecFlatProp);

  ::libs::helpers::utils::check_float (&max_percent_pframe_);
  ::libs::helpers::utils::check_float (&percent_block_);

  ::libs::helpers::utils::check_bound<int> (quality_, 0, 100);
  ::libs::helpers::utils::check_bound (max_percent_pframe_, 1.0f, 10.0f);
  ::libs::helpers::utils::check_bound<int> (max_period_kframe_, 1, 10 * 1024);
  ::libs::helpers::utils::check_bound (percent_block_, 0.0f, 100.0f);

  for (std::size_t _eindx = 0; _eindx < consts::max_count_entropy_coders; ++_eindx)
    {
      entropy_coders_[_eindx][consts::max_len_name_entropy_coder] = '\0';
    }
  return;
}


void
VideoCodecFlatProp::reset ()
{
  size_ = sizeof (VideoCodecFlatProp);

  quality_            = 50;
  max_percent_pframe_ = 8.0f;
  max_period_kframe_  = 500;
  percent_block_      = 8.0f;
  type_               = TypeCodecMode::coder;
  monochrome_         = true;

  memset (entropy_coders_, 0, sizeof (entropy_coders_));
  return;
}


const VideoCodecFlatProp&
VideoCodecFlatProp::operator= (const VideoCodecFlatProp& _op)
{
  size_               = sizeof (VideoCodecFlatProp);
  type_               = _op.type_;
  quality_            = _op.quality_;
  max_percent_pframe_ = _op.max_percent_pframe_;
  max_period_kframe_  = _op.max_period_kframe_;
  percent_block_      = _op.percent_block_;
  monochrome_         = _op.monochrome_;

  ::libs::helpers::mem::acopy (_op.entropy_coders_, entropy_coders_, sizeof (entropy_coders_));
  return *this;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::codec
