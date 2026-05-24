/**
\file       base-id-dll-transform-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       16.07.2018
\project    u3_base_id_dll
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "base_id-includes_int.hpp"
#include "base_id-filter-dll.hpp"

namespace dlls::base_id
{
void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);

  auto events = info.frame_events_;
  U3_ASSERT (events);

  if (!send_base_interf_)
  {
    syn::IEvent::ptr rmsg;
    auto             dmsg = ::libs::iproperties::helpers::create_event< syn::InterfBaseIdEvent > (rmsg);

    dmsg->set_interface (base_interf_);
    dmsg->set_active (true);
    events->push_back (rmsg);
    send_base_interf_ = true;
  }

  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }
  ++counter_frames_;
}
}   // namespace dlls::base_id
