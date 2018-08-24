//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file         video-buff.cpp
\author       Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date         26.07.2016
\copyright    www.uuusoft.com
\project      uuu_dbuffs
\brief        Реализация буфера под видео.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "video-buff.hpp"

namespace utils { namespace dbuffs { namespace video { namespace impl {

VideoBuff::VideoBuff ()
{
  flush ();
}


VideoBuff::~VideoBuff ()
{}


void
VideoBuff::set_format_int (const ::libs::helpers::utils::cuuid& _id)
{
  va_info_.minor_ = _id;
  return;
}


const ::libs::helpers::utils::cuuid&
VideoBuff::get_format_int () const
{
  return va_info_.minor_;
}


void
VideoBuff::flush_int ()
{
  IMemBuff::flush ();

  va_info_.reset ();
  va_info_.minor_.reset ();
  flags_.fill (false);

  dim_vars_.set (TypeDimVar::stride, 0);

  set_flag (TypeFlagsBuff::empty, true);
  return;
}


void
VideoBuff::set_dim_var_int (const TypeDimVar& _type, dim_type _val)
{
  switch (_type)
    {
    case TypeDimVar::stride:
      UASSERT (_val > 0);
      UASSERT (_val * get_dim_var (TypeDimVar::height) <= get_raw_buff ()->get_buff_size ());
      break;
    default:
      break;
    }

  dim_vars_.set (_type, _val);
  return;
}


VideoBuff::dim_type
VideoBuff::get_dim_var_int (const TypeDimVar& _type) const
{
  return dim_vars_.get (_type);
}


bool
VideoBuff::check_int (const check_funct_type& _obj) const
{
  if (get_flag (TypeFlagsBuff::empty))
    {
      return true;
    }

  for (dim_type _indxy = 0; _indxy < get_dim_var (TypeDimVar::height); ++_indxy)
    {
      const short* _bstr = helpers::get_line_const_data_as<const short*> (this, _indxy);
      for (dim_type _indxx = 0; _indxx < get_dim_var (TypeDimVar::width); ++_indxx)
        {
          if (!_obj (_indxx, _indxy, _bstr[_indxx]))
            {
              UASSERT_SIGNAL ("failed");
              return false;
            }
        }
    }
  return true;
}


void
VideoBuff::set_flag_int (const TypeFlagsBuff& _type, bool _val)
{
  UASSERT (_type < TypeFlagsBuff::max_bound);

  switch (_type)
    {
    case TypeFlagsBuff::empty:
      {
        if (_val)
          {
            set_mem_var_int (TypeMemVar::size_data, 0);
          }
        break;
      }
    case TypeFlagsBuff::null:
    case TypeFlagsBuff::convolution_support:
    case TypeFlagsBuff::convolution_data:
      {
        return;      //auto flags
      }
    default:
      break;
    }

  flags_.set (_type, _val);
  return;
}


bool
VideoBuff::get_flag_int (const TypeFlagsBuff& _type) const
{
  UASSERT (_type < TypeFlagsBuff::max_bound);

  switch (_type)
    {
    case TypeFlagsBuff::null:
      {
        if (!get_raw_buff () || 0 == get_raw_buff ()->get_buff_size ())
          {
            return true;
          }

        return false;
      }
    case TypeFlagsBuff::empty:
      {
        if (get_flag (TypeFlagsBuff::null))
          {
            return true;
          }

        if (0 == (*this)[TypeMemVar::size_data])
          {
            return true;
          }

        if (va_info_.minor_.empty ())
          {
            return true;
          }
        return false;
      }
    case TypeFlagsBuff::convolution_data:
      {
        if (get_flag (TypeFlagsBuff::empty))
          {
            return false;
          }

        if ((*this)[TypeMemVar::size_data] < cs16buffs::max_size_core_conv * get_dim_var (TypeDimVar::stride))
          {
            return false;
          }

        const dim_type _yoffset    = cs16buffs::half_max_size_core_conv * get_dim_var (TypeDimVar::stride);
        const dim_type _min_offset = _yoffset + cs16buffs::x_off_edge_conv;

        if ((*this)[TypeMemVar::offset_data] < _min_offset)
          {
            return false;
          }

        if ((*this)[TypeMemVar::size_buffer] < 2 * _min_offset + get_dim_var (TypeDimVar::stride) * get_dim_var (TypeDimVar::height))
          {
            return false;
          }

        return true;
      }
    default:
      break;
    }

  return flags_.get (_type);
}

}}}}      // namespace utils::dbuffs::video::impl
