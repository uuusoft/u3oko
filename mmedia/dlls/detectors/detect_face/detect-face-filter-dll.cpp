/**
\file       detect-face-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_detect_face
*/
#include "detect-face-includes_int.hpp"
#include "detect-face-info-filter-dll.hpp"
#include "detect-face-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::detectors::detect_face
{
Filter::~Filter ()
{
  if (jpeg_buf_)
  {
    tjFree (jpeg_buf_);
    jpeg_buf_      = nullptr;
    size_jpeg_buf_ = 0;
  }
  if (hjpeg_)
  {
    tjDestroy (hjpeg_);
    hjpeg_ = nullptr;
  }
}


void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  // count_if_ge_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCountIfGEAlg::val_key));
  fx16_x8_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX16_X8Alg::val_key));

  auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ();
  temp_buf_ = ibuf->create (0);
}


void
Filter::call_int (syn::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::init_pts (syn::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}


void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  //  add offset for active data and corrected active data correct frame
  itransform (info);
}


void
Filter::itransform (syn::TransformInfo& info)
{
  syn::IVideoBuf::raw_ptr psrc = (*pbuf_)[finfo_.rprops_->bufs_.indx_sbuf_];
  if (!psrc)
  {
    U3_XLOG_DBG ("FACE DETECTOR SKIP if (!psrc)")
    return;
  }

  dlib::array2d< std::uint8_t > img;

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  static std::int32_t counter   = 20;
  const std::string   file_path = "c:/imgs/dump_" + std::to_string (counter) + ".jpg";
  dlib::load_image (img, file_path);
  ++counter;
#endif

  temp_buf_->clone (psrc, 100.0F);
  utils::dbufs::video::helpers::swap_buf_data_by_rows (temp_buf_.get ());
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
    U3_XLOG_DBG ("FACE DETECTOR SKIP: faces not found")
    return;
  }

  for (std::size_t i = 0; i < faces.size (); ++i)
  {
    const auto& face = faces[i];
    U3_LOG_DATA_DEV ("Face index" + VTOLOG (i) + " from" + VTOLOG (faces.size ()) + VTOLOG (face.left ()) + VTOLOG (face.top ()) + VTOLOG (face.width ()) + VTOLOG (face.height ()));
  }

  auto [evnt, revnt]       = ::libs::iproperties::helpers::create_event< syn::AddEvent2EventsMsg > (libs::utility::utils::cuuid (), "???<<<>>>???");
  auto [fd_evnt, fd_revnt] = ::libs::iproperties::helpers::create_event< syn::FaceDetect > ();
  revnt->set_event (fd_evnt);
  info.frame_events_->emplace_back (evnt);
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
Filter::convert_buf2rgb24 (syn::IVideoBuf::craw_ptr psrc, syn::IVideoBuf::raw_ptr pdst)
{
  // utils::dbufs::video::helpers::fill<short>( psrc, []( int indxx, int indxy, std::int16_t& val ) { val = rand() % 100 + 100;  return; } );
  // utils::dbufs::video::helpers::fill<short>( psrc, []( int indxx, int indxy, std::int16_t& val ) { val = counter % 100 + 100;  return; } );

  pdst->buf_alloc (
    ::utils::dbufs::video::AllocParams (
      psrc->get_dim_vars (),
      ::libs::utility::uids::minor::id_val::y8));

  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.push_back (syn::ProxyBuf (psrc, "src dlls::detectors::detect_face"));
  cinfo.dsts_.push_back (syn::ProxyBuf (pdst, "dst dlls::detectors::detect_face"));

  ::libs::optim::mcalls::MTFuncInfo tfunc (&fx16_x8_);
  pthreads_->mthreads_call (
    id_obj_,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
Filter::save_buf2file (
  const std::string&      file_name,
  std::int32_t            counter,
  std::int32_t            quality,
  syn::IVideoBuf::raw_ptr psrc)
{
  U3_CHECK (quality >= 0 && quality <= 100, "check quality");

  const syn::ProxyBuf lsrc (temp_buf_.get (), "temp_buf dlls::detectors::detect_face");
  const std::uint8_t* cur_buf    = utils::dbufs::video::helpers::get_const_data (temp_buf_.get ());
  const std::int32_t  in_format  = TJPF_GRAY;
  const std::int32_t  out_format = TJSAMP_GRAY;
  unsigned long       jpeg_size  = 0;
  unsigned long       max_size   = tjBufSize (lsrc.width_, lsrc.height_, out_format);

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
    ::libs::utility::casts::reinterpret_cast_helper< const std::uint8_t* > (cur_buf),
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
    U3_THROW_EXCEPT ((std::string ("jpeg coder, ") + std::string (jerr ? jerr : "unknow")).c_str ());
  }

  std::ofstream file (file_name.c_str (), std::ios_base::ate | std::ios_base::binary);

  file.write (::libs::utility::casts::reinterpret_cast_helper< const char* > (jpeg_buf_), jpeg_size);
  file.flush ();
}
#endif
}   // namespace dlls::detectors::detect_face
