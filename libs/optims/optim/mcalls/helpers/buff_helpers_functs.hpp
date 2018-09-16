#pragma once
/**
\file       buff_helpers_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief    
*/

namespace libs { namespace optim { namespace mcalls { namespace helpers {
/**
\brief      empty brief
\param[in]  _buff ???
\param[in]  _val  ???
*/
inline void
fill (io::ProxyBuff* _buff, const short _val)
{
  UASSERT (_buff);

  for (std::size_t _indxy = 0; _indxy < _buff->height_; ++_indxy)
    {
      short* _rbuff = _buff->get_line (_indxy);

      std::fill (&_rbuff[0], &_rbuff[_buff->width_], _val);
    }
  return;
}

}}}}      // namespace libs::optim::mcalls::helpers
