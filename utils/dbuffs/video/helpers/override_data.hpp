#pragma once
/**
\file       override_data.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief
*/

namespace utils { namespace dbuffs { namespace video { namespace helpers {
/**
\brief  ???
*/
inline void
override_data (IVideoBuff& _buff, IVideoBuff::dim_type _off_data, IVideoBuff::dim_type _size_data)
{
  CHECK_STATE (_size_data + _off_data <= _buff[TypeMemVar::size_buffer], "failed, invalid size data");
  _buff.set_mem_var (TypeMemVar::offset_data, _off_data);
  _buff.set_mem_var (TypeMemVar::size_data, _size_data);
  _buff.set_flag (TypeFlagsBuff::convolution_support, false);
  return;
}

}}}}      // namespace utils::dbuffs::video::helpers
