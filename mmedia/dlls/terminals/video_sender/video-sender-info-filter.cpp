/**
\file       video-sender-info-filter.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_video_sender_dll
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "video-sender-includes_int.hpp"
#include "video-sender-info-filter.hpp"
#include "video-sender-filter-dll.hpp"

namespace dlls::terminals::video_sender
{
InfoFilter::InfoFilter () :
  rprops_ (nullptr),
  count_frames_ (0)
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::EndPointProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
}
}   // namespace dlls::terminals::video_sender
