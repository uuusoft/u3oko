/**
\file       v4l2-vgen-source-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.02.2026
\project    u3_v4l2_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "v4l2-vgen-includes_int.hpp"
#include "v4l2-vgen-source-impl.hpp"

namespace dlls::sources::v4l2_vgen
{
SourceImpl::~SourceImpl () noexcept
{
  free_device ();
}


void
SourceImpl::init_int ()
{
}


void
SourceImpl::start_int ()
{
  counter_frames_ = 0;
  U3_CHECK (v4l2_init_, "not init device, skip restart");
  start_capture ();
}


void
SourceImpl::start_capture ()
{
}


void
SourceImpl::stop_capture ()
{
}


void
SourceImpl::stop_int ()
{
  stop_capture ();
  v4l2_impl_.reset ();
}


void
SourceImpl::get_sources_int (std::vector< syn::DataSourceInfo > &sources)
{
  static const std::array< ::libs::helpers::uids::minor::id_val, 14 > support_formats = {
    ::libs::helpers::uids::minor::id_val::yuy2,
    ::libs::helpers::uids::minor::id_val::rgb24,
    ::libs::helpers::uids::minor::id_val::rgb32,
    ::libs::helpers::uids::minor::id_val::i420,
    ::libs::helpers::uids::minor::id_val::yuyv,
    ::libs::helpers::uids::minor::id_val::device_specific,
    ::libs::helpers::uids::minor::id_val::y8,
    ::libs::helpers::uids::minor::id_val::y16,
    ::libs::helpers::uids::minor::id_val::ycb,
    ::libs::helpers::uids::minor::id_val::uyvy,
    //::libs::helpers::uids::minor::id_val::iyuv,
    //::libs::helpers::uids::minor::id_val::yv12,
    //::libs::helpers::uids::minor::id_val::yvu9,
    ::libs::helpers::uids::minor::id_val::nv21
  };

  syn::VideoDriverProp        props;
  syn::VideoDriverCaptureProp capture_props;
  syn::LinksVideoDriverProp   links_props;

  ::dlls::sources::gen_lib::SourceImplInfo srcinfo {
    &props,
    &capture_props,
    &links_props
  };

  sources.reserve (consts::max_check_device_count);
  for (std::size_t idd = 0; idd < consts::max_check_device_count; ++idd)
  {
    props.device_name_ = "video" + std::to_string (idd);
    U3_LOG_DATA_DEV ("check v4l2 device" + TOLOG (props.device_name_));
    for (const auto &format : support_formats)
    {
      capture_props.capi_.px_format_ = format;

      try
      {
        auto v4l2 = std::make_unique< camera::CamImpl > (srcinfo);
        if (v4l2->is_init ())
        {
          sources.emplace_back (
            props.device_name_,
            libs::imdata_events::events::DataSources::video,
            1,
            1);
          U3_LOG_DATA_DEV ("add v4l2 device" + TOLOG (props.device_name_));
          break;
        }
      }
      catch (boost::exception &e)
      {
        // U3_LOG_DATA_EXCEPT (boost::diagnostic_information (e));
      }
      catch (std::exception &e)
      {
        // U3_LOG_DATA_EXCEPT (e.what ());
      }
      catch (...)
      {
        // U3_LOG_DATA_EXCEPT ("unknown exception v4l2 device");
      }
    }
  }
}

void
SourceImpl::get_raw_data_int (
  syn::pkeys2bufs_type &bufs,
  syn::tevents_type    *events)
{
  {
    const auto now = std::chrono::high_resolution_clock::now ();
    if (icapture_->is_capture_property_update ())
    {
      U3_LOG_DATA_MARK ("update capture property begin" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (srcimpinfo_.capture_props_)));
      srcimpinfo_.capture_props_ = icapture_->get_capture_property ();
      last_time_restart_         = now - consts::ms_timeout_recreate_device;
      camera_error_              = 0xFF;
    }

    const bool recreate_request             = camera_error_ || !v4l2_init_ ? true : false;
    const auto diff_time_after_last_restart = now - last_time_restart_;
    const bool recreate_request_now         = recreate_request && diff_time_after_last_restart >= consts::ms_timeout_recreate_device;

    if (recreate_request)
    {
      if (recreate_request_now)
      {
        U3_LOG_DATA_MARK ("START recreate device" + VTOLOG (v4l2_init_) + VTOLOG (camera_error_) + VTOLOG (srcimpinfo_.capture_props_->capi_.fps_));
        stop_int ();

        last_time_restart_ = now;
        camera_error_      = 0;

        deinit_device ();
        init_device (srcimpinfo_);
        start_int ();
      }
    }
    if (icorrection_->is_correction_property_update ())
    {
      if (v4l2_impl_)
      {
        syn::VideoCorrectProp::craw_ptr new_prop = icorrection_->get_correction_property ();
        v4l2_impl_->sync_correct_props (new_prop);
      }
    }
  }

  if (!send_interfaces_ && events)
  {
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::InterfCorrectImageEvent > (rmsg);

      dmsg->set_interface (icorrection_);
      dmsg->set_active (true);
      events->push_back (rmsg);
    }
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< syn::InterfCaptureImageEvent > (rmsg);

      dmsg->set_interface (icapture_);
      dmsg->set_active (true);
      events->push_back (rmsg);
    }
    send_interfaces_ = true;
    U3_LOG_DATA_DATA ("send InterfCorrectImageEvent, InterfCaptureImageEvent");
  }

  if (!v4l2_init_)
  {
    return;
  }

  auto &buf = (*bufs)[::utils::dbufs::video::consts::offs::raw];
  U3_ASSERT (buf);
  buf->set_flag (::utils::dbufs::BufFlags::empty, true);

  if (v4l2_impl_)
  {
    syn::IVideoBuf::ptr raw_buf = v4l2_impl_->get_buf ();
    if (!raw_buf)
    {
      if (!is_source_started ())
      {
        return;
      }
      start_capture ();
      return;
    }

    buf->clone (raw_buf.get (), 100.0F);
    raw_buf->set_flag (::utils::dbufs::BufFlags::empty, true);
    ++counter_frames_;
  }
}


void
SourceImpl::set_cpu_int (::libs::helpers::sys::cpu::CpuExts simd)
{
}


void
SourceImpl::free_device () noexcept
{
  stop ();
  v4l2_impl_.reset ();
}

void
SourceImpl::update_source_info_int (const ::dlls::sources::gen_lib::SourceImplInfo &info)
{
  deinit_device ();
  init_device (info);
}


bool
SourceImpl::init_device (const ::dlls::sources::gen_lib::SourceImplInfo &info)
{
  if (v4l2_init_)
  {
    return true;
  }

  try
  {
    v4l2_impl_ = std::make_unique< camera::CamImpl > (srcimpinfo_);
    v4l2_init_ = true;
  }
  catch (const std::exception &e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
    return false;
  }
  return v4l2_init_;
}


void
SourceImpl::deinit_device ()
{
  if (!v4l2_init_)
  {
    return;
  }
  v4l2_init_ = false;
}
}   // namespace dlls::sources::v4l2_vgen
