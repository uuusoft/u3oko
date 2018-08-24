//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.05.2017
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"

namespace dlls { namespace codecs { namespace vcodec_gen {

InfoFilter::InfoFilter () :
  rprops_ (nullptr),
  rcodec_ (nullptr),
  counter_frames_ (0)
{
  init ();
}


InfoFilter::~InfoFilter ()
{}


void
InfoFilter::init ()
{
  counter_frames_ = 0;
  rcodec_         = nullptr;
  file_info_.reset ();
  rprops_ = ::libs::iproperties::helpers::get_and_cast_event<props_type> (props_);
  str2props_.insert (str2prop_type::value_type (props_->get_mid (), rprops_));
  return;
}


void
InfoFilter::sync_int (bool _force)
{
  XULOG_TEST ("InfoFilter::sync_int: beg");
  fps_.set_fps (rprops_->fps_coder_);

  if (rcodec_)
    {
      rcodec_->set_codec_info (rprops_);
    }

  auto _impl = active_impl_.lock ();
  if (_impl)
    {
      XULOG_TEST ("InfoFilter::sync_int: update codec property");
      _impl->update_codec_property (rprops_);
    }
  return;
}

}}}      // namespace dlls::codecs::vcodec_gen
