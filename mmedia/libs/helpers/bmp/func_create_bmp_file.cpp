/**
\file       func_create_bmp_file.cpp
\brief      Дополнительные функции
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "func_create_bmp_file.hpp"

//  old shit
namespace libs::helpers::bmp
{
#ifdef U3_FAKE_DISABLE
HRESULT
CreateImageBMPFile (base_funcs::mem::CCharBlock& image, const std::uint8_t* data, int size_data, AM_MEDIA_TYPE info)
{
  HRESULT          hr = S_OK;
  VIDEOINFOHEADER  vinfo;
  VIDEOINFOHEADER2 vinfo2;
  // int temp_size_image = 0;
  BITMAPFILEHEADER hdr;
  BITMAPINFOHEADER bih;
  // int size_array_color = 0;
  int           i1 = 0, i2 = 0;
  signed int    red = 0, green = 0, blue = 0;
  unsigned long k_red = 0, k_green = 0, k_blue = 0;
  std::uint8_t  r_red = 0, r_green = 0, r_blue = 0;
  unsigned long m_red = 0, m_green = 0, m_blue = 0;
  unsigned long now_color = 0;
  // int size1 = 0;
  int my_picth  = 0;
  int offset    = 0;
  int old_pitch = 0;

  // 09.03.2016
  U3_ASSERT_SIGNAL ("failed");
#  if 0
    if( ( data == 0 ) || 
      ( size_data == 0 ) )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return E_FAIL;
    };

    if( ( info.majortype != IID_Video ) || 
      ( info.pbFormat == 0 ) ||
      ( ( info.formattype != IID_FORMAT_Video ) && ( info.formattype != IID_FORMAT_Video2 ) ) ||
      ( ( info.subtype != uids::minor::IID_MT_UYVY ) && 
      ( info.subtype != uids::minor::id_val::yuy2 ) && 
      ( info.subtype != uids::minor::IID_MT_Y8 ) && 
      ( info.subtype != uids::minor::IID_MT_RGB565 ) && 
      ( info.subtype != uids::minor::IID_MT_RGB555 ) && 
      ( info.subtype != uids::minor::IID_MT_RGB24 ) && 
      ( info.subtype != uids::minor::IID_MT_RGB32 ) ) )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return E_FAIL;
    };
    /**/

    image.free();

    if( info.formattype == IID_FORMAT_Video )
    {
      vinfo = *(r1einterpret_cast<VIDEOINFOHEADER*>(info.pbFormat) );
      bih = vinfo.bmiHeader;
    }
    else
    {
      vinfo2 = *(r1einterpret_cast<VIDEOINFOHEADER2*>(info.pbFormat) );
      bih = vinfo2.bmiHeader;
    }

    my_picth = ( ( bih.biWidth * 3 + 3 ) / 4 ) * 4;
    old_pitch = ( ( bih.biWidth * ( bih.biBitCount / 8 ) + 3 ) / 4 ) * 4;
    size_array_color = my_picth * bih.biHeight;

    //выделяем паямть под массив и шапку
    temp_size_image = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + size_array_color + sizeof( RGBQUAD );

    image.alloc( temp_size_image );
    if( FAILED( hr ) )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return hr;
    }

    //формируем шапку файла - она идентичная для всех типов входных форматов
    bih.biBitCount      = 24;
    bih.biClrImportant  = 0;
    bih.biClrUsed       = 0;
    bih.biCompression   = BI_RGB;
    bih.biPlanes        = 1;
    bih.biSize          = sizeof( BITMAPINFOHEADER );
    bih.biSizeImage     = size_array_color;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;

    hdr.bfType      = 0x4d42;
    hdr.bfSize      = ( sizeof(BITMAPFILEHEADER) + bih.biSize + bih.biSizeImage + sizeof( RGBQUAD ) );
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 

    hdr.bfOffBits   = (unsigned long) sizeof(BITMAPFILEHEADER) + bih.biSize + sizeof( RGBQUAD ); 

    *r1einterpret_cast<BITMAPFILEHEADER *>(image.get() + offset ) = hdr; 
    offset = offset + sizeof( BITMAPFILEHEADER );

    *r1einterpret_cast<BITMAPINFOHEADER*>(image.get() + offset ) = bih; 
    offset = offset + sizeof( BITMAPINFOHEADER );

    *r1einterpret_cast<unsigned long *>(image.get() + offset) = 0;
    offset = offset + sizeof( RGBQUAD );

    if( ( info.subtype == uids::minor::IID_MT_UYVY ) ||
      ( info.subtype == uids::minor::id_val::yuy2 ) || 
      ( info.subtype == uids::minor::IID_MT_Y8 ) )
    {
      if( info.subtype == uids::minor::id_val::yuy2 )
      {
        signed int Y = 0, U = 0, V = 0;
        size1 = 2;

        for( i1 = 0; i1 < bih.biHeight; i1++ )
        {
          for( i2 = 0; i2 < bih.biWidth; i2++ )
          {
            Y = *( (std::uint8_t*)data + i1 * old_pitch + i2 * size1 );

            if( ( ( i2 >> 1 ) << 1 ) == i2 )
            {
              V = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 1 );
              U = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 3 );
            }
            else
            {
              V = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 - 1 );
              U = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 1 );
            };

#    define _S(a) (a) > 255 ? 255 : (a) < 0 ? 0 : \
                                              (a)

#    define _R(y, u, v) (0x2568 * (y) + 0x3343 * (u)) / 0x2000
#    define _G(y, u, v) (0x2568 * (y) - 0x0c92 * (v) - 0x1a1e * (u)) / 0x2000
#    define _B(y, u, v) (0x2568 * (y) + 0x40cf * (v)) / 0x2000

            Y = Y - 16;
            U = U - 128;
            V = V - 128;
            red   = _R( Y, U, V );
            green = _G( Y, U, V );
            blue  = _B( Y, U, V );


            red   = _S( red );
            blue  = _S( blue );
            green = _S( green );


            *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 2 ) = (std::uint8_t)red;
            *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 1 ) = (std::uint8_t)green;
            *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 0 ) = (std::uint8_t)blue;
          };
        };
      }
      else
        if( info.subtype == uids::minor::IID_MT_UYVY )
        {
          signed int Y, U, V;
          size1 = 2;

          for( i1 = 0; i1 < bih.biHeight; i1++ )
          {
            for( i2 = 0; i2 < bih.biWidth; i2++ )
            {
              Y = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 1 );

              if( ( ( i2 >> 1 ) << 1 ) == i2 )
              {
                U = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 0 );
                V = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 2 );
              }
              else
              {
                U = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 - 2 );
                V = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 0 );
              };


#    define _S(a) (a) > 255 ? 255 : (a) < 0 ? 0 : \
                                              (a)

#    define _R(y, u, v) (0x2568 * (y) + 0x3343 * (u)) / 0x2000
#    define _G(y, u, v) (0x2568 * (y) - 0x0c92 * (v) - 0x1a1e * (u)) / 0x2000
#    define _B(y, u, v) (0x2568 * (y) + 0x40cf * (v)) / 0x2000

              Y = Y - 16;
              U = U - 128;
              V = V - 128;
              red   = _R( Y, U, V );
              green = _G( Y, U, V );
              blue  = _B( Y, U, V );


              red   = _S( red );
              blue  = _S( blue );
              green = _S( green );

              *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 2 ) = (std::uint8_t)red;
              *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 1 ) = (std::uint8_t)green;
              *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 0 ) = (std::uint8_t)blue;

            };
          };

        }
        else
          if( info.subtype == uids::minor::IID_MT_Y8 )
          {
            signed int Y = 0;

            for( i1 = 0; i1 < bih.biHeight; i1++ )
            {
              for( i2 = 0; i2 < bih.biWidth; i2++ )
              {
#    define _S(a) (a) > 255 ? 255 : (a) < 0 ? 0 : \
                                              (a)
                Y = *( (std::uint8_t *)data + i1 * old_pitch + i2 );

                red = Y;
                blue = Y;
                green = Y;

                red   = _S( red );
                blue  = _S( blue );
                green = _S( green );

                *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 2 ) = (std::uint8_t)red;
                *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 1 ) = (std::uint8_t)green;
                *(image.get() + offset + ( bih.biHeight - i1 - 1 ) * my_picth + 3 * i2 + 0 ) = (std::uint8_t)blue;
              };
            };
          };

    }
    else
    {   

      //на основе формата поверхности определяем смещения и коэффициенты масштабирования
      //для всех каналов
      if( ( info.subtype == uids::minor::IID_MT_RGB24 ) || 
        ( info.subtype == uids::minor::IID_MT_RGB32 ) )
      {
        m_red = m_green = m_blue = 0x000000FF;

        k_red = k_green = k_blue = (unsigned long)(1.0F );

        r_red = 16;
        r_green = 8;
        r_blue = 0;

        if( info.subtype == uids::minor::IID_MT_RGB24 ) size1 = 3;
        else                                     size1 = 4;
      }
      else
        if( info.subtype == uids::minor::IID_MT_RGB565 )
        {
          m_red = m_blue = 0x0000001F;
          m_green = 0x0000003F;

          k_red = k_blue = (unsigned long)(255.0F / 31.0F );
          k_green = (unsigned long)(255.0F / 63.0F );

          r_red = 11;
          r_green = 5;
          r_blue = 0;

          size1 = 2;
        }
        else
          if( info.subtype == uids::minor::IID_MT_RGB555 )
          {
            m_red = m_blue = m_green = 0x0000001F;

            k_red = k_blue = k_green = (unsigned long)(255.0F / 31.0F );

            r_red = 10;
            r_green = 5;
            r_blue = 0;

            size1 = 2;
          }
          else
          {
            U3_ASSERT_SIGNAL( "failed" );
          };

      int fast_var1 = 0;
      int fast_var3 = 0;
      int fast_var4 = 0;
      unsigned long temp_color = 0;

      for( i1 = 0; i1 < bih.biHeight; i1++ )
      {
        for( i2 = 0; i2 < bih.biWidth; i2++ )
        {
          //второй вариант оптимиации - переход к целочисленным масштабирующим коэффициентам
          //вроде не должен сказатся на качестве
          now_color = *(unsigned long *)( (std::uint8_t *)data + fast_var4 + i2 * size1 );

          temp_color = ( ( k_red   * ( m_red   & ( now_color >> r_red ) ) ) << 16 ) |
            ( ( k_green * ( m_green & ( now_color >> r_green ) ) ) << 8 ) |
            ( k_blue  * ( m_blue  & ( now_color >> r_blue ) ) );

          fast_var3 = r1einterpret_cast<unsigned long>(image.get() ) + offset + fast_var1;

          *r1einterpret_cast<unsigned long *>(fast_var3) = temp_color;
          fast_var1 = fast_var1 + 3;

          /*
          //не оптимизированный вариант
          now_color = *(unsigned long *)( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 );
          red   = (std::uint8_t ) ( k_red   * ( m_red   & ( now_color >> r_red ) ) );
          green = (std::uint8_t ) ( k_green * ( m_green & ( now_color >> r_green ) ) );
          blue  = (std::uint8_t ) ( k_blue  * ( m_blue  & ( now_color >> r_blue ) ) );

          *( temp_image + offset + ( i1 ) * my_picth + 3 * i2 + 2 ) = red;
          *( temp_image + offset + ( i1 ) * my_picth + 3 * i2 + 1 ) = green;
          *( temp_image + offset + ( i1 ) * my_picth + 3 * i2 + 0) = blue;
          */
        };

        fast_var1 = fast_var1 + my_picth - bih.biWidth * 3;
        fast_var4 = fast_var4 + old_pitch;
      };
    }
#  endif
  return hr;
}

HRESULT
CreateImageBMPFile2 (
  base_funcs::mem::CCharBlock& image,
  const std::uint8_t*          data,
  int                          size_data,
  cuuid                        type_data,
  int                          width,
  int                          height,
  bool                         need_dib_section)
{
  HRESULT          hr = S_OK;
  BITMAPFILEHEADER hdr;
  BITMAPINFOHEADER bih;
  // int size_array_color = 0;
  int           i1 = 0, i2 = 0;
  signed int    red = 0, green = 0, blue = 0;
  unsigned long k_red = 0, k_green = 0, k_blue = 0;
  std::uint8_t  r_red = 0, r_green = 0, r_blue = 0;
  unsigned long m_red = 0, m_green = 0, m_blue = 0;
  unsigned long now_color = 0;
  // int size1 = 0;
  int my_picth  = 0;
  int offset    = 0;
  int old_pitch = 0;
  // int temp_i10 = 0;
  // 09.03.2016
  U3_ASSERT_SIGNAL ("failed");
#  if 0
    if( ( data == 0 ) || 
      ( size_data <= 0 ) )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return E_FAIL;
    };
    /**/

    if( ( type_data == GUID_NULL ) || 
      ( width <= 0 ) || 
      ( height <= 0 ) )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return E_FAIL;
    };

    if( ( type_data != uids::minor::IID_MT_UYVY ) && 
      ( type_data != uids::minor::id_val::yuy2 ) && 
      ( type_data != uids::minor::IID_MT_YVU9 ) && 
      ( type_data != uids::minor::IID_MT_YVYU ) && 
      ( type_data != uids::minor::IID_MT_RGB565 ) && 
      ( type_data != uids::minor::IID_MT_RGB555 ) && 
      ( type_data != uids::minor::IID_MT_RGB24 ) && 
      ( type_data != uids::minor::IID_MT_RGB32 ) )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return E_FAIL;
    };

    my_picth = ( ( width * 3 + 3 ) >> 2 ) << 2;
    old_pitch = ( ( width * ( ::libs::helpers::uids::helpers::get_count_bytes_from_format( type_data ) ) + 3 ) >> 2 ) << 2;
    size_array_color = my_picth * height;

    //если нужно выделяем память
    temp_i10 = size_array_color;

    if( need_dib_section )
    {
      temp_i10+= sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + sizeof( RGBQUAD );
    }

    if( image.byte_size() < temp_i10 )
    {
      U3_CHECK_DRES( image.alloc( temp_i10 ) );

      if( FAILED( hr ) )
      {
        U3_ASSERT_SIGNAL( "failed" );
        hr = E_FAIL;
        return hr;
      };
      /**/
    };

    //формируем шапку файла - она идентичная для всех типов входных форматов
    if( need_dib_section )
    {
      bih.biBitCount      = 24;
      bih.biClrImportant  = 0;
      bih.biClrUsed       = 0;
      bih.biCompression   = BI_RGB;
      bih.biPlanes        = 1;
      bih.biSize          = sizeof( BITMAPINFOHEADER );
      bih.biSizeImage     = size_array_color;
      bih.biXPelsPerMeter = 0;
      bih.biYPelsPerMeter = 0;
      bih.biWidth         = width;
      bih.biHeight        = height;

      hdr.bfType      = 0x4d42;
      hdr.bfSize      = ( sizeof(BITMAPFILEHEADER) + bih.biSize + bih.biSizeImage + sizeof( RGBQUAD ) );
      hdr.bfReserved1 = 0; 
      hdr.bfReserved2 = 0; 

      hdr.bfOffBits   = (unsigned long)sizeof(BITMAPFILEHEADER) + bih.biSize + sizeof( RGBQUAD );

      *r1einterpret_cast<BITMAPFILEHEADER*>( (image.get() ) + offset ) = hdr;
      offset = offset + sizeof( BITMAPFILEHEADER );

      *r1einterpret_cast<BITMAPINFOHEADER*>( (image.get() ) + offset ) = bih; 
      offset = offset + sizeof( BITMAPINFOHEADER );

      *r1einterpret_cast<unsigned long*>( (image.get() ) + offset ) = 0;
      offset = offset + sizeof( RGBQUAD );
    };

    if( ( type_data == uids::minor::IID_MT_UYVY ) || 
      ( type_data == uids::minor::id_val::yuy2 ) || 
      ( type_data == uids::minor::IID_MT_YVU9 ) || 
      ( type_data == uids::minor::IID_MT_YVYU ) )
    {

#    define _S(a) (a) > 255 ? 255 : (a) < 0 ? 0 : \
                                              (a)
#    define _R(y, u, v) (0x2568 * (y) + 0x3343 * (u)) / 0x2000
#    define _G(y, u, v) (0x2568 * (y) - 0x0c92 * (v) - 0x1a1e * (u)) / 0x2000
#    define _B(y, u, v) (0x2568 * (y) + 0x40cf * (v)) / 0x2000


      if( type_data == uids::minor::id_val::yuy2 )
      {
        signed int Y = 0, U = 0, V = 0;
        size1 = 2;

        for( i1 = 0; i1 < height; i1++ )
        {
          for( i2 = 0; i2 < width; i2++ )
          {
            Y = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 );

            if( ( ( i2 >> 1 ) << 1 ) == i2 )
            {
              V = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 1 );
              U = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 3 );
            }
            else
            {
              V = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 - 1 );
              U = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 1 );
            };

            Y = Y - 16;
            U = U - 128;
            V = V - 128;
            red   = _R( Y, U, V );
            green = _G( Y, U, V );
            blue  = _B( Y, U, V );

            red   = _S( red );
            blue  = _S( blue );
            green = _S( green );

            *( (image.get() ) + offset + ( height - i1 - 1 ) * my_picth + 3 * i2 + 2 ) = (std::uint8_t)red;
            *( (image.get() ) + offset + ( height - i1 - 1 ) * my_picth + 3 * i2 + 1 ) = (std::uint8_t)green;
            *( (image.get() ) + offset + ( height - i1 - 1 ) * my_picth + 3 * i2 + 0 ) = (std::uint8_t)blue;
          };
        };
      }
      else
        if( type_data == uids::minor::IID_MT_UYVY )
        {
          signed int Y, U, V;
          size1 = 2;

          for( i1 = 0; i1 < height; i1++ )
          {
            for( i2 = 0; i2 < width; i2++ )
            {
              Y = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 1 );

              if( ( ( i2 >> 1 ) << 1 ) == i2 )
              {
                U = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 0 );
                V = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 2 );
              }
              else
              {
                U = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 - 2 );
                V = *( (std::uint8_t *)data + i1 * old_pitch + i2 * size1 + 0 );
              };

              Y = Y - 16;
              U = U - 128;
              V = V - 128;
              red   = _R( Y, U, V );
              green = _G( Y, U, V );
              blue  = _B( Y, U, V );


              red   = _S( red );
              blue  = _S( blue );
              green = _S( green );

              *( (image.get() ) + offset + ( height - i1 - 1 ) * my_picth + 3 * i2 + 2 ) = (std::uint8_t)red;
              *( (image.get() ) + offset + ( height - i1 - 1 ) * my_picth + 3 * i2 + 1 ) = (std::uint8_t)green;
              *( (image.get() ) + offset + ( height - i1 - 1 ) * my_picth + 3 * i2 + 0 ) = (std::uint8_t)blue;
            };
          };

        }
        else
          if( type_data == MEDIASUBTYPE_YVU9 )
          {
#    pragma message("No implement") 
            U3_ASSERT_SIGNAL( "failed" );
          }
          else
            if( type_data == MEDIASUBTYPE_YVYU )
            {
#    pragma message("No implement") 
              U3_ASSERT_SIGNAL( "failed" );
            }
            else
            {
#    pragma message("No implement") 
              U3_ASSERT_SIGNAL( "failed" );
            };
    }
    else
    {

      //на основе формата поверхности определяем смещения и коэффициенты масштабирования
      //для всех каналов
      if( ( type_data == uids::minor::IID_MT_RGB24 ) || 
        ( type_data == uids::minor::IID_MT_RGB32 ) )
      {
        m_red = m_green = m_blue = 0x000000FF;      
        k_red = k_green = k_blue = (unsigned long)1.0F;

        r_red = 16;
        r_green = 8;
        r_blue = 0;

        if( type_data == uids::minor::IID_MT_RGB24 ) size1 = 3;
        else                     size1 = 4;
      }
      else
        if( type_data == uids::minor::IID_MT_RGB565 )
        {
          m_red = m_blue = 0x0000001F;
          m_green = 0x0000003F;

          k_red = k_blue = (unsigned long)(255.0F / 31.0F );
          k_green = (unsigned long)(255.0F / 63.0F );

          r_red = 11;
          r_green = 5;
          r_blue = 0;

          size1 = 2;
        }
        else
          if( type_data == uids::minor::IID_MT_RGB555 )
          {
            m_red = m_blue = m_green = 0x0000001F;      
            k_red = k_blue = k_green = (unsigned long)(255.0F / 31.0F );

            r_red = 10;
            r_green = 5;
            r_blue = 0;

            size1 = 2;
          }
          else
          {
            U3_ASSERT_SIGNAL( "failed" );
          };

      int fast_var1 = 0;
      int fast_var3 = 0;
      int fast_var4 = 0;
      unsigned long temp_color = 0;

      for( i1 = 0; i1 < height; i1++ )
      {
        for( i2 = 0; i2 < width; i2++ )
        {

          //второй вариант оптимиации - переход к целочисленным масштабирующим коэффициентам
          //вроде не должен сказатся на качестве
          now_color = *(unsigned long *)( (std::uint8_t *)data + fast_var4 + i2 * size1 );

          temp_color = 
            ( ( k_red   * ( m_red   & ( now_color >> r_red ) ) ) << 16 ) |
            ( ( k_green * ( m_green & ( now_color >> r_green ) ) ) << 8 ) |
            ( k_blue  * ( m_blue  & ( now_color >> r_blue ) ) );

          fast_var3 = r1einterpret_cast<unsigned long>(image.get() ) + offset + fast_var1;
          *r1einterpret_cast<unsigned long *>(fast_var3) = temp_color;
          fast_var1 = fast_var1 + 3;
        };

        fast_var1 = fast_var1 + my_picth - width * 3;
        fast_var4 = fast_var4 + old_pitch;
      };
    }
#  endif
  return hr;
};


HRESULT
CreateImageBMPFile4x3 (
  base_funcs::mem::CCharBlock& image,
  const std::uint8_t*          data,
  int                          size_data,
  AM_MEDIA_TYPE                info,
  const std::string&           add_text,
  float                        k_mull)
{
  HRESULT hr = S_OK;
  float   f1 = 0.0F, f2 = 0.0F;
  HBITMAP hbmp     = 0;
  HBITMAP old_hbmp = 0;
  HDC     hdc      = 0;
  int     i1       = 0;

  if ((k_mull <= 0.2f) || (k_mull > 1.0F))
  {
    k_mull = 1.0F;
  }

  // сначало формируем кадр исходного размера формата RGB24
  if (FAILED (CreateImageBMPFile (image, data, size_data, info)))
  {
    U3_ASSERT_SIGNAL ("failed");
    return E_FAIL;
  };

  // если нужно корректируем геометрические размеры кадра
  if (image.byte_size () > 0)
  {
    BITMAPINFOHEADER* binfo_header = r1einterpret_cast< BITMAPINFOHEADER* > (image.get () + sizeof (BITMAPFILEHEADER));

    f1 = 768.0F / 576.0F;
    f2 = (float) binfo_header->biWidth / (float) binfo_header->biHeight;

    BITMAPINFO temp_info;
    int        my_picth         = 0;
    int        size_array_color = 0;

    temp_info.bmiHeader = *binfo_header;

    // создаем контекст, совместисмый с текущим режимом дисплея, этим мы
    // себя оганичиваем 16 битами и выше
    hdc          = 0;
    HDC temp_hdc = GetDC (GetDesktopWindow ());

    if (temp_hdc)
    {
      hdc = CreateCompatibleDC (temp_hdc);

      hbmp = CreateCompatibleBitmap (temp_hdc, 768, 576);

      ReleaseDC (GetDesktopWindow (), temp_hdc);
      temp_hdc = 0;
    };

    if (hdc && hbmp)
    {
      if ((old_hbmp = (HBITMAP) SelectObject (hdc, hbmp)) == 0)
      {
        U3_ASSERT_SIGNAL ("failed");
      };

      // копируем в DIB секцию, расширяя если нужно, туда информацию
      i1 = StretchDIBits (
        hdc,
        0,
        0,
        768,
        576,
        0,
        0,
        binfo_header->biWidth,
        binfo_header->biHeight,
        (image.get ()) + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER) + sizeof (RGBQUAD),
        &temp_info,
        DIB_RGB_COLORS,
        SRCCOPY);

      if ((i1 != GDI_ERROR) &&
          (i1))
      {
        if (add_text.length () >= 0)
        {
          RECT rect1;

          SetBkMode (hdc, TRANSPARENT);
          SetBkMode (hdc, OPAQUE);
          SetTextColor (hdc, RGB (0, 155, 155));

          SetRect (&rect1, 0, 0, 700, 200);

          U3_ASSERT_SIGNAL ("failed");
#  if 0
            DrawText( 
              hdc, 
              const_cast<tstring&>( add_text).c_str(), 
              add_text.length(), 
              &rect1, 
              DT_LEFT | DT_TOP | DT_SINGLELINE );
#  endif
        }

        // кооректируем размеры изображения
        binfo_header->biWidth  = 768;
        binfo_header->biHeight = 576;

        my_picth                  = ((binfo_header->biWidth * 3 + 3) / 4) * 4;
        size_array_color          = my_picth * binfo_header->biHeight;
        binfo_header->biSizeImage = size_array_color;

        // выделяем паямть под массив и шапку
        int loc_need_size =
          sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER) + sizeof (RGBQUAD) + binfo_header->biSizeImage;

        U3_CHECK_DRES (image.realloc (loc_need_size));

        if (FAILED (hr))
        {
          U3_ASSERT_SIGNAL ("failed");
          hr = E_FAIL;
          goto END_FUNCT;
        };

        // получаем изображение с поверхности
        binfo_header = r1einterpret_cast< BITMAPINFOHEADER* > (image.get () + sizeof (BITMAPFILEHEADER));

        temp_info.bmiHeader = *binfo_header;

        // копируем отмасштабированное изображение в буфер, который будет записан
        temp_info.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);

        i1 = GetDIBits (
          hdc,
          hbmp,
          0,
          576,
          image.get () + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER) + sizeof (RGBQUAD),
          &temp_info,
          DIB_RGB_COLORS);

        if (i1 == 0)
        {
          U3_ASSERT_SIGNAL ("failed");
        };
      }
      else
      {
        U3_ASSERT_SIGNAL ("failed");
      };
    }
    else
    {
      U3_ASSERT_SIGNAL ("failed");
    };
  }
  else
  {
    U3_ASSERT_SIGNAL ("failed");
  };

END_FUNCT:

  if (hdc)
  {
    SelectObject (hdc, old_hbmp);

    if (DeleteDC (hdc) == false)
    {
      U3_ASSERT_SIGNAL ("failed");
    };

    hdc = 0;
  };

  if (hbmp)
  {
    if (DeleteObject (hbmp) == false)
    {
      U3_ASSERT_SIGNAL ("failed");
    };
    hbmp = 0;
  };
  return hr;
};


HRESULT
CreateImageBMPFile4x3 (
  base_funcs::mem::CCharBlock& image,
  const std::uint8_t*          data,
  int                          size_data,
  cuuid                        subtype,
  int                          width,
  int                          height,
  const std::string&           add_text,
  float                        k_mull)
{
  HRESULT         hr = S_OK;
  int             i1 = 0;
  AM_MEDIA_TYPE   info;
  VIDEOINFOHEADER vinfo;

  // 09.03.2016
  U3_ASSERT_SIGNAL ("failed");
#  if 0
    info.majortype = IID_Video;
    info.pbFormat = r1einterpret_cast<std::uint8_t*>( &vinfo );
    info.formattype = IID_FORMAT_Video;
    info.subtype = subtype;

    SetRect( &vinfo.rcSource, 0, 0, width, height );
    SetRect( &vinfo.rcTarget, 0, 0, width, height );

    vinfo.dwBitRate = 0;
    vinfo.dwBitErrorRate = 0;
    vinfo.AvgTimePerFrame = 0;
    vinfo.bmiHeader.biSize = sizeof( vinfo.bmiHeader );
    vinfo.bmiHeader.biWidth = width;
    vinfo.bmiHeader.biHeight = height;
    vinfo.bmiHeader.biPlanes = 1;
    vinfo.bmiHeader.biSizeImage = 0;
    vinfo.bmiHeader.biXPelsPerMeter = 0;
    vinfo.bmiHeader.biYPelsPerMeter = 0;
    vinfo.bmiHeader.biClrUsed = 0;
    vinfo.bmiHeader.biClrImportant = 0;

    const cuuid array_guid[] = 
    {
      ::libs::helpers::uids::minor::id_val::yuy2,
      ::libs::helpers::uids::minor::IID_MT_UYVY,
      ::libs::helpers::uids::minor::IID_MT_YVYU,
      ::libs::helpers::uids::minor::IID_MT_Y8
    };

    const unsigned long array_short_guid[] = 
    {
      mmioFOURCC( 'Y', 'U', 'Y', '2' ),
      mmioFOURCC( 'U', 'Y', 'V', 'Y' ),
      mmioFOURCC( 'Y', 'V', 'Y', 'U' ),
      mmioFOURCC( ' ', ' ', 'Y', '8' )
    };

    const std::int32_t array_bitcount[] =
    {
      16,
      16,
      16,
      8
    };

    for( i1 = 0; i1 < std::size( array_short_guid ); i1++ )
    {
      if( array_guid[ i1 ] == subtype )
      {
        vinfo.bmiHeader.biBitCount = (WORD)array_bitcount[ i1 ];
        vinfo.bmiHeader.biCompression = array_short_guid[ i1 ];
        break;
      };
    };

    if( i1 == std::size( array_short_guid ) )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return hr;
    };

    hr = CreateImageBMPFile4x3( image, data, size_data, info, add_text, k_mull );
#  endif
  return hr;
}
#endif
}   // namespace libs::helpers::bmp
