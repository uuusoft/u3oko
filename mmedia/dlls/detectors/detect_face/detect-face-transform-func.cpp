/**
\file       detect-face-transform-funct.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_detect_face
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "detect-face-includes_int.hpp"
#include "detect-face-info-filter-dll.hpp"
#include "detect-face-filter-dll.hpp"

namespace dlls::detectors::detect_face
{
#if 0
void
Filter::convert_buf2rgb24 (syn::IVideoBuf::craw_ptr psrc, syn::IVideoBuf::raw_ptr pdst)
{
  // utils::dbufs::video::helpers::fill<short>( psrc, []( int indxx, int indxy, std::int16_t& val ) { val = rand() % 100 + 100;  return; } );
  // utils::dbufs::video::helpers::fill<short>( psrc, []( int indxx, int indxy, std::int16_t& val ) { val = counter % 100 + 100;  return; } );

  pdst->buf_alloc (
    ::utils::dbufs::video::AllocBufInfo (
      psrc->get_dim_vars (),
      ::libs::helpers::uids::minor::id_val::y8));

  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.push_back (syn::ProxyBuf (psrc, "src dlls::detectors::detect_face"));
  cinfo.dsts_.push_back (syn::ProxyBuf (pdst, "dst dlls::detectors::detect_face"));

  ::libs::optim::mcalls::InfoMFunct tfunct (&fx16_x8_);
  pthreads_->mthreads_call (
    id_obj_,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
#endif
#if 0
void
Filter::save_buf2file (
  const std::string&      file_name,
  std::int32_t            counter,
  std::int32_t            quality,
  syn::IVideoBuf::raw_ptr psrc)
{
  U3_CHECK (quality >= 0 && quality <= 100, "check quality");

  const syn::ProxyBuf lsrc (temp_buf_.get (), "temp_buf dlls::detectors::detect_face");
  const std::uint8_t*  cur_buf   = utils::dbufs::video::helpers::get_const_data (temp_buf_.get ());
  const std::int32_t   in_format  = TJPF_GRAY;
  const std::int32_t   out_format = TJSAMP_GRAY;
  unsigned long        jpeg_size  = 0;
  unsigned long        max_size   = tjBufSize (lsrc.width_, lsrc.height_, out_format);

  // std::generate( cur_buf, cur_buf + lsrc.stride_ * lsrc.height_, []()->std::uint8_t { return rand() % 100 + 100; } );
  // std::generate( cur_buf, cur_buf + lsrc.stride_ * lsrc.height_, []()->std::uint8_t { return 100; } );
  if (!hjpeg_)
  {
    hjpeg_ = tjInitCompress ();
  }

  if (!jpeg_buf_ || max_size > size_jpeg_buf_)
  {
    if (jpeg_buf_)
    {
      tjFree (jpeg_buf_);
      jpeg_buf_ = nullptr;
    }

    jpeg_buf_      = tjAlloc (U3_CAST_INT32 (max_size));
    size_jpeg_buf_ = max_size;
  }

  const std::int32_t res_jpeg = tjCompress2 (
    hjpeg_,
    U3_CAST_REINTERPRET< const std::uint8_t* > (cur_buf),
    lsrc.width_,
    lsrc.stride_,
    lsrc.height_,
    in_format,
    &jpeg_buf_,
    &jpeg_size,
    out_format,
    100,
    TJFLAG_NOREALLOC | TJFLAG_FASTDCT | TJFLAG_BOTTOMUP);

  if (-1 == res_jpeg)
  {
    char* jerr = tjGetErrorStr ();
    U3_THROW_EXCEPTION ((std::string ("jpeg coder, ") + std::string (jerr ? jerr : "unknow")).c_str ());
  }

  std::ofstream file (file_name.c_str (), std::ios_base::ate | std::ios_base::binary);

  file.write (U3_CAST_REINTERPRET< const char* > (jpeg_buf_), jpeg_size);
  file.flush ();
}
#endif

void
Filter::itransform (syn::TransformInfo& info)
{
  syn::IVideoBuf::raw_ptr psrc = (*pbuf_)[finfo_.rprops_->bufs_.indx_sbuf_];
  if (!psrc)
  {
    U3_XLOG_DBG ("FACE DETECTOR SKIP if (!psrc)")
    return;
  }


#ifndef U3_SKIP_DLIB
  dlib::array2d< std::uint8_t > img;

#  if 0
  static std::int32_t counter   = 20;
  const std::string   file_path = "c:/imgs/dump_" + std::to_string (counter) + ".jpg";
  dlib::load_image (img, file_path);
  ++counter;
#  endif

  temp_buf_->clone (psrc, 100.0f);
  utils::dbufs::video::helpers::invert_rows (temp_buf_.get ());
  helpers::copy2dlib (temp_buf_.get (), img);

  // Make the image bigger by a factor of two.  This is useful since
  // the face detector looks for faces that are about 80 by 80 pixels
  // or larger.  Therefore, if you want to find faces that are smaller
  // than that then you need to upsample the image as we do here by
  // calling pyramid_up().  So this will allow it to detect faces that
  // are at least 40 by 40 pixels in size.  We could call pyramid_up()
  // again to find even smaller faces, but note that every time we
  // upsample the image we make the detector run slower since it must
  // process a larger image.
  // dlib::pyramid_up( img );

  // Now tell the face detector to give us a list of bounding boxes
  // around all the faces it can find in the image.
  // std::vector< dlib::rectangle > faces = finfo_.detector_ (img);
  auto faces = finfo_.detector_ (img);
  if (faces.empty ())
  {
    U3_XLOG_DBG ("FACE DETECTOR SKIP face not found")
    return;
  }

  for (std::size_t i = 0; i < faces.size (); ++i)
  {
    const auto& face = faces[i];
    U3_LOG_DATA_DEV ("Face" + VTOLOG (i) + " from" + VTOLOG (faces.size ()) + VTOLOG (face.left ()) + VTOLOG (face.top ()) + VTOLOG (face.width ()) + VTOLOG (face.height ()));
  }

  ::libs::events::IEvent::ptr rmsg;
  U3_CHECK (::libs::iproperties::helpers::create_event< syn::FaceDetect > (rmsg), "FaceDetect");
  info.frame_events_->push_back (rmsg);
#endif
}
}   // namespace dlls::detectors::detect_face
