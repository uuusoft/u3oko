/**
\file       gen-vgen-filter-dll-idatasource.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_gen_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "gen-vgen-includes_int.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "gen-vgen-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::sources::gen_vgen
{
void
Filter::fill_buf (
  InfoFilter*             finfo,
  syn::BufsEvent::raw_ptr pbufevent)
{
  ::libs::bufs::Bufs::raw_ptr bufs = pbufevent->get_buf ().get ();

  bufs->set_flag (::libs::bufs::BufsFlags::empty, true);

  std::unique_lock< InfoFilter::sync_type > lock (finfo->wdmtx_, consts::ms_wait_capture_device);
  if (!lock.owns_lock ())
  {
    U3_LOG_DATA_ERROR ("failed acquired mutex" + VTOLOG (consts::ms_wait_capture_device.count ()) + "ms");
    return;
  }

  if (!finfo->impl_frames_.empty ())
  {
    U3_LOG_DATA_DBG ("copy from finfo->impl_frames_ to graph" + VTOLOG (finfo->impl_frames_.size ()));
    {
      bool  set_raw_as_base = false;
      auto& framefront      = *finfo->impl_frames_.front ();

      bufs->set_flag (::libs::bufs::BufsFlags::empty, false);

      for (auto& keybuf : framefront)
      {
        bufs->set_buf (keybuf.first, keybuf.second);
        if (!keybuf.second || keybuf.second->get_flag (::utils::dbufs::BufFlags::empty))
        {
          continue;
        }
        U3_LOG_DATA_DBG ("get full buf from source" + VTOLOG (set_raw_as_base) + TOLOG (keybuf.first));
        //  Сырой (не пустой) буфер имеет приоритет.
        if (!set_raw_as_base)
        {
          bufs->set_base_index (keybuf.first);
          set_raw_as_base = utils::dbufs::video::consts::offs::raw == keybuf.first ? true : false;
        }
      }
    }

    // debug
    //::libs::bufs::dump (bufs, true);
    finfo->impl_frames_.pop_front ();
  }

  if (!events_from_impl_.empty ())
  {
    auto events = pbufevent->get_events ();

    std::ranges::copy (events_from_impl_, std::back_inserter (*events));
    events_from_impl_.clear ();

    for (const auto& event : *events)
    {
      auto* devent = ::libs::iproperties::helpers::cast_event< syn::InterfCaptureImageEvent > (event);
      if (devent)
      {
        U3_LOG_DATA_MARK ("recive InterfCaptureImageEvent -> update properties" + VTOLOG (devent->is_active ()));
        finfo_.capture_impl_ = devent->is_active () ? devent->get_interface () : finfo->null_impl_;
        U3_ASSERT (!finfo_.capture_impl_.expired ());
        if (auto impl = finfo_.capture_impl_.lock ())
        {
          impl->update_capture_property (finfo->capture_props_);
          impl->update_driver_property (finfo->rprops_);
        }
      }
    }
  }
}
}   // namespace dlls::sources::gen_vgen
