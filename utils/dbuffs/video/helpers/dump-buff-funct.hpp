#pragma once
/**
\file       dump-buff-funct.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       12.07.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief
*/

namespace utils { namespace dbuffs { namespace video { namespace helpers {
/**
\brief  ???
*/
inline void
dump (IVideoBuff::craw_ptr _buff, bool _only_filled)
{
  UASSERT (_buff);
  if (_only_filled && (_buff->get_flag (TypeFlagsBuff::empty) || _buff->get_flag (TypeFlagsBuff::null)))
    {
      return;
    }
  XULOG_INFO ("dump IVideoBuff:");
  XULOG_INFO ("   format=" << ::libs::helpers::uids::helpers::get_readable_name (_buff->get_format ()));
  XULOG_INFO ("   flags: fake=" << _buff->get_flag (TypeFlagsBuff::fake) << ", null=" << _buff->get_flag (TypeFlagsBuff::null) << ", empty=" << _buff->get_flag (TypeFlagsBuff::empty) << ", convolution_support=" << _buff->get_flag (TypeFlagsBuff::convolution_support) << ", convolution_data=" << _buff->get_flag (TypeFlagsBuff::convolution_data));
  XULOG_INFO ("   dims: stride=" << _buff->get_dim_var (TypeDimVar::stride) << ", width=" << _buff->get_dim_var (TypeDimVar::width) << ", height=" << _buff->get_dim_var (TypeDimVar::height) << ", size_data=" << (*_buff)[TypeMemVar::size_data] << ", offset_data=" << (*_buff)[TypeMemVar::offset_data] << ", size_buffer=" << (*_buff)[TypeMemVar::size_buffer]);
  return;
}

}}}}      // namespace utils::dbuffs::video::helpers
