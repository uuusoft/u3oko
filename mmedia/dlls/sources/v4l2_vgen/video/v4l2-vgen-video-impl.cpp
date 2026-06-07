/**
\file       v4l2-vgen-video-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.02.2026
\project    u3_v4l2_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../v4l2-vgen-includes_int.hpp"
#include "v4l2-vgen-video-impl.hpp"

// old shit
#ifdef U3_FAKE_DISABLE
namespace dlls::sources::v4l2_vgen::video
{
MMAL_STATUS_T
create_video_component (DriverState* state)
{
  MMAL_COMPONENT_T* video        = nullptr;
  MMAL_PORT_T*      video_input  = nullptr;
  MMAL_PORT_T*      video_output = nullptr;
  MMAL_STATUS_T     status       = MMAL_SUCCESS;

  CHECK_STATUS (mmal_component_create (MMAL_COMPONENT_DEFAULT_VIDEO_ENCODER, &video), "Unable to create video component");

  if (!video->input_num || !video->output_num)
  {
    status = MMAL_ENOSYS;
    U3_XLOG_WARN ("video doesn't have input/output ports" + VTOLOG (status));
    return status;
  }

  video_input  = video->input[0];
  video_output = video->output[0];

  mmal_format_copy (video_output->format, video_input->format);

  video_output->format->encoding = state->encoding_;
  // video_output->buf_size      = video_output->buf_size_recommended;

  switch (state->encoding_)
  {
  case MMAL_ENCODING_H264: {
    const std::int32_t max_bitrate = state->level_ == MMAL_VIDEO_LEVEL_H264_4 ? consts::max_bitrate_x264_level4 : consts::max_bitrate_x264_level42;
    state->bitrate_                = state->bitrate_ > max_bitrate ? max_bitrate : state->bitrate_;
    video_output->buf_size         = video_output->buf_size_recommended;
    break;
  }
  case MMAL_ENCODING_MJPEG:
    state->bitrate_        = state->bitrate_ > consts::max_bitrate_mjpeg ? consts::max_bitrate_mjpeg : state->bitrate_;
    video_output->buf_size = 256 << 10;
    break;
  default:
    U3_XLOG_WARN ("unknown encoding" + VTOLOG (state->encoding_));
    break;
  }

  auto props = state->video_->get_codec_interf ()->get_codec_property ();

  {
    video_output->buf_size = video_output->buf_size < video_output->buf_size_min ? video_output->buf_size_min : video_output->buf_size;
    video_output->buf_num  = video_output->buf_num_recommended;
    video_output->buf_num  = video_output->buf_num < video_output->buf_num_min ? video_output->buf_num_min : video_output->buf_num;

    MMAL_ES_FORMAT_T* format = video_output->format;

    format->bitrate                  = U3_CAST_UINT32 (state->bitrate_ * props->plane_.quality_ / 100.0F);
    format->es->video.frame_rate.num = 0;
    format->es->video.frame_rate.den = 1;
    format->es->video.width          = VCOS_ALIGN_UP (state->width, 32);
    format->es->video.height         = VCOS_ALIGN_UP (state->height, 16);
    format->es->video.crop.x         = 0;
    format->es->video.crop.y         = 0;
    format->es->video.width          = state->width;
    format->es->video.height         = state->height;
    format->es->video.frame_rate     = MMAL_RATIONAL_T { 30, 1 };
    format->es->video.frame_rate     = MMAL_RATIONAL_T { 0, 1 };   // We need to set the frame rate on output to 0, to ensure it gets updated correctly from the input framerate when port connected

    // video_output->format->bitrate                  = U3_CAST_UINT32 (state->bitrate_ * 1.0F / 100.0F); //debug
  }

  CHECK_STATUS (mmal_port_format_commit (video_output), "Unable to set format on video output port");
  CHECK_STATUS (mmal_port_parameter_set_boolean (video_input, MMAL_PARAMETER_VIDEO_IMMUTABLE_INPUT, state->immutable_video_input_), "set immutable_video_input_");

#  if 0
   //set INLINE HEADER flag to generate SPS and PPS for every IDR if requested
   if (mmal_port_parameter_set_boolean(encoder_output, MMAL_PARAMETER_VIDEO_ENCODE_INLINE_HEADER, state->bInlineHeaders) != MMAL_SUCCESS)
   {
      vcos_log_error("to set INLINE HEADER FLAG parameters");
      // Continue rather than abort..
   }

   //set INLINE VECTORS flag to request motion vector estimates
   if (state->encoding == MMAL_ENCODING_H264 &&
       mmal_port_parameter_set_boolean(encoder_output, MMAL_PARAMETER_VIDEO_ENCODE_INLINE_VECTORS, state->inlineMotionVectors) != MMAL_SUCCESS)
   {
      vcos_log_error("to set INLINE VECTORS parameters");
      // Continue rather than abort..
   }

   // Adaptive intra refresh settings
   if (state->encoding == MMAL_ENCODING_H264 &&
       state->intra_refresh_type != -1)
   {
      MMAL_PARAMETER_VIDEO_INTRA_REFRESH_T  param;
      param.hdr.id = MMAL_PARAMETER_VIDEO_INTRA_REFRESH;
      param.hdr.size = sizeof(param);

      // Get first so we don't overwrite anything unexpectedly
      status = mmal_port_parameter_get(encoder_output, &param.hdr);
      if (status != MMAL_SUCCESS)
      {
         vcos_log_warn("Unable to get existing H264 intra-refresh values. Please update your firmware");
         // Set some defaults, don't just pass random stack data
         param.air_mbs = param.air_ref = param.cir_mbs = param.pir_mbs = 0;
      }

      param.refresh_mode = state->intra_refresh_type;

      //if (state->intra_refresh_type == MMAL_VIDEO_INTRA_REFRESH_CYCLIC_MROWS)
      //   param.cir_mbs = 10;

      status = mmal_port_parameter_set(encoder_output, &param.hdr);
      if (status != MMAL_SUCCESS)
      {
         vcos_log_error("Unable to set H264 intra-refresh values");
         goto error;
      }
   }

#  endif
  //  Enable component
  CHECK_STATUS (mmal_component_enable (video), "Unable to enable video video");

  //  Create pool of buf headers for the output port to consume
  MMAL_POOL_T* pool = mmal_port_pool_create (video_output, video_output->buf_num, video_output->buf_size);
  if (!pool)
  {
    U3_XLOG_WARN ("Failed to create buf header pool for video output port name=" + std::string (video_output->name));
  }

  state->video_pool_ = pool;
  state->video_comp_ = video;
  return status;
}
/**
 * Destroy the encoder component
 *
 * @param state Pointer to state control struct
 *
 */
void
destroy_video_component (DriverState* state)
{
  if (state->video_connect_)
  {
    mmal_connection_destroy (state->video_connect_);
    state->video_connect_ = nullptr;
  }

  // Get rid of any port bufs first
  if (state->video_pool_)
  {
    mmal_port_pool_destroy (state->video_comp_->output[0], state->video_pool_);
  }

  if (state->video_comp_)
  {
    mmal_component_disable (state->video_comp_);
    mmal_component_destroy (state->video_comp_);
    state->video_comp_ = nullptr;
  }
  return;
}


VideoImpl::VideoImpl (DriverState* device_state) :
  devstate_ (device_state),
  init_device_ (false),
  video_codec_interf_ (std::make_shared< VideoCodecInterf > ()),
  codec_props_ (nullptr),
  video_frame_size_ (0),
  video_beg_time_ (U3_GET_CURRENT_TIME)
{
  U3_ASSERT (devstate_);
}

VideoImpl::~VideoImpl ()
{
  // free_int();
}

IEvent::ptr
VideoImpl::get_interface_event ()
{
  IEvent::ptr rmsg;
  auto        dmsg = ::libs::iproperties::helpers::create_event< ::libs::ievents::runtime::interf::InterfCodecImageEvent > (rmsg);
  dmsg->set_active (true);
  return rmsg;
}


VideoCodecInterf::ptr
VideoImpl::get_codec_interf ()
{
  return video_codec_interf_;
}


int
VideoImpl::get_filled_buf (::dlls::sources::gen_lib::syn::pkeys2bufs_type& bufs)
{
  lock_type lock (mtx_);
  if (ready_video_bufs_.empty ())
  {
    return 0;
  }

  auto& codec_buf = (*bufs)[::utils::dbufs::video::consts::offs::mjpg];
  U3_ASSERT (codec_buf);

  auto source_buf = ready_video_bufs_.front ();
  ready_video_bufs_.pop_front ();
  codec_buf->swap (*source_buf);
  source_buf->set_flag (::utils::dbufs::BufFlags::empty, true);
  codec_buf->set_flag (::utils::dbufs::BufFlags::empty, false);
  empty_video_bufs_.push_back (source_buf);
  return 1;
}

void
VideoImpl::update_source_info (const ::dlls::sources::gen_lib::SourceImplInfo& info)
{
  lock_type lock (mtx_);
  auto      buf_alocator = info.links_props_.pdriver2buf_->impl ();

  std::copy (ready_video_bufs_.begin (), ready_video_bufs_.end (), std::back_inserter (empty_video_bufs_));
  ready_video_bufs_.clear ();
  empty_video_bufs_.resize (info.capture_props_.capi_.count_preload_frame_);

  for (auto& buf : empty_video_bufs_)
  {
    if (!buf)
    {
      buf = buf_alocator->get ();
    }
  }
  return;
}

bool
VideoImpl::init_device (const ::dlls::sources::gen_lib::SourceImplInfo& info)
{
  lock_type     lock (mtx_);
  MMAL_STATUS_T status = MMAL_SUCCESS;

  if (init_device_)
  {
    return true;
  }

  CHECK_STATUS_RET (create_video_component (devstate_), "create video");

  MMAL_PORT_T* cap_port     = devstate_->cam_comp_->output[helpers::consts::indx_camera_port_video];
  MMAL_PORT_T* einput_port  = devstate_->video_comp_ ? devstate_->video_comp_->input[0] : nullptr;
  MMAL_PORT_T* eoutput_port = devstate_->video_comp_ ? devstate_->video_comp_->output[0] : nullptr;

  U3_ASSERT (einput_port);
  U3_ASSERT (eoutput_port);

  MMAL_ES_FORMAT_T* still_format = cap_port->format;

  still_format->encoding = mmal_util_rgb_order_fixed (cap_port) ? MMAL_ENCODING_RGB24 : MMAL_ENCODING_BGR24;
  // still_format->encoding = MMAL_ENCODING_RGB24;      //debug

  CHECK_STATUS (mmal_port_format_commit (cap_port), "camera video format couldn't be set");
  CHECK_STATUS (helpers::connect_ports (cap_port, einput_port, &devstate_->video_connect_), "Failed to connect camera video port to video input");
  CHECK_STATUS (mmal_port_parameter_set_uint32 (devstate_->cam_comp_->control, MMAL_PARAMETER_SHUTTER_SPEED, devstate_->cam_params_.shutter_speed), "Failed to set shutter speed");

  eoutput_port->userdata = ::libs::helpers::casts::reinterpret_cast_helper< struct MMAL_PORT_USERDATA_T* > (devstate_);

  CHECK_STATUS (mmal_port_enable (eoutput_port, buf_callback), "enable video port");

  const std::int32_t num = mmal_queue_length (devstate_->video_pool_->queue);
  for (int q = 0; q < num; q++)
  {
    MMAL_BUFFER_HEADER_T* buf = mmal_queue_get (devstate_->video_pool_->queue);
    U3_CHECK (buf, "Unable to get a required buf from pool queue ");
    CHECK_STATUS (mmal_port_send_buf (eoutput_port, buf), "Unable to send a buf to video output port");
  }

  CHECK_STATUS (mmal_port_parameter_set_boolean (cap_port, MMAL_PARAMETER_CAPTURE, 1), "Failed to start capture video port");
  init_device_ = true;
  return init_device_;
}

void
VideoImpl::deinit_device ()
{
  // lock_type lock(mtx_);
  if (!init_device_)
  {
    return;
  }

  lock_type lock (mtx_);
  helpers::check_disable_port (devstate_->video_comp_->output[0]);
  destroy_video_component (devstate_);
  init_device_      = false;
  video_frame_size_ = 0;
  return;
}

void
VideoImpl::buf_callback_int (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf)
{
  lock_type     lock (mtx_);
  MMAL_STATUS_T status   = MMAL_SUCCESS;
  bool          complete = false;
  DriverState*  devstate = reinterpret_cast< DriverState* > (port->userdata);

  U3_CHECK (devstate, "Received a camera still buf callback with no state");

  int        bytes_written  = 0;
  int        bytes_to_write = buf->length;
  const auto width          = port->format->es->video.width;
  const auto height         = port->format->es->video.height;

  if (devstate->onlyLuma)
  {
    bytes_to_write = vcos_min (buf->length, width * height);
  }

  if (!empty_video_bufs_.empty ())
  {
    auto buf = empty_video_bufs_.front ();

    if (0 == video_frame_size_)
    {
      time_type  end        = U3_GET_CURRENT_TIME;
      auto       diff_time  = end - video_beg_time_;
      const auto req_stride = width * ::libs::helpers::uids::helpers::get_count_bytes_from_format (::libs::helpers::uids::minor::id_val::rgb32);

      buf->buf_alloc (::utils::dbufs::video::AllocBufInfo (width, height, req_stride, ::libs::helpers::uids::minor::id_val::y8));

      video_frame_size_ = sizeof (HeaderIFrame);
      //::utils::dbufs::video::helpers::override_data (*buf, 0, video_frame_size_);
      HeaderIFrame* head = U3_CAST_CODECS< HeaderIFrame* > (buf->get_buf ());

      head->reset ();

      // head->base_part_.set_guid_codec (::libs::helpers::uids::codecs::x264);
      head->base_part_.set_guid_codec (::libs::helpers::uids::codecs::mjpeg);
      head->base_part_.style_         = ::dlls::codecs::codec_gen::Frames::iframe;
      head->base_part_.sinfo_.width_  = width;
      head->base_part_.sinfo_.height_ = height;
      head->base_part_.sinfo_.stride_ = width;
      head->cinfo_.nocolor_           = false;
    }

    auto data = buf->get_buf ();

    mmal_buf_header_mem_lock (buf);
    memcpy (data + video_frame_size_, buf->data, bytes_to_write);
    mmal_buf_header_mem_unlock (buf);

    video_frame_size_ += bytes_to_write;
    buf->set_flag (::utils::dbufs::BufFlags::empty, false);
    buf->set_mem_var (::utils::dbufs::MemVars::size_data, video_frame_size_);
  }

  // Check end of frame or error
  if (buf->flags & (MMAL_BUFFER_HEADER_FLAG_FRAME_END | MMAL_BUFFER_HEADER_FLAG_TRANSMISSION_FAILED))
  {
    if (!empty_video_bufs_.empty ())
    {
      auto buf = empty_video_bufs_.front ();

      empty_video_bufs_.pop_front ();
      ready_video_bufs_.push_back (buf);

      HeaderIFrame* head = U3_CAST_CODECS< HeaderIFrame* > (buf->get_buf ());

      head->base_part_.size_compress_ = video_frame_size_ - sizeof (HeaderIFrame);
      head->csize_                    = video_frame_size_ - sizeof (HeaderIFrame);

      // head->csize_ = video_frame_size_;
      // head->coff_ = from_header;
      // from_header += video_size;
      // out_size += video_size;
      //  U3_ASSERT(out_size > 0);

      // head->base_part_.size_compress_ = out_size;
      // head->base_part_.sinfo_.width_ = lsrc.width_;
      // head->base_part_.sinfo_.height_ = lsrc.height_;
      // head->base_part_.sinfo_.stride_ = lsrc.width_ * (colored ? 3 : 1);

      // head->cinfo_ = cinfo_.plane_;
      // head->cinfo_.nocolor_ = colored ? false : true; //переопределяем по
      // факту, т.к. у пользователя может быть установлено сжатие с цветом при
      // его фактическом отсутствии и наоборот.

      // std::copy(
      //  vcodec_mjpg::consts::guid_codec.get_vals().begin(),???
      // vcodec_mjpg::consts::guid_codec.get_vals().end(),
      // head->base_part_.guid_);

      // U3_ASSERT(head->check());
    }

    complete          = true;
    video_frame_size_ = 0;
    video_beg_time_   = U3_GET_CURRENT_TIME;
  }

  mmal_buf_header_release (buf);

  if (port->is_enabled)
  {
    MMAL_BUFFER_HEADER_T* new_buf = mmal_queue_get (devstate->video_pool_->queue);

    U3_CHECK (new_buf, "received null buf");
    // and back to the port from there.
    if (new_buf)
    {
      CHECK_STATUS (mmal_port_send_buf (port, new_buf), "call mmal_port_send_buf");
    }
  }

  if (complete)
  {
    complete_bufs_int (port, buf);
  }
  return;
}


void
VideoImpl::complete_bufs_int (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf)
{
  MMAL_STATUS_T status     = MMAL_SUCCESS;
  MMAL_PORT_T*  video_port = devstate_->cam_comp_->output[helpers::consts::indx_camera_port_video];
  // MMAL_PORT_T*  video_output = devstate_->video_comp_->output[0];
  // MMAL_PORT_T*  video_input  = devstate_->video_comp_->input[0];

  if (video_codec_interf_->is_codec_property_update ())
  {
    update_codec_props_int (port, buf);
  }
  // Enable the camera still output port and tell it its callback function
  // U3_CHECK(MMAL_SUCCESS == mmal_port_enable(video_port, ::buf_callback), "Failed to setup camera output");
  // There is a possibility that shutter needs to be set each loop.
  // CHECK_STATUS( mmal_port_parameter_set_uint32( devstate_->cam_comp_->control, MMAL_PARAMETER_SHUTTER_SPEED, devstate_->cam_params_.shutter_speed), "Unable to set shutter speed");

  // Send all the bufs to the camera output port
  free_bufs_int (port, buf);

  if (devstate_->burstCaptureMode)
  {
    // mmal_port_parameter_set_boolean(devstate_->cam_comp_->control, MMAL_PARAMETER_CAMERA_BURST_CAPTURE, 1);
  }

  CHECK_STATUS (mmal_port_parameter_set_boolean (video_port, MMAL_PARAMETER_CAPTURE, 1), "Failed to start capture");

  return;
}


void
VideoImpl::free_bufs_int (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf)
{
  MMAL_STATUS_T      status     = MMAL_SUCCESS;
  const std::int32_t count_bufs = mmal_queue_length (devstate_->video_pool_->queue);
  MMAL_PORT_T*       video_port = devstate_->cam_comp_->output[helpers::consts::indx_camera_port_video];
  // MMAL_PORT_T*  video_output = devstate_->video_comp_->output[0];
  // MMAL_PORT_T*  video_input  = devstate_->video_comp_->input[0];

  for (int indx = 0; indx < count_bufs; ++indx)
  {
    MMAL_BUFFER_HEADER_T* buf = mmal_queue_get (devstate_->video_pool_->queue);
    U3_CHECK (buf, "Unable to get a required buf d from pool queue");
    CHECK_STATUS (mmal_port_send_buf (video_port, buf), "Unable to send a buf to camera output port");
  }
  return;
}


void
VideoImpl::update_codec_props_int (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf)
{
  MMAL_STATUS_T status = MMAL_SUCCESS;
  // MMAL_PORT_T*  video_port  = devstate_->cam_comp_->output[helpers::consts::indx_camera_port_video];
  // MMAL_PORT_T*  video_output = devstate_->video_comp_->output[0];
  // MMAL_PORT_T*  video_input  = devstate_->video_comp_->input[0];
  /*
  VideoCodecProp::craw_ptr props = video_codec_interf_->get_codec_property ();

  CHECK_STATUS (mmal_port_parameter_set_boolean (video_port, MMAL_PARAMETER_CAPTURE, 0), "Failed to start capture");
  mmal_format_copy (video_output->format, video_input->format);
  //state->encoding_               = MMAL_ENCODING_H264;
  //state->encoding_               = MMAL_ENCODING_MJPEG;
  video_output->format->encoding = devstate_->encoding_;

  if (devstate_->encoding_ == MMAL_ENCODING_H264)
    {
      if (devstate_->level_ == MMAL_VIDEO_LEVEL_H264_4)
        {
          if (devstate_->bitrate_ > helpers::max_bitrate_x264_level4)
            {
              devstate_->bitrate_ = helpers::max_bitrate_x264_level4;
            }
        }
      else
        {
          if (devstate_->bitrate_ > helpers::max_bitrate_x264_level42)
            {
              devstate_->bitrate_ = helpers::max_bitrate_x264_level42;
            }
        }
    }
  else if (devstate_->encoding_ == MMAL_ENCODING_MJPEG)
    {
      if (devstate_->bitrate_ > helpers::max_bitrate_mjpeg)
        {
          devstate_->bitrate_ = helpers::max_bitrate_mjpeg;
        }
    }

  video_output->format->bitrate = U3_CAST_UINT32 (devstate_->bitrate_ * props->plane_.quality_ / 100.0F);

  if (devstate_->encoding_ == MMAL_ENCODING_H264)
    video_output->buf_size = video_output->buf_size_recommended;
  else
    video_output->buf_size = 256 << 10;

  if (video_output->buf_size < video_output->buf_size_min)
    {
      video_output->buf_size = video_output->buf_size_min;
    }

  video_output->buf_num = video_output->buf_num_recommended;
  */
  // VideoCodecProp::craw_ptr props = video_codec_interf_->get_codec_property ();
  //
  // const std::uint32_t val = ::libs::helpers::utils::ret_check_bound<uint3-2_t> (U3_CAST_UINT32 (props->plane_.quality_), 1, 100);
  // CHECK_STATUS ( mmal_port_parameter_set_uint32 ( video_output, MMAL_PARAMETER_JPEG_Q_FACTOR, val), "update video quality");
  // CHECK_STATUS ( mmal_port_format_commit (video_output), "Unable to update format on video output port");

  return;
}


void
VideoImpl::buf_callback (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf)
{
  DriverState* devstate = ::libs::helpers::casts::reinterpret_cast_helper< DriverState* > (port->userdata);
  if (!devstate)
  {
    U3_LOG_DATA_WRN ("received empty user data");
    return;
  }

  devstate->video_->buf_callback_int (port, buf);
}

}   // namespace dlls::sources::v4l2_vgen::video

#endif
