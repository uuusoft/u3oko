/**
\file       work-with-string-bufs-funcs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "work-with-string-bufs-funcs.hpp"

namespace libs::helpers::strings
{
bool
inplace_replace_substring (
  const syn::replace_val_type* vals,
  const std::size_t            vals_count,
  std::string&                 buf)
{
  bool ret = false;
  std::for_each (
    vals, vals + vals_count, [&buf, &ret] (const syn::replace_val_type& val) {
      const char* replace_str = nullptr;
      while ((replace_str = strstr (buf.c_str (), val.first.c_str ())))
      {
        if (val.first.length () < val.second.length ())
        {
          U3_XLOG_ERROR ("replace" + TOLOG (val.first) + TOLOG (val.second) + VTOLOG (val.first.length ()) + VTOLOG (val.second.length ()));
          ret = false;
          break;
        }
        memset (::libs::helpers::casts::reinterpret_cast_helper< void* > (const_cast< char* > (replace_str)), ' ', val.first.length ());
        memcpy (const_cast< char* > (replace_str), val.second.c_str (), val.second.length ());
        ret = true;
      } });
  return ret;
}


bool
replace_substring (
  const syn::replace_val_type& val,
  const std::string&           srcbuf,
  std::string&                 dstbuf)
{
  bool        ret         = false;
  std::size_t srcoff      = 0;
  const char* replace_str = nullptr;

  dstbuf.clear ();

  while ((replace_str = strstr (srcbuf.c_str () + srcoff, val.first.c_str ())))
  {
    if (val.first.length () < val.second.length ())
    {
      U3_XLOG_ERROR ("replace" + TOLOG (val.first) + TOLOG (val.second) + VTOLOG (val.first.length ()) + VTOLOG (val.second.length ()));
      ret = false;
      break;
    }

    const std::size_t cpyoff = replace_str - srcbuf.c_str ();

    if (srcoff < cpyoff)
    {
      dstbuf += std::string (srcbuf.c_str () + srcoff, cpyoff - srcoff);
    }

    dstbuf += val.second;
    ret    = true;
    srcoff = (replace_str - srcbuf.c_str ()) + val.first.length ();
  }

  if (ret)
  {
    if (srcoff < srcbuf.length ())
    {
      dstbuf += std::string (srcbuf.c_str () + srcoff, srcbuf.length () - srcoff);
    }
  }
  else
  {
    dstbuf = srcbuf;
  }
  return ret;
}


bool
replace_substring (
  const syn::replace_val_type* vals,
  const std::size_t            vals_count,
  const std::string&           srcbuf,
  std::string&                 dstbuf)
{
  bool        ret     = false;
  std::string tempbuf = srcbuf;

  dstbuf.clear ();

  std::for_each (
    vals,
    vals + vals_count,
    [&dstbuf, &tempbuf, &ret] (const syn::replace_val_type& val) {
      ret     = replace_substring (val, tempbuf, dstbuf) || ret;
      tempbuf = dstbuf;
    });

  if (!ret)
  {
    dstbuf = srcbuf;
  }
  return ret;
}
}   // namespace libs::helpers::strings
