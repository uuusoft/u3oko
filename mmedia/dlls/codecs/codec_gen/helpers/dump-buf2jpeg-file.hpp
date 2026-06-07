#pragma once
/**
\file       dump-buf2jpeg-file.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       29.07.2018
\project    u3_codec_funcs
*/

namespace dlls::codecs::codec_gen::helpers
{
inline void
dump_buf2file (const ::utils::dbufs::video::IVideoBuf::raw_ptr out_buf, const std::string& name_file)
{
  if (!out_buf || out_buf->get_flag (::utils::dbufs::BufFlags::empty))
  {
    U3_LOG_DATA_INFO ("skip dump empty data" + TOLOG (name_file));
    return;
  }

  U3_ASSERT (!name_file.empty ());
  std::ofstream file (name_file.c_str (), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
  if (!file.is_open ())
  {
    U3_LOG_DATA_ERROR ("open file for dump jpeg" + TOLOG (name_file));
    return;
  }

  const char*   write_data   = ::utils::dbufs::video::helpers::get_const_buf_as< const char* > (out_buf);
  const auto*   head         = U3_CAST_CODECS< const ::dlls::codecs::codec_gen::HeaderIFrame* > (write_data);
  const char*   sdata        = write_data + head->base_part_.size_;
  const char*   cdata        = sdata + head->coff_;
  std::uint32_t src_size_res = head->csize_;

  dump (*head);
  file.write (cdata, src_size_res);

  if (file.bad ())
  {
    U3_LOG_DATA_ERROR ("dump jpeg in file" + TOLOG (name_file));
  }
}
}   // namespace dlls::codecs::codec_gen::helpers
