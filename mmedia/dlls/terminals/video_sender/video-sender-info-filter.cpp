/**
\file       video-sender-info-filter.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_video_sender_dll
*/
#include "video-sender-includes_int.hpp"
#include "video-sender-info-filter.hpp"
#include "video-sender-filter-dll.hpp"

namespace dlls::terminals::video_sender
{
InfoFilter::InfoFilter () : rprops_ (::libs::iproperties::helpers::create_event_in_list< syn::EndPointProp > (ef_props_))
{
  str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
}
}   // namespace dlls::terminals::video_sender
