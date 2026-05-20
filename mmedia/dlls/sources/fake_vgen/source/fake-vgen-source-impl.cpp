/**
\file       fake-vgen-source-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
\project    u3_fake_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "fake-vgen-source-impl.hpp"
#include "fake-vgen-color-helpers-funcs.hpp"

namespace dlls::sources::fake_vgen
{
SourceImpl::SourceImpl () :
  indx_bcomp_ (0),
  counter_frames_ (0)
{
  fill_rand_vals ();
  init_gen_funcs ();
}


SourceImpl::~SourceImpl ()
{
  U3_CHECK_NT (free_int (), "SourceImpl::~SourceImpl");
}


void
SourceImpl::init_int ()
{
}


void
SourceImpl::start_int ()
{
  U3_LOG_DATA_DBG ("dlls::sources::fake_vgen::SourceImpl::start_int");
  counter_frames_ = 0;
}


void
SourceImpl::stop_int ()
{
  U3_LOG_DATA_DBG ("dlls::sources::fake_vgen::SourceImpl::stop_int");
}


void
SourceImpl::get_sources_int (std::vector< syn::DataSourceInfo >& sources)
{
  sources.push_back (syn::DataSourceInfo ());

  auto& el = sources.back ();

  el.max_count_ = 0;
  el.number_    = 1;
  el.name_      = "fake-camera";
  el.type_      = libs::imdata_events::events::DataSources::video;
}


void
SourceImpl::get_raw_data_int (syn::pkeys2bufs_type& bufs, syn::tevents_type* events)
{
  auto& buf = (*bufs)[::utils::dbufs::video::consts::offs::raw];
  U3_ASSERT (buf);

  buf->set_flag (::utils::dbufs::BufFlags::empty, true);

  boost::posix_time::ptime now_time  = boost::posix_time::microsec_clock::universal_time ();
  const auto&              props     = srcimpinfo_.capture_props_;
  const auto               px_format = ::libs::helpers::uids::minor::id_val::device_specific == props->capi_.px_format_ ? ::libs::helpers::uids::minor::id_val::yuy2 : props->capi_.px_format_;
  U3_LOG_DATA_DBG ("dlls::sources::fake_vgen::SourceImpl::get_raw_data_int px_format=" + ::libs::helpers::uids::helpers::get_readable_name (px_format));

  buf->buf_alloc (
    ::utils::dbufs::video::AllocBufInfo (
      props->capi_.width_, props->capi_.height_, 0, px_format));

  auto it_make_buf_funct = gen_funcs_.find (px_format);
  U3_CHECK (it_make_buf_funct != gen_funcs_.end (), "empty make buf funct");
  buf->set_format (px_format);

  auto& make_buf_funct = it_make_buf_funct->second;

  make_buf_funct (
    buf->get_dim_var (::utils::dbufs::video::Dims::width),
    buf->get_dim_var (::utils::dbufs::video::Dims::height),
    buf->get_dim_var (::utils::dbufs::video::Dims::stride),
    utils::dbufs::video::helpers::get_data (buf.get ()));

  buf->set_mem_var (
    ::utils::dbufs::MemVars::size_data,
    buf->get_dim_var (::utils::dbufs::video::Dims::stride) * props->capi_.height_);

  ++indx_bcomp_;
  ++counter_frames_;
  time_last_frame_ = now_time;
}


void
SourceImpl::set_cpu_int (::libs::helpers::sys::cpu::CpuExts current_optim)
{
}


bool
SourceImpl::free_int ()
{
  U3_LOG_DATA_DBG ("dlls::sources::fake_vgen::SourceImpl::free_int");
  stop ();
  return true;
}


void
SourceImpl::update_source_info_int (const syn::SourceImplInfo& info)
{
  U3_LOG_DATA_DBG ("dlls::sources::fake_vgen::SourceImpl::update_source_info_int");
  const auto& px_format = srcimpinfo_.capture_props_->capi_.px_format_;
  if (!gen_funcs_[px_format])
  {
    U3_LOG_DATA_WRN ("try use unsupported format fake came " + ::libs::helpers::uids::helpers::get_readable_name (px_format));
    // px_format = ::libs::helpers::uids::minor::id_val::rgb24;
  }
}


void
SourceImpl::fill_rand_vals ()
{
  std::random_device               seed;
  std::default_random_engine       eng (seed ());
  std::uniform_real_distribution<> dist (0, 1);

  rand_bcomp_.fill (0);
  for (std::uint8_t& val : rand_bcomp_)
  {
    val = U3_CAST_UINT8 (128 + dist (eng) * 127);
  }
}


void
SourceImpl::init_gen_funcs ()
{
  U3_LOG_DATA_DBG ("dlls::sources::fake_vgen::SourceImpl::init_gen_funcs");
  constexpr uint32_t col_width = 30;

  auto col2r = [this] (std::uint32_t colpos) -> std::uint8_t { 
    const std::uint8_t bcomp = rand_bcomp_[indx_bcomp_ % rand_bcomp_.size ()];    
    return colpos <= 9 ? bcomp : 0; };

  auto col2g = [this] (std::uint32_t colpos) -> std::uint8_t { 
    const std::uint8_t bcomp = rand_bcomp_[indx_bcomp_ % rand_bcomp_.size ()];
    return colpos >= 10 && colpos <= 19 ? bcomp : 0; };

  auto col2b = [this] (std::uint32_t colpos) -> std::uint8_t { 
    const std::uint8_t bcomp = rand_bcomp_[indx_bcomp_ % rand_bcomp_.size ()];
    return colpos >= 20 && colpos <= 29 ? bcomp : 0; };

  //  yuy2
  gen_funcs_[::libs::helpers::uids::minor::id_val::yuy2] =
    [col2r, col2g, col2b] (std::uint32_t width, std::uint32_t height, std::uint32_t stride, std::uint8_t* beg_buf) {
      for (std::uint32_t iy = 0; iy < height; ++iy)
      {
        std::uint8_t* prow = beg_buf + iy * stride;
        for (std::uint32_t ix = 0; ix < width; ix += 2)
        {
          const std::uint32_t colpos = ix % col_width;
          const auto          r      = col2r (colpos);
          const auto          g      = col2g (colpos);
          const auto          b      = col2b (colpos);

          prow[2 * ix + 0] = ::libs::optim::convert::gen::rgb2y (r, g, b);   // y
          prow[2 * ix + 1] = ::libs::optim::convert::gen::rgb2u (r, g, b);   // u
          prow[2 * ix + 2] = ::libs::optim::convert::gen::rgb2y (r, g, b);   // y
          prow[2 * ix + 3] = ::libs::optim::convert::gen::rgb2v (r, g, b);   // v
        }
      }
    };

  // yuyv
  gen_funcs_[::libs::helpers::uids::minor::id_val::yuyv] = gen_funcs_[::libs::helpers::uids::minor::id_val::yuy2];

  //  uyvy
  gen_funcs_[::libs::helpers::uids::minor::id_val::uyvy] =
    [col2r, col2g, col2b] (std::uint32_t width, std::uint32_t height, std::uint32_t stride, std::uint8_t* beg_buf) {
      for (std::uint32_t iy = 0; iy < height; ++iy)
      {
        std::uint8_t* prow = beg_buf + iy * stride;
        for (std::uint32_t ix = 0; ix < width; ix += 2)
        {
          const std::uint32_t colpos = ix % col_width;
          const auto          r      = col2r (colpos);
          const auto          g      = col2g (colpos);
          const auto          b      = col2b (colpos);

          prow[2 * ix + 0] = ::libs::optim::convert::gen::rgb2u (r, g, b);   // u
          prow[2 * ix + 1] = ::libs::optim::convert::gen::rgb2y (r, g, b);   // y
          prow[2 * ix + 2] = ::libs::optim::convert::gen::rgb2v (r, g, b);   // v
          prow[2 * ix + 3] = ::libs::optim::convert::gen::rgb2y (r, g, b);   // y
        }
      }
    };

  // rgb24
  gen_funcs_[::libs::helpers::uids::minor::id_val::rgb24] =
    [col2r, col2g, col2b] (std::uint32_t width, std::uint32_t height, std::uint32_t stride, std::uint8_t* beg_buf) {
      for (std::uint32_t iy = 0; iy < height; ++iy)
      {
        std::uint8_t* prow = beg_buf + iy * stride;
        for (std::uint32_t ix = 0; ix < width; ++ix)
        {
          const std::uint32_t colpos = ix % col_width;

          prow[3 * ix + 0] = col2r (colpos);
          prow[3 * ix + 1] = col2g (colpos);
          prow[3 * ix + 2] = col2b (colpos);
        }
      }
    };

  // rgb32
  gen_funcs_[::libs::helpers::uids::minor::id_val::rgb32] =
    [col2r, col2g, col2b] (std::uint32_t width, std::uint32_t height, std::uint32_t stride, std::uint8_t* beg_buf) {
      for (std::uint32_t iy = 0; iy < height; ++iy)
      {
        std::uint8_t* prow = beg_buf + iy * stride;
        for (std::uint32_t ix = 0; ix < width; ++ix)
        {
          const std::uint32_t colpos = ix % col_width;

          prow[4 * ix + 0] = col2r (colpos);
          prow[4 * ix + 1] = col2g (colpos);
          prow[4 * ix + 2] = col2b (colpos);
          prow[4 * ix + 3] = 0;
        }
      }
    };

  // i420
  gen_funcs_[::libs::helpers::uids::minor::id_val::i420] =
    [col2r, col2g, col2b] (std::uint32_t width, std::uint32_t height, std::uint32_t stride, std::uint8_t* beg_buf) {
      std::uint8_t* beg_ubuf = beg_buf + stride * height;
      std::uint8_t* beg_vbuf = beg_buf + stride * height + stride * (height >> 1);

      for (std::uint32_t iy = 0; iy < height; ++iy)
      {
        std::uint8_t* prow  = beg_buf + iy * stride;
        std::uint8_t* purow = beg_ubuf + (iy >> 1) * stride;
        std::uint8_t* pvrow = beg_vbuf + (iy >> 1) * stride;
        for (std::uint32_t ix = 0; ix < width; ix += 2)
        {
          const std::uint32_t colpos = ix % col_width;
          const auto          r      = col2r (colpos);
          const auto          g      = col2g (colpos);
          const auto          b      = col2b (colpos);

          prow[ix + 0] = ::libs::optim::convert::gen::rgb2y (r, g, b);
          prow[ix + 1] = ::libs::optim::convert::gen::rgb2y (r, g, b);

          purow[ix >> 1] = ::libs::optim::convert::gen::rgb2u (r, g, b);
          pvrow[ix >> 1] = ::libs::optim::convert::gen::rgb2v (r, g, b);
        }
      }
    };
}
}   // namespace dlls::sources::fake_vgen
