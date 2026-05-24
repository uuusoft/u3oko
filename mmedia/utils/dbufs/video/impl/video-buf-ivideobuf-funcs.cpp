/**
\file       video-buf-ivideobuf-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
VideoBuf::set_format_int (const libs::helpers::uids::minor::id_val& _id)
{
  params_.minor_ = _id;
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
  // EAI-BREAK-CHANGE 22.03.2026
  params_.minor_ = ::libs::helpers::uids::minor::id_val::unknown;
  // params_.minor_.reset ();
  params_.flags_.fill (false);

  params_.geom_dims_[Dims::stride] = 0;
  // dim_vars_.set (Dims::stride, 0);

  set_flag_int (BufFlags::empty, true);
}


void
VideoBuf::set_dim_var_int (const Dims& _type, dim_type _val)
{
  switch (_type)
  {
  case Dims::stride:
    U3_ASSERT (_val > 0);
    U3_ASSERT (_val * get_dim_var_int (Dims::height) <= getraw_buf ()->get_buf_size ());
    break;
  default:
    break;
  }

  // dim_vars_.set (_type, _val);
  params_.geom_dims_[_type] = _val;
}


VideoBuf::dim_type
VideoBuf::get_dim_var_int (const Dims& _type) const
{
  return params_.geom_dims_[_type];
  // return dim_vars_.get (_type);
}


const ::utils::dbufs::video::DimVars&
VideoBuf::get_dim_vars_int () const
{
  return params_.geom_dims_;
}


bool
VideoBuf::check_int (const check_func_type& _obj) const
{
  if (get_flag_int (BufFlags::empty))
  {
    return true;
  }

  for (dim_type indxy = 0; indxy < get_dim_var_int (Dims::height); ++indxy)
  {
    const std::int16_t* _bstr = helpers::get_line_const_data_as< const std::int16_t* > (this, indxy);
    for (dim_type indxx = 0; indxx < get_dim_var_int (Dims::width); ++indxx)
    {
      if (!_obj (indxx, indxy, _bstr[indxx]))
      {
        U3_ASSERT_SIGNAL_NT ("failed");
        return false;
      }
    }
  }
  return true;
}


void
VideoBuf::set_flag_int (const BufFlags& _type, bool _val)
{
  U3_ASSERT (_type < BufFlags::max_bound);

  switch (_type)
  {
  case BufFlags::empty: {
    if (_val)
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

  params_.flags_[_type] = _val;
}


bool
VideoBuf::get_flag_int (const BufFlags& _type) const
{
  U3_ASSERT (_type < BufFlags::max_bound);

  switch (_type)
  {
  case BufFlags::null: {
    if (!getraw_buf () || 0 == getraw_buf ()->get_buf_size ())
    {
      return true;
    }

    return false;
  }
  case BufFlags::empty: {
    if (get_flag_int (BufFlags::null))
    {
      return true;
    }

    if (0 == (*this)[MemVars::size_data])
    {
      return true;
    }
    // EAI-BREAK-CHANGE 22.03.2026
    if (::libs::helpers::uids::minor::id_val::unknown == params_.minor_)
    // if (params_.minor_.empty ())
    {
      return true;
    }
    return false;
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

    const dim_type _yoffset    = ::libs::optim::s16bit::conv::consts::bufs::half_max_size_core_conv * get_dim_var_int (Dims::stride);
    const dim_type _min_offset = _yoffset + ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv;

    if ((*this)[MemVars::offset_data] < _min_offset)
    {
      return false;
    }

    if ((*this)[MemVars::size_buf] < 2 * _min_offset + get_dim_var_int (Dims::stride) * get_dim_var_int (Dims::height))
    {
      return false;
    }

    return true;
  }
  default:
    break;
  }

  return params_.flags_[_type];
}


void
VideoBuf::buf_alloc_int (const AllocBufInfo& info)
{
  if (DimChecks::enable == info.check_dims_)
  {
    check_dims (info.geom_dims_[Dims::width], info.geom_dims_[Dims::height]);
  }

  // EAI-BREAK-CHANGE 22.03.2026
  params_.minor_ = info.minor_ != ::libs::helpers::uids::minor::id_val::unknown ? info.minor_ : params_.minor_;
  // params_.minor_     = info.minor_ != ::libs::helpers::utils::cuuid () ? info.minor_ : params_.minor_;
  params_.geom_dims_ = info.geom_dims_;
  params_.flags_     = info.flags_;

  set_mem_var_int (MemVars::offset_data, 0);

  dim_type _alloc_size = info.force_size_;
  dim_type offset_data = 0;
  dim_type size_data   = 0;
  dim_type _stride     = _alloc_size ? info.geom_dims_[Dims::width] : 0;   //  для явно заданного размера используем переданные параметры, в данном случае ширину.

  const bool _conv_support = (0 == _alloc_size) && (info.flags_[BufFlags::convolution_support] || info.flags_[BufFlags::convolution_data]) ? true : false;

  if (0 == _alloc_size)
  {
    const dim_type _px_byte  = ::libs::helpers::uids::helpers::get_count_bytes_from_format (params_.minor_);
    const dim_type _khresize = ::libs::helpers::uids::helpers::get_hkoeff_from_format (params_.minor_);

    if (_conv_support)
    {
      _stride     = ::libs::helpers::mem::get_align64 (U3_CAST_UINT32 (info.geom_dims_[Dims::width] * sizeof (std::int16_t) + ::libs::optim::s16bit::conv::consts::bufs::x_add_conv));
      offset_data = (::libs::optim::s16bit::conv::consts::bufs::half_max_size_core_conv + 1) * _stride + ::libs::optim::s16bit::conv::consts::bufs::x_off_edge_conv;
      _alloc_size = offset_data * 2 + info.geom_dims_[Dims::height] * _khresize * _stride;
      // dim_vars_.set (Dims::width, info.width_);
      // dim_vars_.set (Dims::height, info.height_);
    }
    else
    {
      _stride     = ::libs::helpers::mem::get_align64 (info.geom_dims_[Dims::stride] ? info.geom_dims_[Dims::stride] : _px_byte * info.geom_dims_[Dims::width]);
      offset_data = 0;
      _alloc_size = info.geom_dims_[Dims::height] * _stride * _khresize;
    }
  }

  // дополнительно всегда выделяем снизу несколько строк, чтобы гарантировать нормальную работу деления буфера на рабочие потоки
  _alloc_size += _stride * ::libs::optim::s16bit::conv::consts::bufs::max_align_block_by_y_for_algs;

  U3_CHECK (_alloc_size > 0, "received zero size for alloc");
  U3_CHECK (info.geom_dims_[Dims::stride] <= _stride, "calculated stride too small" + VTOLOG (info.geom_dims_[Dims::stride]) + VTOLOG (_stride) + VTOLOG (_conv_support));

  ialloc (_alloc_size);
  set_mem_var_int (MemVars::size_data, size_data);
  // dim_vars_[Dims::stride] = _stride;
  params_.geom_dims_[Dims::stride] = _stride;
  set_mem_var_int (MemVars::offset_data, offset_data);

  params_.flags_[BufFlags::convolution_support] = _conv_support;
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

  if (!src->get_flag (BufFlags::empty) && (percent > 0.0f) && src->get_flag (BufFlags::convolution_data))
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
