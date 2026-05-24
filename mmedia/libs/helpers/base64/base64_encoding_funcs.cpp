/**
\file       base64_encoding_funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2018
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "base64_encoding_funcs.hpp"

namespace libs::helpers::base64
{
static constexpr char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

inline bool
is_base64 (std::uint8_t c)
{
  return (isalnum (static_cast< int > (c)) || (static_cast< char > (c) == '+') || (static_cast< char > (c) == '/'));
}


std::string
base64_encode (const std::uint8_t* buf, std::uint64_t bufLen)
{
  std::string  ret;
  std::int32_t i = 0;
  std::int32_t j = 0;
  std::uint8_t char_array_3[3];
  std::uint8_t char_array_4[4];

  while (bufLen--)
  {
    char_array_3[i++] = *(buf++);

    if (i == 3)
    {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; (i < 4); i++)
      {
        ret += base64_chars[char_array_4[i]];
      }

      i = 0;
    }
  }

  if (i)
  {
    for (j = i; j < 3; j++)
    {
      char_array_3[j] = '\0';
    }

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
    {
      ret += base64_chars[char_array_4[j]];
    }

    while ((i++ < 3))
    {
      ret += '=';
    }
  }
  return ret;
}


std::string
base64_encode (const std::string& src)
{
  return base64_encode (U3_CAST_REINTERPRET< const std::uint8_t* > (src.c_str ()), src.length ());
}


std::vector< std::uint8_t >
buf_base64_decode (const std::string& encoded_string)
{
  auto                        in_len = encoded_string.size ();
  std::int32_t                i      = 0;
  std::int32_t                j      = 0;
  std::int32_t                in_    = 0;
  std::uint8_t                char_array_4[4];
  std::uint8_t                char_array_3[3];
  std::vector< std::uint8_t > ret;

  while (in_len-- && (encoded_string[in_] != '=') && is_base64 (encoded_string[in_]))
  {
    char_array_4[i++] = encoded_string[in_];
    in_++;

    if (i == 4)
    {
      for (i = 0; i < 4; i++)
      {
        char_array_4[i] = *std::find (base64_chars, base64_chars + std::size (base64_chars), char_array_4[i]);
      }

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
      {
        ret.push_back (char_array_3[i]);
      }

      i = 0;
    }
  }

  if (i)
  {
    for (j = i; j < 4; j++)
    {
      char_array_4[j] = 0;
    }

    for (j = 0; j < 4; j++)
    {
      char_array_4[j] = *std::find (base64_chars, base64_chars + std::size (base64_chars), char_array_4[j]);
    }

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++)
    {
      ret.push_back (char_array_3[j]);
    }
  }
  return ret;
}


std::string
base64_decode (const std::string& src)
{
#if 1
  const auto temp = buf_base64_decode (src);
  return std::string (temp.begin (), temp.end ());
#else
  const auto  temp = buf_base64_decode (src);
  std::string ret;
  ret.reserve (temp.size () + 1);
  for (auto ch : temp)
  {
    ret.push_back (static_cast< char > (ch));
  }
  return ret;
// return std::string (temp.begin (), temp.end ());
#endif
}
}   // namespace libs::helpers::base64
