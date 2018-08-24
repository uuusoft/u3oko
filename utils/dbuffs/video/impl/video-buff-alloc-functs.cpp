//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-buff-alloc-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Реализация части функционала буфера с видео данными.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "video-buff.hpp"

namespace utils { namespace dbuffs { namespace video { namespace impl {

void
check_dims (const VideoBuff::dim_type _width, const VideoBuff::dim_type _height)
{
  CHECK_STATE (_width >= consts::min_width, "failed, _width less consts::min_width, " << _width);
  CHECK_STATE (_width <= consts::max_width, "failed, _width large consts::max_width" << _width);
  CHECK_STATE (_height >= consts::min_height, "failed, _height less consts::min_height" << _height);
  CHECK_STATE (_height <= consts::max_height, "failed, _height large consts::max_height" << _height);
  return;
}


void
VideoBuff::balloc_int (const AllocBuffInfo& _info)
{
  XULOG_TRACE ("VideoBuff::balloc_int: beg");
  if (TypeCheckDim::enable_check == _info.check_dims_)
    {
      check_dims (_info.width_, _info.height_);
    }

  va_info_.minor_ = _info.minor_ != ::libs::helpers::utils::cuuid () ? _info.minor_ : va_info_.minor_;

  dim_vars_.set (TypeDimVar::width, _info.width_);
  dim_vars_.set (TypeDimVar::height, _info.height_);
  set_mem_var_int (TypeMemVar::offset_data, 0);
  flags_.set (TypeFlagsBuff::empty, true);

  dim_type _alloc_size   = _info.force_size_;
  dim_type _offset_data  = 0;
  dim_type _size_data    = 0;
  dim_type _stride       = _alloc_size ? _info.width_ : 0;      //  для явно заданного размера используем переданные параметры, в данном случае ширину.
  bool     _conv_support = (0 == _alloc_size) && ((TypeFlagsBuff::convolution_support == _info.flag_) || (TypeFlagsBuff::convolution_data == _info.flag_)) ? true : false;

  if (0 == _alloc_size)
    {
      const dim_type _px_byte  = ::libs::helpers::uids::helpers::get_count_bytes_from_format (va_info_.minor_);
      const dim_type _khresize = ::libs::helpers::uids::helpers::get_hkoeff_from_format (va_info_.minor_);

      if (_conv_support)
        {
          _stride      = smem::get_align64 (_info.width_ * sizeof (short) + cs16buffs::x_add_conv);
          _offset_data = (cs16buffs::half_max_size_core_conv + 1) * _stride + cs16buffs::x_off_edge_conv;
          _alloc_size  = _offset_data * 2 + _info.height_ * _khresize * _stride;
          //dim_vars_.set (TypeDimVar::width, _info.width_);
          //dim_vars_.set (TypeDimVar::height, _info.height_);
        }
      else
        {
          _stride      = smem::get_align64 (_info.stride_ ? _info.stride_ : _px_byte * _info.width_);
          _offset_data = 0;
          _alloc_size  = _info.height_ * _stride * _khresize;
        }
    }

  CHECK_STATE (_alloc_size > 0, "failed, received zero size for alloc");
  ialloc (_alloc_size);
  set_mem_var_int (TypeMemVar::size_data, _size_data);
  dim_vars_.set (TypeDimVar::stride, _stride);
  set_mem_var_int (TypeMemVar::offset_data, _offset_data);
  flags_.set (TypeFlagsBuff::convolution_support, _conv_support);
  XULOG_TRACE ("VideoBuff::balloc_int: end");
  return;
}


void
VideoBuff::clone_int (IBuff::craw_ptr _isrc, float _percent)
{
  auto _src = dynamic_cast<VideoBuff::craw_ptr> (_isrc);
  UASSERT (_src);
  if (this == _src)
    {
      XULOG_WARNING ("try clone itself, 0x" << std::hex << this);
      return;
    }

  IMemBuff::clone_int (_isrc, _percent);

  va_info_.minor_ = _src->va_info_.minor_;

  dim_vars_.set (TypeDimVar::width, _src->get_dim_var (TypeDimVar::width));
  dim_vars_.set (TypeDimVar::height, _src->get_dim_var (TypeDimVar::height));
  dim_vars_.set (TypeDimVar::stride, _src->get_dim_var (TypeDimVar::stride));

  flags_.set (TypeFlagsBuff::fake, _src->get_flag (TypeFlagsBuff::fake));
  flags_.set (TypeFlagsBuff::null, _src->get_flag (TypeFlagsBuff::null));
  flags_.set (TypeFlagsBuff::empty, _src->get_flag (TypeFlagsBuff::empty));
  flags_.set (TypeFlagsBuff::convolution_support, _src->get_flag (TypeFlagsBuff::convolution_support));
  flags_.set (TypeFlagsBuff::convolution_data, _src->get_flag (TypeFlagsBuff::convolution_data));

  if (!_src->get_flag (TypeFlagsBuff::empty) && (_percent > 0.0f) && _src->get_flag (TypeFlagsBuff::convolution_data))
    {
      smem::acopy (_src->get_cbuff (), get_buff (), (*_src)[TypeMemVar::size_buffer]);
    }
  return;
}


void
VideoBuff::swap_int (IBuff& _isrc)
{
  VideoBuff& _src = dynamic_cast<VideoBuff&> (_isrc);
  if (this == &_src)
    {
      XULOG_WARNING ("try swap itself, 0x" << std::hex << this);
      return;
    }

  IMemBuff::swap_int (_isrc);

  va_info_.swap (_src.va_info_);
  //std::swap( va_info_, _src.va_info_ );
  //std::swap( va_info_.minor_, _src.va_info_.minor_ );

  std::swap (flags_, _src.flags_);
  std::swap (dim_vars_, _src.dim_vars_);
  return;
}

}}}}      // namespace utils::dbuffs::video::impl
