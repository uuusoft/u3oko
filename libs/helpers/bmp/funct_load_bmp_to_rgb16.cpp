//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file   funct_load_bmp_to_rgb16.cpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date   01.01.2017
\copyright  www.uuusoft.com
\brief    Function for load data from bmp32 file and convert to r16g16b16 format
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "funct_load_bmp_to_rgb16.hpp"
// old shit
namespace libs { namespace helpers { namespace bmp {

#if 0
  bool load_bmp_to_s16bit (
    ::libs::optim::s16bit::convert::rgb32_rgb48_funct convert_funct,
    ::libs::optim::funct_mcall_type               mirror_funct,
    const std::string&                  name_file,
    short**                       r16,
    short**                       g16,
    short**                       b16,
    int*                        width,
    int*                        height,
    int*                        stride_byte,
    int                         need_div_stride_byte,
    int*                        max_size_buffer)
  {
    BITMAPFILEHEADER        loc_hdr;
    BITMAPINFOHEADER        loc_bih;
    ::utils::SmartHandleFile    hfile;
    base_functs::mem::CCharBlock  _tbuff1;
    base_functs::mem::CCharBlock  loc_aligned_rgb32;

    UASSERT ( convert_funct );

    if (0 == convert_funct )
    {
      convert_funct = ::libs::optim::s16bit::convert::rgb32_to_rgb48_alu;
    }

    UASSERT ( mirror_funct );

    if (0 == mirror_funct )
    {
      mirror_funct = ::libs::optim::s16bit::block::flip_y_mmx;
    }
    
    *width = 0;
    *height = 0;
    *stride_byte = 0;

    //load header and get info, file must include 32 bit data and exist
    CHECK_CALL (hfile.Open (name_file, "rb") );

    if ( !hfile.IsReadable () )
    {
      UASSERT_SIGNAL( "failed" );
      return false;
    }

    std::size_t readen_bytes = 0;

    unsigned char* loc_array_buffer[] =
    {
      r1einterpret_cast<unsigned char*>( &loc_hdr),
      r1einterpret_cast<unsigned char*>( &loc_bih)
    };
    unsigned long loc_array_size_buffer[] =
    {
      sizeof ( loc_hdr),
      sizeof ( loc_bih)
    };

    for (unsigned int indx1 = 0; indx1 < COUNT_OF ( loc_array_buffer); indx1++)
    {
      memset ( loc_array_buffer[indx1], 0, loc_array_size_buffer[indx1] );
    }

    for (unsigned int indx1 = 0; indx1 < COUNT_OF ( loc_array_buffer); indx1++)
    {
      readen_bytes = 0;

      if ( !hfile.Read ( loc_array_size_buffer[indx1], loc_array_buffer[indx1], readen_bytes) )
      {
        UASSERT_SIGNAL( "failed" );
        return false;
      }
#if 0
      ????
      BOOL res = ReadFile(
        hfile.GetHandle(),
        loc_array_buffer[ indx1 ],
        loc_array_size_buffer[ indx1 ],
        &readen_bytes,
        0 );
      if( ( readen_bytes != loc_array_size_buffer[ indx1 ] ) ||
        ( !res ) )
      {
        UASSERT_SIGNAL( "failed" );
        return hr;
      }
#endif
    }

    if ( 32 != loc_bih.biBitCount )
    {
      UASSERT_SIGNAL( "failed" );
      return false;
    }

    bool  loc_need_revers = loc_bih.biHeight > 0 ? true : false;

    loc_bih.biHeight = loc_bih.biHeight > 0 ? loc_bih.biHeight : -loc_bih.biHeight;
    loc_bih.biWidth = loc_bih.biWidth > 0 ? loc_bih.biWidth : -loc_bih.biWidth;

    //if needed realloc memory
    if ( ( loc_bih.biHeight <= 0) ||
      ( loc_bih.biWidth <= 0) )
    {
      UASSERT_SIGNAL( "failed" );
      return false;
    }

    //load image
    int loc_stride_buff = loc_bih.biWidth * sizeof (unsigned char) * 4;
    int loc_aligned_stride_buff = loc_stride_buff;
    int loc_need_size_temp_buff = loc_bih.biHeight * loc_stride_buff;

    _tbuff1.alloc ( loc_need_size_temp_buff );

    if (0 == _tbuff1.get () )
    {
      UASSERT_SIGNAL( "failed" );
      return false;
    }

    readen_bytes = 0;
#if 0
    BOOL res = ReadFile(
      hfile.GetHandle(),
      _tbuff1.get(),
      loc_need_size_temp_buff,
      &readen_bytes,
      0 );
#endif
    if ( !hfile.Read ( loc_need_size_temp_buff, _tbuff1.get (), readen_bytes) )
    //if( ( readen_bytes != (unsigned int )loc_need_size_temp_buff ) ||
      //( !res ) )
    {
      UASSERT_SIGNAL( "failed" );
      //<name_file.DumpString( true );
      return false;
    }

    // 16.06.2016 - needed aligne buffer to 16 byte
    if ( loc_stride_buff & 0x0000000F)???
    {
      loc_aligned_stride_buff = ( loc_stride_buff + 16) & ::libs::helpers::mem::consts::align_ptr16;

      loc_aligned_rgb32.alloc ( loc_aligned_stride_buff * loc_bih.biHeight );

      if (0 == loc_aligned_rgb32.get () )
      {
        UASSERT_SIGNAL( "failed" );
        return false;
      }

      CHECK_CALL ( ::libs::optim::s16bit::resize::scale1::restride_short_string (
        _tbuff1.get (),
        loc_aligned_rgb32.get (),
        loc_stride_buff,
        loc_bih.biHeight,
        loc_stride_buff,
        loc_aligned_stride_buff ) );

      _tbuff1 = loc_aligned_rgb32;
    }

    CHECK_CALL ( convert_funct (
      _tbuff1.get (),
      r16, g16, b16,
      max_size_buffer,
      loc_aligned_stride_buff,
      stride_byte,
      loc_bih.biWidth,
      loc_bih.biHeight ) );

#if 0
    if (FAILED (hr) )
    {
      UASSERT_SIGNAL( "failed" );
      hr = E_FAIL;
      return hr;
    }
#endif
    *width = loc_bih.biWidth;
    *height = loc_bih.biHeight;

    // 27.07.2016 если требуется переворачиваем изображение
    if ( loc_need_revers)
    {
      short* loc_array_revers_y[] =
      {
        *r16,
        *g16,
        *b16
      };

      for (unsigned int indx1 = 0; indx1 < COUNT_OF ( loc_array_revers_y); indx1++)
      {
#if 1
        UASSERT_SIGNAL( "failed" );//call
#else
         ::libs::optim::MCallInfo _info (
           ::libs::optim::MCallInfo::dests_type {{loc_array_revers_y[indx1], 0, 0}},
           ::libs::optim::MCallInfo::sources_type {{0, 0, 0}},
          0, *stride_byte, 0,
          loc_bih.biWidth, loc_bih.biHeight,
          0, 0, 0, 0);

        CHECKRES ( mirror_funct ( _info ) );
#endif
      }
    }
    return true;
  }
#endif

}}}      // namespace libs::helpers::bmp
