/**
\file       video-buf-ivideobuf-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_dbufs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../dbufs-includes_int.hpp"
#include "video-buf.hpp"

namespace utils::dbufs::video::impl
{
void
check_dims (const VideoBuf::dim_type width, const VideoBuf::dim_type height)
{
  U3_CHECK (width >= consts::min_width, "width less consts::min_width" + VTOLOG (width) + VTOLOG (consts::min_width));
  U3_CHECK (width <= consts::max_width, "width large consts::max_width" + VTOLOG (width) + VTOLOG (consts::max_width));
  U3_CHECK (height >= consts::min_height, "height less consts::min_height" + VTOLOG (height) + VTOLOG (consts::min_height));
  U3_CHECK (height <= consts::max_height, "height large consts::max_height" + VTOLOG (height) + VTOLOG (consts::max_height));
}


void
VideoBuf::set_format_int (const libs::helpers::uids::minor::id_val& fid)
{
  params_.minor_ = fid;
}


libs::helpers::uids::minor::id_val
VideoBuf::get_format_int () const
{
  return params_.minor_;
}


void
VideoBuf::flush_int ()
{
  IMemBuf::flush ();

  params_.reset ();
  params_.minor_ = ::libs::helpers::uids::minor::id_val::unknown;
  params_.flags_.fill (false);
  params_.geom_dims_[Dims::stride] = 0;
  set_flag_int (BufFlags::empty, true);
}


void
VideoBuf::set_dim_var_int (const Dims& dtype, dim_type dval)
{
  switch (dtype)
  {
  case Dims::stride:
    U3_ASSERT (dval > 0);
    U3_ASSERT (dval * get_dim_var_int (Dims::height) <= getraw_buf ()->get_buf_size ());
    break;
  default:
    break;
  }
  params_.geom_dims_[dtype] = dval;
}


VideoBuf::dim_type
VideoBuf::get_dim_var_int (const Dims& dtype) const
{
  return params_.geom_dims_[dtype];
}


const ::utils::dbufs::video::DimVars&
VideoBuf::get_dim_vars_int () const
{
  return params_.geom_dims_;
}


bool
VideoBuf::check_int (const check_func_type& obj) const
{
  if (get_flag_int (BufFlags::empty))
  {
    return true;
  }

  for (dim_type indxy = 0; indxy < get_dim_var_int (Dims::height); ++indxy)
  {
    const std::int16_t* bstr = helpers::get_line_const_data_as< const std::int16_t* > (this, indxy);
    for (dim_type indxx = 0; indxx < get_dim_var_int (Dims::width); ++indxx)
    {
      if (!obj (indxx, indxy, bstr[indxx]))
      {
        U3_ASSERT_SIGNAL_NT ("failed");
        return false;
      }
    }
  }
  return true;
}


void
VideoBuf::set_flag_int (const BufFlags& ftype, bool fval)
{
  U3_ASSERT (ftype < BufFlags::max_bound);

  switch (ftype)
  {
  case BufFlags::empty: {
    if (fval)
    {
      set_mem_var_int (MemVars::size_data, 0);
    }
    break;
  }
  case BufFlags::null:
  case BufFlags::convolution_support:
  case BufFlags::convolution_data:
    return;   // auto flags
  default:
    break;
  }

  params_.flags_[ftype] = fval;
}


bool
VideoBuf::get_flag_int (const BufFlags& ftype) const
{
  U3_ASSERT (ftype < BufFlags::max_bound);
  switch (ftype)
  {
  case BufFlags::null: {
    return !getraw_buf () || 0 == getraw_buf ()->get_buf_size () ? true : false;
  }
  case BufFlags::empty: {
    return get_flag_int (BufFlags::null) || 0 == (*this)[MemVars::size_data] || ::libs::helpers::uids::minor::id_val::unknown == params_.minor_ ? true : false;
  }
  case BufFlags::convolution_data: {
    if (get_flag_int (BufFlags::empty))
    {
      return false;
    }
    if ((*this)[MemVars::size_data] < ::libs::optim::s16bit::conv::consts::bufs::max_size_core_conv * get_dim_var_int (Dims::stride))
    {
      return false;
    }

    const dim_type yoffset    = ::libs::optim::s16bit::conv::consts::bufs::half_max_size_core_conv * get_dim_var_int (Dims::stride);
    const dim_type min_offset = yoffset + ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv;

    if ((*this)[MemVars::offset_data] < min_offset)
    {
      return false;
    }
    if ((*this)[MemVars::size_buf] < 2 * min_offset + get_dim_var_int (Dims::stride) * get_dim_var_int (Dims::height))
    {
      return false;
    }
    return true;
  }
  default:
    break;
  }
  return params_.flags_[ftype];
}


void
VideoBuf::buf_alloc_int (const AllocBufInfo& info)
{
  if (DimChecks::enable == info.check_dims_)
  {
    check_dims (info.geom_dims_[Dims::width], info.geom_dims_[Dims::height]);
  }

  params_.minor_     = info.minor_ != ::libs::helpers::uids::minor::id_val::unknown ? info.minor_ : params_.minor_;
  params_.geom_dims_ = info.geom_dims_;
  params_.flags_     = info.flags_;

  set_mem_var_int (MemVars::offset_data, 0);

  dim_type alloc_size  = info.force_size_;
  dim_type offset_data = 0;
  dim_type size_data   = 0;
  dim_type stride      = alloc_size ? info.geom_dims_[Dims::width] : 0;   //  для явно заданного размера используем переданные параметры, в данном случае ширину.

  const bool conv_support = (0 == alloc_size) && (info.flags_[BufFlags::convolution_support] || info.flags_[BufFlags::convolution_data]) ? true : false;

  if (0 == alloc_size)
  {
    const dim_type px_byte  = ::libs::helpers::uids::helpers::get_count_bytes_from_format (params_.minor_);
    const dim_type khresize = ::libs::helpers::uids::helpers::get_hkoeff_from_format (params_.minor_);

    if (conv_support)
    {
      stride      = ::libs::helpers::mem::align_value (U3_CAST_UINT32 (info.geom_dims_[Dims::width] * sizeof (std::int16_t) + ::libs::optim::s16bit::conv::consts::bufs::x_add_conv), 64U, true);
      offset_data = (::libs::optim::s16bit::conv::consts::bufs::half_max_size_core_conv + 1) * stride + ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv;
      alloc_size  = offset_data * 2 + info.geom_dims_[Dims::height] * khresize * stride;
    }
    else
    {
      stride      = ::libs::helpers::mem::align_value (info.geom_dims_[Dims::stride] ? info.geom_dims_[Dims::stride] : px_byte * info.geom_dims_[Dims::width], 64U, true);
      offset_data = 0;
      alloc_size  = info.geom_dims_[Dims::height] * stride * khresize;
    }
  }

  // дополнительно всегда выделяем снизу несколько строк, чтобы гарантировать нормальную работу деления буфера на рабочие потоки
  alloc_size += stride * ::libs::optim::s16bit::conv::consts::bufs::max_align_block_by_y_for_algs;

  U3_CHECK (alloc_size > 0, "received invalid size for alloc" + VTOLOG (alloc_size));
  U3_CHECK (info.geom_dims_[Dims::stride] <= stride, "calculated stride too small" + VTOLOG (info.geom_dims_[Dims::stride]) + VTOLOG (stride) + VTOLOG (conv_support));

  ialloc (alloc_size);
  set_mem_var_int (MemVars::size_data, size_data);
  // dim_vars_[Dims::stride] = stride;
  params_.geom_dims_[Dims::stride] = stride;
  set_mem_var_int (MemVars::offset_data, offset_data);

  params_.flags_[BufFlags::convolution_support] = conv_support;
  params_.flags_[BufFlags::empty]               = true;
}


void
VideoBuf::clone_int (IBuf::craw_ptr isrc, float percent)
{
  auto src = dynamic_cast< VideoBuf::craw_ptr > (isrc);
  U3_ASSERT (src);
  if (this == src)
  {
    U3_XLOG_WARN ("try clone itself" + PTR_TOLOG (this));
    return;
  }

  IMemBuf::clone_int (isrc, percent);

  // params_.minor_ = src->params_.minor_;
  params_ = src->params_;

  if (!src->get_flag (BufFlags::empty) && (percent > 0.0F) && src->get_flag (BufFlags::convolution_data))
  {
    ::libs::helpers::mem::u3copy (src->get_cbuf (), get_buf (), (*src)[MemVars::size_buf]);
  }
}


void
VideoBuf::swap_int (IBuf& isrc)
{
  VideoBuf& src = dynamic_cast< VideoBuf& > (isrc);
  if (this == &src)
  {
    U3_XLOG_WARN ("try swap itself" + PTR_TOLOG (this));
    return;
  }

  IMemBuf::swap_int (isrc);
  params_.swap (src.params_);
}
}   // namespace utils::dbufs::video::impl
