/**
\file       v4l2-vgen-jpeg-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/
#include "../v4l2-vgen-includes_int.hpp"
#include "v4l2-vgen-jpeg-impl.hpp"

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
namespace dlls::sources::v4l2_openmax_vgen::jpeg
{

JpegImpl::JpegImpl (DriverState* device_state) :
  devstate_ (device_state),
  init_device_ (false),
  jpeg_codec_interf_ (std::make_shared< JpegCodecImageInterf > ()),
  codec_props_ (nullptr),
  jpeg_frame_size_ (0),
  jpeg_beg_time_ (U3_GET_CURRENT_TIME)
{
  U3_ASSERT (devstate_);
}

JpegImpl::~JpegImpl ()
{
  // free_int();
}

IEvent::ptr
JpegImpl::get_interface_event ()
{
  auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< ::libs::events_base::runtime::interf::InterfCodecImageEvent > ();
  revnt->set_active (true);
  return evnt;
}

int
JpegImpl::get_filled_buf (::dlls::sources::gen_lib::syn::pkeys2bufs_type& bufs)
{
  lock_type lock (mtx_);

  if (ready_jpeg_bufs_.empty ())
  {
    return 0;
  }


  auto& codec_buf = (*bufs)[::utils::dbufs::video::consts::offs::mjpg];
  U3_ASSERT (codec_buf);

  auto source_buf = ready_jpeg_bufs_.front ();
  ready_jpeg_bufs_.pop_front ();
  codec_buf->swap (*source_buf);
  source_buf->set_flag (::utils::dbufs::BufFlags::empty, true);
  codec_buf->set_flag (::utils::dbufs::BufFlags::empty, false);
  empty_jpeg_bufs_.push_back (source_buf);
  return 1;
}

void
JpegImpl::update_source_info (const ::dlls::sources::gen_lib::SourceImplInfo& info)
{
  lock_type lock (mtx_);
  auto      buf_alocator = info.links_props_.pdriver2buf_->impl ();

  std::copy (ready_jpeg_bufs_.begin (), ready_jpeg_bufs_.end (), std::back_inserter (empty_jpeg_bufs_));
  ready_jpeg_bufs_.clear ();
  empty_jpeg_bufs_.resize (info.capture_props_.capi_.count_preload_frame_);

  for (auto& buf : empty_jpeg_bufs_)
  {
    if (!buf)
    {
      buf = buf_alocator->get ();
    }
  }
  return;
}

bool
JpegImpl::init_device (const ::dlls::sources::gen_lib::SourceImplInfo& info)
{
  lock_type lock (mtx_);

  if (init_device_)
  {
    return true;
  }

  int           exit_code = EX_OK;
  MMAL_STATUS_T status    = MMAL_SUCCESS;

  U3_CHECK (
    MMAL_SUCCESS == helpers::create_encoder_comp_ (devstate_),
    "create jpeg encoder");


  MMAL_PORT_T* still_port   = devstate_->cam_comp_->output[helpers::consts::indx_camera_port_capture];
  MMAL_PORT_T* einput_port  = devstate_->encoder_comp_ ? devstate_->encoder_comp_->input[0] : nullptr;
  MMAL_PORT_T* eoutput_port = devstate_->encoder_comp_ ? devstate_->encoder_comp_->output[0] : nullptr;

  U3_ASSERT (einput_port);
  U3_ASSERT (eoutput_port);

  MMAL_ES_FORMAT_T* still_format = still_port->format;

  still_format->encoding = mmal_util_rgb_order_fixed (still_port) ? MMAL_ENCODING_RGB24 : MMAL_ENCODING_BGR24;
  // still_format->encoding = MMAL_ENCODING_RGB24;      //debug

  CHECK_STATUS (mmal_port_format_commit (still_port), "camera still format couldn't be set");
  CHECK_STATUS (helpers::connect_ports (still_port, einput_port, &devstate_->encoder_connect_), "Failed to connect camera video port to encoder input");
  CHECK_STATUS (mmal_port_parameter_set_uint32 (devstate_->cam_comp_->control, MMAL_PARAMETER_SHUTTER_SPEED, devstate_->cam_params_.shutter_speed), "Failed to set shutter speed, ");

  eoutput_port->userdata = ::libs::utility::casts::reinterpret_cast_helper< MMAL_PORT_USERDATA_T* > (devstate_);

  CHECK_STATUS (mmal_port_enable (eoutput_port, helpers::encoder_buf_callback), "enable encoder port");

  const std::int32_t num = mmal_queue_length (devstate_->encoder_pool_->queue);
  for (int q = 0; q < num; q++)
  {
    MMAL_BUFFER_HEADER_T* buf = mmal_queue_get (devstate_->encoder_pool_->queue);
    U3_CHECK (buf, "Unable to get a required buf from pool queue ");
    CHECK_STATUS (mmal_port_send_buf (eoutput_port, buf), "Unable to send a buf to encoder output port");
  }


  CHECK_STATUS (mmal_port_parameter_set_boolean (still_port, MMAL_PARAMETER_CAPTURE, 1), "Failed to start capture video port");

  init_device_ = true;

  return init_device_;
}

void
JpegImpl::deinit_device ()
{
  // lock_type lock(mtx_);
  if (!init_device_)
  {
    return;
  }

  helpers::check_disable_port (devstate_->encoder_comp_->output[0]);
  helpers::destroy_encoder_comp_ (devstate_);
  init_device_     = false;
  jpeg_frame_size_ = 0;
  return;
}

void
JpegImpl::encoder_buf_callback (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf)
{
  lock_type     lock (mtx_);
  MMAL_STATUS_T status   = MMAL_SUCCESS;
  bool          complete = false;
  DriverState*  devstate = ::libs::utility::casts::reinterpret_cast_helper< DriverState* > (port->userdata);

  U3_CHECK (devstate, "Received a camera still buf callback with no state");


  int        bytes_written  = 0;
  int        bytes_to_write = buf->length;
  const auto width          = port->format->es->video.width;
  const auto height         = port->format->es->video.height;

  if (devstate->onlyLuma)
  {
    bytes_to_write = vcos_min (buf->length, width * height);
  }

  if (!empty_jpeg_bufs_.empty ())
  {
    auto buf = empty_jpeg_bufs_.front ();

    if (0 == jpeg_frame_size_)
    {
      time_type end       = U3_GET_CURRENT_TIME;
      auto      diff_time = end - jpeg_beg_time_;

      buf->buf_alloc (::utils::dbufs::video::AllocParams (
        2048,
        2048,
        // width,
        // height,
        2048 * 3,
        ::libs::utility::uids::minor::id_val::y8));

      jpeg_frame_size_ = sizeof (HeaderIFrame);
      ::utils::dbufs::video::helpers::replace_buf_params (*buf, 0, jpeg_frame_size_);

      auto* head = ::libs::utility::casts::reinterpret_cast_helper< HeaderIFrame* > (buf->get_buf ());
      head->reset ();

      head->base_part_.set_guid_codec (::libs::utility::uids::codecs::mjpeg);
      head->base_part_.style_         = ::dlls::codecs::codec_gen::Frames::iframe;
      head->base_part_.sinfo_.width_  = width;
      head->base_part_.sinfo_.height_ = height;
      head->base_part_.sinfo_.stride_ = width;
      head->cinfo_.nocolor_           = false;
      // head->base_part_.size_compress_ = jpeg_frame_size_;
      // head->csize_                    = jpeg_frame_size_;
    }

    auto data = buf->get_buf ();

    mmal_buf_header_mem_lock (buf);
    memcpy (data + jpeg_frame_size_, buf->data, bytes_to_write);
    mmal_buf_header_mem_unlock (buf);

    jpeg_frame_size_ += bytes_to_write;
    buf->set_flag (::utils::dbufs::BufFlags::empty, false);
    buf->set_mem_var (::utils::dbufs::MemVars::size_data, jpeg_frame_size_);
  }
  // Check end of frame or error
  if (buf->flags & (MMAL_BUFFER_HEADER_FLAG_FRAME_END | MMAL_BUFFER_HEADER_FLAG_TRANSMISSION_FAILED))
  {
    if (!empty_jpeg_bufs_.empty ())
    {
      auto buf = empty_jpeg_bufs_.front ();

      empty_jpeg_bufs_.pop_front ();
      ready_jpeg_bufs_.push_back (buf);

      auto* head = ::libs::utility::casts::reinterpret_cast_helper< HeaderIFrame* > (buf->get_buf ());

      head->base_part_.size_compress_ = jpeg_frame_size_ - sizeof (HeaderIFrame);
      head->csize_                    = jpeg_frame_size_ - sizeof (HeaderIFrame);

      // head->csize_ = jpeg_frame_size_;
      // head->coff_ = from_header;
      // from_header += jpeg_size;
      // out_size += jpeg_size;
      //  U3_ASSERT(out_size > 0);

      // head->base_part_.size_compress_ = out_size;
      // head->base_part_.sinfo_.width_ = lsrc.width_;
      // head->base_part_.sinfo_.height_ = lsrc.height_;
      // head->base_part_.sinfo_.stride_ = lsrc.width_ * (colored ? 3 : 1);

      // head->cinfo_ = cinfo_.plane_;
      // head->cinfo_.nocolor_ = colored ? false : true; //переопределяем по факту, т.к. у пользователя может быть установлено сжатие с цветом при его фактическом отсутствии и наоборот.

      // std::copy(
      //   vcodec_mjpg::consts::guid_codec.get_vals().begin(),????
      // vcodec_mjpg::consts::guid_codec.get_vals().end(),
      // head->base_part_.guid_);
    }

    complete         = true;
    jpeg_frame_size_ = 0;
    jpeg_beg_time_   = U3_GET_CURRENT_TIME;
  }

  mmal_buf_header_release (buf);

  if (port->is_enabled)
  {
    MMAL_BUFFER_HEADER_T* new_buf = mmal_queue_get (devstate->encoder_pool_->queue);

    U3_CHECK (new_buf, "received null buf");
    // and back to the port from there.
    if (new_buf)
    {
      CHECK_STATUS (mmal_port_send_buf (port, new_buf), "mmal_port_send_buf");
    }
  }

  if (complete)
  {
    MMAL_PORT_T* camera_video_port = devstate_->cam_comp_->output[helpers::consts::indx_camera_port_capture];
    MMAL_PORT_T* encoder_output    = devstate_->encoder_comp_->output[0];

    if (jpeg_codec_interf_->is_codec_property_update ())
    {
      CHECK_STATUS (mmal_port_parameter_set_boolean (camera_video_port, MMAL_PARAMETER_CAPTURE, 0), "Failed to start capture");

      VideoCodecProp::craw_ptr props = jpeg_codec_interf_->get_codec_property ();

      const std::uint32_t val = ::libs::utility::utils::ret_check_bound (U3_CAST_UINT32 (props->plane_.quality_), 1U, 100U);

      CHECK_STATUS (mmal_port_parameter_set_uint32 (encoder_output, MMAL_PARAMETER_JPEG_Q_FACTOR, val), "update jpeg quality");
    }

    // Enable the camera still output port and tell it its callback function
    // U3_CHECK(MMAL_SUCCESS == mmal_port_enable(camera_video_port, ::encoder_buf_callback), "Failed to setup camera output");
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
    // There is a possibility that shutter needs to be set each loop.
    MMAL_STATUS_T port_status = mmal_port_parameter_set_uint32 (
      devstate_->cam_comp_->control,
      MMAL_PARAMETER_SHUTTER_SPEED,
      devstate_->cam_params_.shutter_speed);

    U3_CHECK (MMAL_SUCCESS == helpers::mmal_status_to_int (port_status), "Unable to set shutter speed");
#  endif
    // Send all the bufs to the camera output port
    const std::int32_t num = mmal_queue_length (devstate_->encoder_pool_->queue);

    for (int q = 0; q < num; q++)
    {
      MMAL_BUFFER_HEADER_T* buf = mmal_queue_get (devstate_->encoder_pool_->queue);

      U3_CHECK (buf, "Unable to get a required buf d from pool queue");
      CHECK_STATUS (mmal_port_send_buf (camera_video_port, buf), "Unable to send a buf to camera output port");
    }

    CHECK_STATUS (mmal_port_parameter_set_boolean (camera_video_port, MMAL_PARAMETER_CAPTURE, 1), "Failed to start capture");
  }

  return;
}

}   // namespace dlls::sources::v4l2_openmax_vgen::jpeg
#endif
