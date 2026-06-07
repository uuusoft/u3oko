#pragma once
/**
\file       url-decode-func.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    mhttp
\original   http://www.boost.org/doc/libs/1_46_0/doc/html/boost_asio/example/http/server3/request_handler.cpp.
*/

namespace modules::mhttp::appl::helpers
{
/// Функция декодирования адреса
inline bool
url_decode (const std::string& in, std::string& out)
{
  out.clear ();
  out.reserve (in.size ());

  for (std::size_t i = 0; i < in.size (); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size ())
      {
        int                value = 0;
        std::istringstream is (in.substr (i + 1, 2));

        if (is >> std::hex >> value)
        {
          out += U3_CAST_INT8 (value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}
}   // namespace modules::mhttp::appl::helpers
