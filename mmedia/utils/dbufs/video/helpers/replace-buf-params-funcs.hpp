#pragma once
/**
\file       replace-buf-params-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_dbufs
*/

namespace utils::dbufs::video::helpers
{
inline void
replace_buf_params (
  IVideoBuf&          buf,
  IVideoBuf::dim_type off_data,
  IVideoBuf::dim_type size_data)
{
  U3_CHECK (size_data + off_data <= buf[MemVars::size_buf], VTOLOG (size_data) + VTOLOG (off_data) + VTOLOG (buf[MemVars::size_buf]));

  buf.set_mem_var (MemVars::offset_data, off_data);
  buf.set_mem_var (MemVars::size_data, size_data);
  buf.set_flag (BufFlags::convolution_support, false);
}
}   // namespace utils::dbufs::video::helpers
