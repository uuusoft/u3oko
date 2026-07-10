/**
\file       pict-vgen-source-impl-isourceimpl-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_pict_vgen
*/
#include "includes_int.hpp"
#include "pict-vgen-source-impl.hpp"

namespace dlls::sources::pict_vgen
{
void
SourceImpl::init_int ()
{
}


void
SourceImpl::start_int ()
{
}


void
SourceImpl::stop_int ()
{
}


void
SourceImpl::get_sources_int (SourceImpl::sources_type& sources)
{
  sources.emplace_back (
    "images",
    libs::events_media::events::DataSources::video,
    0,
    0);
}


void
SourceImpl::get_raw_data_int (
  syn::pkeys2bufs_type& bufs,
  syn::tevents_type*    events)
{
  auto& buf = (*bufs)[::utils::dbufs::video::consts::offs::raw];
  U3_ASSERT (buf);

  buf->set_flag (::utils::dbufs::BufFlags::empty, true);

  if (!send_interfaces_ && events)
  {
    auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::InterfCaptureImageEvent > ();
    revnt->set_interface (icapture_);
    revnt->set_active (true);
    events->push_back (evnt);
    send_interfaces_ = true;
    U3_LOG_DATA_DATA ("send interfaces: InterfCorrectImageEvent (+) InterfCaptureImageEvent (+)");
  }

  if (icapture_->is_capture_property_update ())
  {
    U3_MARK_UNUSED volatile auto new_prop = icapture_->get_capture_property ();   // reset flag icapture_->is_capture_property_update
    sync_internal_structures ();
  }

  const auto picters_folder = ::libs::utility::files::update_home_folder (srcimpinfo_.props_->ext_vals_.at (consts::param_keys::picter_folder));
  if (picters_folder.empty () ||
      enum_files_.files_.empty () ||
      !::libs::utility::files::is_folder (picters_folder))
  {
    return;
  }

  print_images2buf (buf);

  auto now = boost::posix_time::microsec_clock::universal_time ();
  if (::dlls::sources::pict_vgen::Image2Frames::one != image2frame_style_)
  {
    auto               diff              = now - time_last_change_file_;
    const std::int32_t user_scroll_speed = std::stoi (srcimpinfo_.props_->ext_vals_.at (consts::param_keys::scroll_speed));
    float              scroll_speed      = user_scroll_speed * 30.0F * diff.total_milliseconds () / 1000.0F;

    ::libs::utility::utils::check_bound (scroll_speed, 1.0F, 500.0F);
    // scroll_speed     = 1.0F;   // debug
    off_first_image_ = off_first_image_ > 0.0F ? off_first_image_ : 0.0F;
    off_first_image_ += scroll_speed;
  }

  time_last_change_file_ = now;
}


void
SourceImpl::set_cpu_int (syn::CpuExts current_optim)
{
}


void
SourceImpl::update_source_info_int (const syn::SourceImplInfo& info)
{
  U3_LOG_DATA_DBG ("sync picter source::---->" + VTOLOG (info.capture_props_->capi_.width_) + VTOLOG (info.capture_props_->capi_.height_));
  source_impl_info_ = info;
  sync_internal_structures ();
}
}   // namespace dlls::sources::pict_vgen
