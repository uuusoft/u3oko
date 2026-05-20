#pragma once
/**
\file       buf_get_data_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_dbufs
*/

namespace utils::dbufs::video::helpers
{
template< typename TypeAs >
TypeAs
get_buf_as (IVideoBuf::raw_ptr buf)
{
  return U3_CAST_REINTERPRET< TypeAs > (buf->get_buf ());
}


template< typename TypeAs >
const TypeAs
get_const_buf_as (IVideoBuf::craw_ptr buf)
{
  return U3_CAST_REINTERPRET< const TypeAs > (buf->get_cbuf ());
}


template< typename TypeAs >
TypeAs
get_data_as (IVideoBuf::raw_ptr buf)
{
  U3_CHECK (!buf->get_flag (BufFlags::null), "try get data from null buf");
  return U3_CAST_REINTERPRET< TypeAs > (buf->get_buf () + (*buf)[MemVars::offset_data]);
}


inline std::uint8_t*
get_data (IVideoBuf::raw_ptr buf)
{
  return get_data_as< std::uint8_t* > (buf);
}


template< typename TypeAs >
const TypeAs
get_const_data_as (IVideoBuf::craw_ptr buf)
{
  U3_CHECK (!buf->get_flag (BufFlags::null), "try get data from null buf");
  return U3_CAST_REINTERPRET< const TypeAs > (buf->get_cbuf () + (*buf)[MemVars::offset_data]);
}


inline const std::uint8_t*
get_const_data (IVideoBuf::craw_ptr buf)
{
  return get_const_data_as< const std::uint8_t* > (buf);
}


template< typename TypeAs >
TypeAs
get_data_with_off_as (IVideoBuf::raw_ptr buf, const IVideoBuf::dim_type off)
{
  U3_CHECK (!buf->get_flag (BufFlags::null), "try get data from null buf");
  return U3_CAST_REINTERPRET< TypeAs > (buf->get_buf () + (*buf)[MemVars::offset_data] + off);
}


template< typename TypeAs >
const TypeAs
get_const_data_with_off_as (IVideoBuf::craw_ptr buf, const IVideoBuf::dim_type off)
{
  return U3_CAST_REINTERPRET< const TypeAs > (get_const_buf_as< const std::uint8_t* > (buf) + (*buf)[MemVars::offset_data] + off);
}


template< typename TypeAs >
TypeAs
get_line_data_as (IVideoBuf::raw_ptr buf, IVideoBuf::dim_type indxy)
{
  U3_CHECK (!buf->get_flag (BufFlags::empty), "empty flag in buf");
  U3_CHECK (indxy < buf->get_dim_var (Dims::height), "invalid height indxy");

  const IVideoBuf::dim_type off = buf->get_dim_var (Dims::stride) * indxy;
  return get_data_with_off_as< TypeAs > (buf, off);
}


template< typename TypeAs >
const TypeAs
get_line_const_data_as (IVideoBuf::craw_ptr buf, IVideoBuf::dim_type indxy)
{
  U3_CHECK (!buf->get_flag (BufFlags::empty), "empty flag in buf");
  U3_CHECK (indxy < buf->get_dim_var (Dims::height), "invalid height indxy");

  const IVideoBuf::dim_type off = buf->get_dim_var (Dims::stride) * indxy;
  return get_const_data_with_off_as< const TypeAs > (buf, off);
}
}   // namespace utils::dbufs::video::helpers
