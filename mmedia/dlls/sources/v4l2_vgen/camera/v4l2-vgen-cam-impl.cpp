/**
\file       v4l2-vgen-cam-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.02.2026
\project    u3_v4l2_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../v4l2-vgen-includes_int.hpp"
#include <string>
#include <functional>
#include <thread>
#include <cstdlib>
#include <dirent.h>
#include <ctime>
#include <cstring>

namespace dlls::sources::v4l2_vgen::camera
{
void
CamImpl::sync_runtime_props (const syn::VideoDriverCaptureProp &capprops)
{
  U3_CHECK (v4l2capture_, "CamImpl::sync_runtime_props");
  capparams_ = capprops.capi_;

  const auto runtime_width         = v4l2capture_->getWidth ();
  const auto runtime_height        = v4l2capture_->getHeight ();
  const auto runtime_fourcc_format = v4l2capture_->getFormat ();
  const auto runtime_format        = ::libs::helpers::uids::helpers::fourcc2idval (runtime_fourcc_format);

  if (capparams_.width_ != runtime_width ||
      capparams_.height_ != runtime_height ||
      capparams_.px_format_ != runtime_format)
  {
    U3_LOG_DATA_WRN ("failed set params to v4l2 device1" + VTOLOG (runtime_width) + VTOLOG (runtime_height) + VTOLOG (runtime_fourcc_format))
    U3_LOG_DATA_WRN ("failed set params to v4l2 device2" + libs::helpers::uids::helpers::get_readable_name (runtime_format))
    capparams_.width_     = runtime_width;
    capparams_.height_    = runtime_height;
    capparams_.px_format_ = runtime_format;
  }
}


CamImpl::CamImpl (const gen_lib::SourceImplInfo &props_info) :
  srcparams_ (props_info),
  v4l2capture_ (nullptr)
{
  const auto &capprops    = *srcparams_.capture_props_;
  const auto &device_name = v4l2_vgen::consts::dev_path + srcparams_.props_->device_name_;
  const auto  fourcc      = libs::helpers::uids::helpers::idval2fourcc (capprops.capi_.px_format_);
  U3_LOG_DATA_DBG ("create v4l2" + TOLOG (device_name));
  U3_LOG_DATA_DBG ("params v4l2 " + ::libs::helpers::uids::helpers::get_readable_name (capprops.capi_.px_format_) + VTOLOG (fourcc));
  U3_LOG_DATA_DBG ("params v4l2" + VTOLOG (capprops.capi_.width_) + VTOLOG (capprops.capi_.height_));
  U3_LOG_DATA_DBG ("params v4l2" + VTOLOG (capprops.capi_.fps_));

  V4L2DeviceParameters param (
    device_name.c_str (),
    fourcc,
    capprops.capi_.width_,
    capprops.capi_.height_,
    capprops.capi_.fps_,
    IOTYPE_MMAP);

  v4l2capture_.reset (V4l2Capture::create (param));
  // U3_CHECK (v4l2capture_, "FAILED create v4l2 device" + TOLOG (srcparams_.props_->device_name_));
  sync_runtime_props (capprops);
}


bool
CamImpl::is_init () const
{
  return v4l2capture_ ? true : false;
}


syn::IVideoBuf::ptr
CamImpl::get_buf ()
{
  std::scoped_lock lock (sync_);

  timeval       tv       = { 0, 100 };
  const int32_t read_res = v4l2capture_ ? v4l2capture_->isReadable (&tv) : -1;

  if (1 != read_res)
  {
    return syn::IVideoBuf::ptr ();
  }

  auto       ibuf         = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ();
  auto       new_buf      = ibuf->create (0);
  const auto bpp          = ::libs::helpers::uids::helpers::get_count_bytes_from_format (capparams_.px_format_);
  const auto stride       = capparams_.width_ * bpp;
  const auto align_stride = ::libs::helpers::mem::get_align16 (stride);

  new_buf->buf_alloc (
    ::utils::dbufs::video::AllocBufInfo (
      capparams_.width_,
      capparams_.height_,
      capparams_.px_format_,
      align_stride * capparams_.height_));

  U3_MARK_UNUSED const auto req_buf_size  = v4l2capture_->getBufferSize ();
  U3_MARK_UNUSED const auto temp_buf_size = (*new_buf)[utils::dbufs::MemVars::size_buf];

  U3_MARK_UNUSED const auto size_res = v4l2capture_->read (
    utils::dbufs::video::helpers::get_buf_as< char * > (new_buf.get ()),
    temp_buf_size);

  new_buf->set_mem_var (::utils::dbufs::MemVars::size_data, stride * capparams_.height_);
  new_buf->set_dim_var (utils::dbufs::video::Dims::stride, stride);
  return new_buf;
}


void
CamImpl::sync_correct_props (syn::VideoCorrectProp::craw_ptr correctprops)
{
  if (::libs::ievents::SelectorImpls::software == correctprops->hint_correct_impl_)
  {
    return;
  }

  std::scoped_lock lock (sync_);
  if (nullptr == v4l2capture_)
  {
    return;
  }

  auto convert = [] (const v4l2_queryctrl &queryctrl, float koeff) -> int32_t {
    const auto diff = queryctrl.maximum - queryctrl.minimum;
    if (koeff < 0.0F)
    {
      return queryctrl.minimum + diff * (koeff + 1.0F);
    }
    else if (koeff > 0.0F)
    {
      return queryctrl.maximum - diff * (1.0F - koeff);
    }
    return queryctrl.default_value;
  };

  const auto enable_correct = correctprops->get_using_state () != ::libs::events::PropertyUsings::disabled;

  const std::pair< int32_t, float > cids2koeffs[] = {
    { V4L2_CID_BRIGHTNESS, correctprops->bright_.first },
    { V4L2_CID_CONTRAST, correctprops->contrast_.first },
    { V4L2_CID_SATURATION, correctprops->saturation_.first },
    { V4L2_CID_HUE, correctprops->hue_.first },
    { V4L2_CID_GAMMA, correctprops->gamma_.first },
    { V4L2_CID_GAIN, correctprops->gain_.first },
    { V4L2_CID_EXPOSURE, correctprops->exposure_.first }
  };

  auto fd = v4l2capture_->getFd ();
  for (const auto &cid2koeff : cids2koeffs)
  {
    v4l2_queryctrl queryctrl;
    memset (&queryctrl, 0, sizeof (queryctrl));
    queryctrl.id = cid2koeff.first;

    if (-1 == ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl))
    {
      U3_LOG_DATA_WRN (VTOLOG (cid2koeff.first) + TOLOG (strerror (errno)));
      continue;
    }
    else if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)
    {
      U3_LOG_DATA_WRN (VTOLOG (cid2koeff.first) + " not supported");
      continue;
    }

    v4l2_control control;
    memset (&control, 0, sizeof (control));
    control.id    = cid2koeff.first;
    control.value = enable_correct ? U3_CAST_INT32 (convert (queryctrl, cid2koeff.second)) : queryctrl.default_value;
    // U3_LOG_DATA_DEV (VTOLOG (queryctrl.minimum) + VTOLOG (queryctrl.maximum) + VTOLOG (correctprops->bright_.first) + VTOLOG (control.value));
    if (-1 == ioctl (fd, VIDIOC_S_CTRL, &control))
    {
      U3_LOG_DATA_ERROR (VTOLOG (cid2koeff.first) + TOLOG (strerror (errno)));
    }
  }
}
}   // namespace dlls::sources::v4l2_vgen::camera
