#pragma once
/**
\file       dump-buffer2jpeg-file.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       29.07.2018
\copyright  www.uuusoft.com
\project    uuu_codec_functs
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen { namespace helpers {
/**
\brief  ???
*/
inline void
dump_buffer2file (const IVideoBuff::raw_ptr _out_buff, const std::string& _name_file)
{
  if (!_out_buff || _out_buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      return;
    }

  UASSERT (!_name_file.empty ());
  std::ofstream _file (_name_file.c_str (), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
  if (!_file.is_open ())
    {
      XULOG_ERROR ("failed open file for dump jpeg, " << _name_file);
      return;
    }

  const char*         _write_data   = ::utils::dbuffs::video::helpers::get_const_buff_as<const char*> (_out_buff);
  const HeaderIFrame* _head         = UUU_CODECS_CAST<const HeaderIFrame*> (_write_data);
  const auto&         _base_head    = _head->base_part_;
  const char*         _sdata        = _write_data + _head->base_part_.size_;
  const char*         _cdata        = _sdata + _head->coff_;
  unsigned int        _src_size_res = _head->csize_;
  const auto          _size_data    = (*_out_buff)[::utils::dbuffs::TypeMemVar::size_data];

  dump (*_head);
  _file.write (_cdata, _src_size_res);

  if (_file.bad ())
    {
      XULOG_ERROR ("failed dump jpeg in file, " << _name_file);
    }
  return;
}

}}}}      // namespace dlls::codecs::codec_gen::helpers
