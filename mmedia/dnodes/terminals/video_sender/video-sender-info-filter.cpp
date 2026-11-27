/**
\file       video-sender-info-filter.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/
#include "video-sender-includes_int.hpp"
#include "video-sender-info-filter.hpp"
#include "video-sender-filter-dll.hpp"

namespace dnodes::terminals::video_sender
{
InfoFilter::InfoFilter () : rprops_ (::libs::iproperties::helpers::create_event_in_list< syn::EndPointProp > (ef_props_))
{
  // str2props_.insert ({ ef_props_.front ()->get_mid (), rprops_ });
  str2props_[ef_props_.front ()->get_mid ()] = rprops_;
}
}   // namespace dnodes::terminals::video_sender
