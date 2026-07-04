/**
\file       all2hsl-dll-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_all2hsl
*/
#include "all2hsl-dll-includes_int.hpp"
#include "all2hsl-dll-info-filter-dll.hpp"
#include "all2hsl-dll-filter-dll.hpp"

namespace dlls::convertors::all2hsl
{
void
Filter::init_pts (syn::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}


void
Filter::alloc_fake_frame (syn::TransformInfo& info)
{
  (*info.ibuf_)->reset (false);

  const std::int16_t bits_per_pixel = 24;
  const std::int32_t req_width      = 640;
  const std::int32_t req_height     = 480;
  const std::int32_t req_stride     = ::libs::utility::mem::align_value (req_width * bits_per_pixel / 8, 64, true);
  const std::int32_t req_size       = req_stride * req_height;
  auto               base_buf       = (**info.ibuf_)[(*info.ibuf_)->get_base_index ()];

  //  for all other format create null frame RGB24 320x240
  base_buf->set_dim_var (::utils::dbufs::video::Dims::width, req_width);
  base_buf->set_dim_var (::utils::dbufs::video::Dims::height, req_height);

  syn::IVideoBuf::raw_ptr raw_buf = (**info.ibuf_)[syn::offs::raw];

  raw_buf->buf_alloc (
    ::utils::dbufs::video::AllocParams (
      req_width,
      req_height,
      req_stride,
      ::libs::utility::uids::minor::id_val::rgb24));

  ::utils::dbufs::video::helpers::replace_buf_params (*raw_buf, 0, req_size);
}


void
Filter::alloc_bufs ()
{
  syn::IVideoBuf::raw_ptr braw     = (*pbuf_)[syn::offs::raw];
  auto                    base_buf = (*pbuf_)[pbuf_->get_base_index ()];
  const auto              width    = base_buf->get_dim_var (::utils::dbufs::video::Dims::width);
  const auto              height   = base_buf->get_dim_var (::utils::dbufs::video::Dims::height);

  finfo_.strip_color_ = finfo_.rprops_->strip_color_ || (::libs::utility::uids::minor::id_val::rgb24 != braw->get_format ());

  syn::IVideoBuf::raw_ptr hsl[3] = {
    finfo_.strip_color_ ? nullptr : (*pbuf_)[syn::offs::hue],
    finfo_.strip_color_ ? nullptr : (*pbuf_)[syn::offs::sat],
    (*pbuf_)[syn::offs::lit]
  };

  for (syn::IVideoBuf::raw_ptr cbuf : hsl)
  {
    if (!cbuf)
    {
      continue;
    }

    auto alloc_info = ::utils::dbufs::video::AllocParams (
      width,
      height,
      0,
      ::libs::utility::uids::minor::id_val::y16,
      utils::dbufs::video::DimChecks::enable);

    alloc_info.flags_[::utils::dbufs::BufFlags::convolution_support] = true;
    cbuf->buf_alloc (alloc_info);
  }
}


void
Filter::alloc_temp_bufs ()
{
  //  Резервируем память под второстепенные буфера, связанные с основным.
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  const syn::IVideoBuf::raw_ptr l16_buf     = (*pbuf_)[syn::offs::lit];
  const syn::offs::off_buf_type indx_bufs[] = { syn::offs::temp1, syn::offs::temp2 };

  for (const syn::offs::off_buf_type& indx_buf : indx_bufs)
  {
    syn::IVideoBuf::raw_ptr tbuf = (*pbuf_)[indx_buf];
    tbuf->clone (l16_buf, 0.0F);
  }
#endif
}


void
Filter::convert_bufs_from_rgb ()
{
  syn::IVideoBuf::raw_ptr hsl[3] = {
    finfo_.strip_color_ ? nullptr : (*pbuf_)[syn::offs::hue],
    finfo_.strip_color_ ? nullptr : (*pbuf_)[syn::offs::sat],
    (*pbuf_)[syn::offs::lit]
  };

  syn::IVideoBuf::raw_ptr           rcbuf = (*pbuf_)[syn::offs::raw];
  ::libs::optim::io::MCallInfo      cinfo;
  ::libs::optim::mcalls::MTFuncInfo tfunc;

  cinfo.srcs_.emplace_back (rcbuf, "rcbuf convertors::all2hsl");

  if (finfo_.strip_color_)
  {
    cinfo.dsts_.emplace_back (hsl[2], "hsl 2 convertors::all2hsl");

    tfunc.pfunc_           = syn::Accuracys::best == finfo_.rprops_->atype_ ? &rgb24_to_l_accurate_ : &rgb24_to_l_fast_;
    tfunc.src_align_.px_x_ = 1;
    tfunc.dst_align_.px_x_ = 1;
    tfunc.src_align_.px_y_ = 1;
    tfunc.dst_align_.px_y_ = 1;
  }
  else
  {
    cinfo.dsts_.emplace_back (hsl[0], "hsl 0 convertors::all2hsl");
    cinfo.dsts_.emplace_back (hsl[1], "hsl 1 convertors::all2hsl");
    cinfo.dsts_.emplace_back (hsl[2], "hsl 2 convertors::all2hsl");

    tfunc.pfunc_           = &rgb24_to_hsl_;
    tfunc.src_align_.px_x_ = 1;
    tfunc.dst_align_.px_x_ = 1;
    tfunc.src_align_.px_y_ = 1;
    tfunc.dst_align_.px_y_ = 1;
  }

  if (!finfo_.rprops_->debug_skip_transform_)
  {
    pthreads_->mthreads_call (id_obj_, tfunc, cinfo, transinfo_->exptimes_);
  }

  for (syn::IVideoBuf::raw_ptr cbuf : hsl)
  {
    if (!cbuf)
    {
      continue;
    }

    cbuf->set_mem_var (
      syn::MemVars::size_data,
      static_cast< const syn::mem_var_type > (cbuf->get_dim_var (syn::Dims::height) * cbuf->get_dim_var (syn::Dims::stride)));

    // cbuf->fill( rand() % 255 );//debug
  }
}


void
Filter::convert_bufs_from_y8 ()
{
  syn::IVideoBuf::raw_ptr l     = (*pbuf_)[syn::offs::lit];
  syn::IVideoBuf::raw_ptr rcbuf = (*pbuf_)[syn::offs::raw];

  {
    ::libs::optim::io::MCallInfo cinfo;

    cinfo.srcs_.emplace_back (rcbuf, "rcbuf convertors::all2hsl");
    cinfo.dsts_.emplace_back (l, "l convertors::all2hsl");

    ::libs::optim::mcalls::MTFuncInfo tfunc (&fx8_to_x16_);

    pthreads_->mthreads_call (
      id_obj_,
      tfunc,
      cinfo,
      transinfo_->exptimes_);
  }

  l->set_mem_var (
    syn::MemVars::size_data,
    static_cast< const syn::mem_var_type > (l->get_dim_var (syn::Dims::height) * l->get_dim_var (syn::Dims::stride)));

  // utils::dbufs::video::helpers::fill( l, rand() % 256 );//debug
}


void
Filter::convert_bufs_from_y16 ()
{
  syn::IVideoBuf::raw_ptr l     = (*pbuf_)[syn::offs::lit];
  syn::IVideoBuf::raw_ptr rcbuf = (*pbuf_)[syn::offs::raw];

  l->clone (rcbuf, 100.0F);
  l->set_mem_var (
    syn::MemVars::size_data,
    static_cast< const syn::mem_var_type > (l->get_dim_var (syn::Dims::height) * l->get_dim_var (syn::Dims::stride)));

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // debug
  l->fill (rand () % 255);
#endif
}


void
Filter::duplicate_bufs ()
{
  if (!finfo_.rprops_->duplicate_image_)
  {
    return;
  }

  const syn::IVideoBuf::raw_ptr l16_buf      = (*pbuf_)[syn::offs::lit];
  syn::IVideoBuf::raw_ptr       copy_l16_buf = (*pbuf_)[consts::dupl_l];

  copy_l16_buf->clone (l16_buf, 100.0F);

  if (finfo_.strip_color_)
  {
    return;
  }

  const syn::IVideoBuf::raw_ptr h16_buf      = (*pbuf_)[syn::offs::hue];
  const syn::IVideoBuf::raw_ptr s16_buf      = (*pbuf_)[syn::offs::sat];
  syn::IVideoBuf::raw_ptr       copy_h16_buf = (*pbuf_)[consts::dupl_h];
  syn::IVideoBuf::raw_ptr       copy_s16_buf = (*pbuf_)[consts::dupl_s];

  copy_h16_buf->clone (h16_buf, 100.0F);
  copy_s16_buf->clone (s16_buf, 100.0F);
}


void
Filter::flip_y_bufs ()
{
  if (!finfo_.rprops_->flip_y_)
  {
    return;
  }

  syn::IVideoBuf::raw_ptr hsl[3] = {
    finfo_.strip_color_ ? nullptr : (*pbuf_)[syn::offs::hue],
    finfo_.strip_color_ ? nullptr : (*pbuf_)[syn::offs::sat],
    (*pbuf_)[syn::offs::lit]
  };

  for (syn::IVideoBuf::raw_ptr cbuf : hsl)
  {
    if (!cbuf)
    {
      continue;
    }

    //  sync y
    ::libs::optim::io::MCallInfo      cinfo;
    ::libs::optim::mcalls::MTFuncInfo tfunc (&flip_y_);

    cinfo.dsts_.emplace_back (cbuf, "dst Filter::flip_y_bufs");

    pthreads_->mthreads_call (
      id_obj_,
      tfunc,
      cinfo,
      transinfo_->exptimes_,
      1);
  }
}


void
Filter::itransform ()
{
  alloc_bufs ();

  auto       rcbuf  = (*pbuf_)[syn::offs::raw];
  const auto format = rcbuf->get_format ();

  if (rcbuf->get_flag (::utils::dbufs::BufFlags::empty))
  {
    return;
  }

  switch (format)
  {
  case ::libs::utility::uids::minor::id_val::rgb24:
    convert_bufs_from_rgb ();
    break;
  case ::libs::utility::uids::minor::id_val::y8:
    convert_bufs_from_y8 ();
    break;
  case ::libs::utility::uids::minor::id_val::y16:
    convert_bufs_from_y16 ();
    break;
  default:
    U3_LOG_DATA_ERROR ("unknown raw format - skip convert: " + ::libs::utility::uids::helpers::get_readable_name (format));
    return;
  }

  flip_y_bufs ();
  duplicate_bufs ();
  alloc_temp_bufs ();

  if (finfo_.strip_color_)
  {
    (*pbuf_)[syn::offs::hue]->flush ();
    (*pbuf_)[syn::offs::sat]->flush ();
  }
  else
  {
    ::utils::dbufs::video::helpers::fill_edges ((*pbuf_)[syn::offs::hue]);
    ::utils::dbufs::video::helpers::fill_edges ((*pbuf_)[syn::offs::sat]);
  }

  ::utils::dbufs::video::helpers::fill_edges ((*pbuf_)[syn::offs::lit]);
}
}   // namespace dlls::convertors::all2hsl
