/**
\file   func_load_bmp_to_rgb16.cpp
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date   01.01.2017
\brief    Function for load data from bmp32 file and convert to r16g16b16 format
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "func_load_bmp_to_rgb16.hpp"

// old shit
namespace libs::helpers::bmp
{
#if 0
bool
load_bmp_to_s16bit (
  ::libs::optim::s16bit::convert::rgb32_rgb48_funct convert_funct,
  ::libs::optim::io::mtcall_func                    mirror_funct,
  const std::string&                                name_file,
  std::int16_t**                                    r16,
  std::int16_t**                                    g16,
  std::int16_t**                                    b16,
  std::int32_t*                                     width,
  std::int32_t*                                     height,
  std::int32_t*                                     stride_byte,
  int                                               need_div_stride_byte,
  std::int32_t*                                     max_size_buf)
{
  BITMAPFILEHEADER            loc_hdr;
  BITMAPINFOHEADER            loc_bih;
  ::utils::SmartHandleFile    hfile;
  base_funcs::mem::CCharBlock tbuf1;
  base_funcs::mem::CCharBlock loc_aligned_rgb32;

  U3_ASSERT (convert_funct);

  if (0 == convert_funct)
  {
    convert_funct = ::libs::optim::s16bit::convert::rgb32_to_rgb48_alu;
  }

  U3_ASSERT (mirror_funct);

  if (0 == mirror_funct)
  {
    mirror_funct = ::libs::optim::s16bit::block::flip_y_mmx;
  }

  *width       = 0;
  *height      = 0;
  *stride_byte = 0;

  // load header and get info, file must include 32 bit data and exist
  U3_CHECK (hfile.Open (name_file, "rb"));

  if (!hfile.IsReadable ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  std::size_t readen_bytes = 0;

  std::uint8_t* loc_array_buf[] = {
    r1einterpret_cast< std::uint8_t* > (&loc_hdr),
    r1einterpret_cast< std::uint8_t* > (&loc_bih)
  };
  unsigned long loc_array_size_buf[] = {
    sizeof (loc_hdr),
    sizeof (loc_bih)
  };

  for (uint32_t indx1 = 0; indx1 < std::size (loc_array_buf); indx1++)
  {
    memset (loc_array_buf[indx1], 0, loc_array_size_buf[indx1]);
  }

  for (uint32_t indx1 = 0; indx1 < std::size (loc_array_buf); indx1++)
  {
    readen_bytes = 0;

    if (!hfile.Read (loc_array_size_buf[indx1], loc_array_buf[indx1], readen_bytes))
    {
      U3_ASSERT_SIGNAL ("failed");
      return false;
    }
#  if 0
      ????
      BOOL res = ReadFile(
        hfile.GetHandle(),
        loc_array_buf[ indx1 ],
        loc_array_size_buf[ indx1 ],
        &readen_bytes,
        0 );
      if( ( readen_bytes != loc_array_size_buf[ indx1 ] ) ||
        ( !res ) )
      {
        U3_ASSERT_SIGNAL( "failed" );
        return hr;
      }
#  endif
  }

  if (32 != loc_bih.biBitCount)
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  bool loc_need_revers = loc_bih.biHeight > 0 ? true : false;

  loc_bih.biHeight = loc_bih.biHeight > 0 ? loc_bih.biHeight : -loc_bih.biHeight;
  loc_bih.biWidth  = loc_bih.biWidth > 0 ? loc_bih.biWidth : -loc_bih.biWidth;

  // if needed realloc memory
  if ((loc_bih.biHeight <= 0) ||
      (loc_bih.biWidth <= 0))
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  // load image
  int loc_stride_buf         = loc_bih.biWidth * sizeof (std::uint8_t) * 4;
  int loc_aligned_stride_buf = loc_stride_buf;
  int loc_need_size_temp_buf = loc_bih.biHeight * loc_stride_buf;

  tbuf1.alloc (loc_need_size_temp_buf);

  if (0 == tbuf1.get ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  readen_bytes = 0;
#  if 0
    BOOL res = ReadFile(
      hfile.GetHandle(),
      tbuf1.get(),
      loc_need_size_temp_buf,
      &readen_bytes,
      0 );
#  endif
  if (!hfile.Read (loc_need_size_temp_buf, tbuf1.get (), readen_bytes))
  // if( ( readen_bytes != (uint32_t )loc_need_size_temp_buf ) ||
  //( !res ) )
  {
    U3_ASSERT_SIGNAL ("failed");
    //<name_fileDumpString( true );
    return false;
  }

  // 16.06.2016 - needed aligne buf to 16 byte
  if (loc_stride_buf & 0x0000000F)
    ? ? ?
    {
      loc_aligned_stride_buf = (loc_stride_buf + 16) & ::libs::helpers::mem::consts::align_ptr16;

      loc_aligned_rgb32.alloc (loc_aligned_stride_buf * loc_bih.biHeight);

      if (0 == loc_aligned_rgb32.get ())
      {
        U3_ASSERT_SIGNAL ("failed");
        return false;
      }

      U3_CHECK (::libs::optim::s16bit::resize::scale1::restride_short_string (
        tbuf1.get (),
        loc_aligned_rgb32.get (),
        loc_stride_buf,
        loc_bih.biHeight,
        loc_stride_buf,
        loc_aligned_stride_buf));

      tbuf1 = loc_aligned_rgb32;
    }

  U3_CHECK (convert_funct (
    tbuf1.get (),
    r16,
    g16,
    b16,
    max_size_buf,
    loc_aligned_stride_buf,
    stride_byte,
    loc_bih.biWidth,
    loc_bih.biHeight));

#  if 0
    if (FAILED (hr) )
    {
      U3_ASSERT_SIGNAL( "failed" );
      hr = E_FAIL;
      return hr;
    }
#  endif
  *width  = loc_bih.biWidth;
  *height = loc_bih.biHeight;

  // 27.07.2016 если требуется переворачиваем изображение
  if (loc_need_revers)
  {
    std::int16_t* loc_array_revers_y[] = {
      *r16,
      *g16,
      *b16
    };

    for (uint32_t indx1 = 0; indx1 < std::size (loc_array_revers_y); indx1++)
    {
#  if 1
      U3_ASSERT_SIGNAL ("failed");   // call
#  else
      ::libs::optim::io::MCallInfo info (
        ::libs::optim::io::MCallInfo::dests_type { { loc_array_revers_y[indx1], 0, 0 } },
        ::libs::optim::io::MCallInfo::sources_type { { 0, 0, 0 } },
        0,
        *stride_byte,
        0,
        loc_bih.biWidth,
        loc_bih.biHeight,
        0,
        0,
        0,
        0);

      U3_CHECK_DRES (mirror_funct (info));
#  endif
    }
  }
  return true;
}
#endif
}   // namespace libs::helpers::bmp
