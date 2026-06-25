/**
\file       vcodec-gen-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_vcodec_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcodec-gen-includes_int.hpp"
#include "vcodec-gen-info-filter-dll.hpp"

namespace dlls::codecs::vcodec_gen
{
InfoFilter::InfoFilter ()
{
  init ();
}


void
InfoFilter::init ()
{
  counter_frames_ = 0;
  dll_codec_      = nullptr;

  file_info_.reset ();

  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoCodecProp > (ef_props_);
  str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
}


void
InfoFilter::sync_int (bool force)
{
  fps_.set_fps (rprops_->fps_coder_);

  if (dll_codec_)
  {
    dll_codec_->set_codec_info (rprops_);
  }

  auto impl = active_codec_impl_.lock ();
  if (impl)
  {
    impl->update_codec_property (rprops_);
  }
}
}   // namespace dlls::codecs::vcodec_gen
