#pragma once
/**
\file       buff_get_data_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление вспомогательных функции для конвертации формата буфера.
*/

namespace utils { namespace dbuffs { namespace video { namespace helpers {

template <typename TypeAs>
TypeAs
get_buff_as (IVideoBuff::raw_ptr _buff)
{
  return UUU_MEM_CAST<TypeAs> (_buff->get_buff ());
}


template <typename TypeAs>
const TypeAs
get_const_buff_as (IVideoBuff::craw_ptr _buff)
{
  return UUU_MEM_CAST<const TypeAs> (_buff->get_cbuff ());
}


template <typename TypeAs>
TypeAs
get_data_as (IVideoBuff::raw_ptr _buff)
{
  CHECK_STATE (!_buff->get_flag (TypeFlagsBuff::null), "failed, try get data from null buff");
  return UUU_MEM_CAST<TypeAs> (_buff->get_buff () + (*_buff)[TypeMemVar::offset_data]);
}


inline unsigned char*
get_data (IVideoBuff::raw_ptr _buff)
{
  return get_data_as<unsigned char*> (_buff);
}


template <typename TypeAs>
const TypeAs
get_const_data_as (IVideoBuff::craw_ptr _buff)
{
  CHECK_STATE (!_buff->get_flag (TypeFlagsBuff::null), "failed, try get data from null buff");
  return UUU_MEM_CAST<const TypeAs> (_buff->get_cbuff () + (*_buff)[TypeMemVar::offset_data]);
}


inline const unsigned char*
get_const_data (IVideoBuff::craw_ptr _buff)
{
  return get_const_data_as<const unsigned char*> (_buff);
}


template <typename TypeAs>
TypeAs
get_data_with_off_as (IVideoBuff::raw_ptr _buff, const IVideoBuff::dim_type _off)
{
  CHECK_STATE (!_buff->get_flag (TypeFlagsBuff::null), "failed, try get data from null buff");
  return UUU_MEM_CAST<TypeAs> (_buff->get_buff () + (*_buff)[TypeMemVar::offset_data] + _off);
}


template <typename TypeAs>
const TypeAs
get_const_data_with_off_as (IVideoBuff::craw_ptr _buff, const IVideoBuff::dim_type _off)
{
  return UUU_MEM_CAST<const TypeAs> (get_const_buff_as<const unsigned char*> (_buff) + (*_buff)[TypeMemVar::offset_data] + _off);
}


template <typename TypeAs>
TypeAs
get_line_data_as (IVideoBuff::raw_ptr _buff, IVideoBuff::dim_type _indxy)
{
  CHECK_STATE (!_buff->get_flag (TypeFlagsBuff::empty), "failed, empty buff");
  CHECK_STATE (_indxy < _buff->get_dim_var (TypeDimVar::height), "failed, invalid indxy");

  const IVideoBuff::dim_type _off = _buff->get_dim_var (TypeDimVar::stride) * _indxy;
  return get_data_with_off_as<TypeAs> (_buff, _off);
}


template <typename TypeAs>
const TypeAs
get_line_const_data_as (IVideoBuff::craw_ptr _buff, IVideoBuff::dim_type _indxy)
{
  CHECK_STATE (!_buff->get_flag (TypeFlagsBuff::empty), "failed, empty buff");
  CHECK_STATE (_indxy < _buff->get_dim_var (TypeDimVar::height), "failed, invalid indxy");

  const IVideoBuff::dim_type _off = _buff->get_dim_var (TypeDimVar::stride) * _indxy;
  return get_const_data_with_off_as<const TypeAs> (_buff, _off);
}

}}}}      // namespace utils::dbuffs::video::helpers
