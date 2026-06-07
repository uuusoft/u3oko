#pragma once
/**
\file       acoding.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_codec_funcs
*/

#ifdef U3_FAKE_DISABLE
/// Функция арифмтического кодирования
HRESULT
MainCodecObject1::CompressWithACoding (
  const std::uint8_t *input,
  INT                 size_input,
  std::uint8_t       *output,
  INT                *size_compress_output)
{
  DEBUG_INFO_CLASS ("MainCodecObject1::CompressWithACoding");
  HRESULT      hr = S_OK;
  register INT i1 = 0, i2 = 0;
  BOOL         prev_null_escape = false;
  INT          len_prev_escape  = 0;
  FINALLY_BEGIN

  *size_compress_output = 0;
  encode_symbol (symbol, cum_freq) int symbol;     /* Кодиpуемый символ     */
  int                                  cum_freq[]; /* Hакапливаемые частоты */
  {
    long range;                                              /* Шиpина текущего       */
    range = (long) (high - low) + 1;                         /* кодового интеpвала    */
    high  = low +                                            /* Сужение интеpвала ко- */
           (range * cum_freq[symbol - 1]) / cum_freq[0] - 1; /*  дов  до */
    low = low +                                              /* выделенного для symbol*/
          (range * cum_freq[symbol]) / cum_freq[0];
    for (;;)
    { /* Цикл по выводу битов  */
      if (high < Half)
      {                       /* Если в нижней половине*/
        bits_plus_follow (0); /* исходного интеpвала,  */
      } /* то вывод 0            */
      else if (low >= Half)
      {                      /* Если в веpхней, то    */
        bit_plus_follow (1); /* вывод 1, а затем      */
        low -= Half;         /* убpать известную у    */
        high -= Half;        /* гpаниц общую часть    */
      }
      else if (low >= First_qtr /* Если текущий интеpвал */
               && high < Third_qtr)
      {                      /* содеpжит сеpедину ис- */
        bits_to_follow += 1; /* ходного, то вывод еще */
        low -= First_qtr;    /* одного обpатного бита */
        high -= First_qtr;   /* позже, а сейчас       */
      } /* убpать общую часть    */
      else
        break;             /* Иначе выйти из цикла  */
      low  = 2 * low;      /* Расшиpить текущий pа- */
      high = 2 * high + 1; /* бочий кодовый интеpвал*/
    }
  }

  // собственно кодирование
  for (i1 = 0; i1 < ::dlls::codecs::consts::count_elements_macroblock; i1++)
  {
    // встречен не нулевой символ
    if (input[i1])
    {
      // если до этого была нулевая последовательность - надо сформировать соотвествующий байты
      if (prev_null_escape)
      {
        output[(*size_compress_output)++] = 0;
        output[(*size_compress_output)++] = len_prev_escape;

        prev_null_escape = false;
        len_prev_escape  = 0;
      };

      // заносим собтсвенно указанное число
      output[(*size_compress_output)++] = input[i1];
    }
    // встречен нулевой символ
    else
    {
      len_prev_escape++;
      prev_null_escape = true;

#  if 0
      //специально обрабатываем случай, когда последоватльность стала равна 255 - это максимально возможная длина
      //полседовальности - делим ее
      if( len_prev_escape == 255 )
      {
        output[ (*size_compress_output )++ ] = 0;
        output[ (*size_compress_output )++ ] = len_prev_escape;

        prev_null_escape = false;
        len_prev_escape = 0;
      };
#  endif
    };
  };


  // если последний символ был пустой - его то-же надо зафиксировать
  if (prev_null_escape)
  {
    output[(*size_compress_output)++] = 0;
    output[(*size_compress_output)++] = len_prev_escape;
    prev_null_escape                  = false;
  };


#  if 0

  //проходим по блокам и выводим текущие буфера сжатия и расжатия
  char deb_buf1[ 128 ];
  MSG( "Uncompress buf" );

  for( i1 = 0; i1 < size_input; i1++ )
  {
    sprintf( deb_buf1, "%i", input[ i1 ] );
    MSG( deb_buf1 );
  };

  MSG( "Compress buf with RLE" );

  for( i1 = 0; i1 < *size_compress_output; i1++ )
  {
    sprintf( deb_buf1, "%i", (*output )[ i1 ] );
    MSG( deb_buf1 );
  };

#  endif


  FINALLY_END ("MainCodecObject1::CompressWithACoding");
  return hr;
};

#endif
