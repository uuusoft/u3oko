#pragma once
/**
\file       freq_dct_b8x8_forward_int.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "TCallParams.hpp"
#include "../consts/vals.hpp"
#include "../helpers/mem/funcs_copy_mem_b8x8.hpp"
#include "../helpers/zigzag/funcs_zigzag_b8x8.hpp"
#include "../helpers/pack/funcs_pack_short2byte_b8x8.hpp"
#include "../helpers/quant/CQuant.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::forward
{
void get_params (::libs::optim::io::MCallInfo& info, TCallParams& params);

template< typename TTDCT8x8 >
void
freq_dct_b8x8_forward_generic (::libs::optim::io::MCallInfo& info)
{
  TCallParams params;
  get_params (info, params);

  TTDCT8x8            impl;
  const std::int32_t  active_swidth = (params.psrc_->width_ / b8x8::consts::dim_elements_macroblock) * b8x8::consts::dim_elements_macroblock * sizeof (std::int16_t);
  const std::int32_t  lsleak_width  = params.psrc_->stride_ - active_swidth;
  const std::int16_t* cur_buf       = params.psrc_->buf ();
  std::uint8_t*       dbuf          = params.pdst_->ubuf ();
  std::int32_t&       out_size      = (*params.prets_)[info.indx_thread_].byte_size_;

  U3_ALIGN_DEFAULT std::int16_t src_block[b8x8::consts::count_elements_macroblock];

  out_size = 0;

  (*params.prets_)[info.indx_thread_].beg_dst_ = dbuf;

  for (std::uint32_t indxy = 0; indxy < params.psrc_->height_; indxy += 8)
  {
    for (std::uint32_t indxx = 0; indxx < params.psrc_->width_; indxx += 8)
    {
      helpers::mem::forward (cur_buf, src_block, params.psrc_->stride_);
      // производим прямое дискретное преобразование для ярскости данного блока
      // после данного преобразования мы получаем блок данных со знаком длиной 16 бит
      // чтобы увеличить коэффикиент сжатия, после квантования, когда данные фактически
      // находятся в диапозоне от -127 до 128 сжимаем их до 8 бит
      //  change to pointer for different I and P frame
#if defined(DEBUG) && 0
      {
        U3_ALIGN_DEFAULT std::int16_t deb_src_block[::dlls::codecs::consts::count_elements_macroblock];

        memcpy (deb_src_block, src_block, sizeof (deb_src_block));
        int res = memcmp (deb_src_block, src_block, sizeof (deb_src_block));

        ::dlls::codecs::dct::fdct_mm32 (deb_src_block);
        ::dlls::codecs::dct::idct_mm32 (deb_src_block);

        res                = memcmp (deb_src_block, src_block, sizeof (deb_src_block));
        volatile bool test = false;
        test;
      }
#endif

      impl (src_block);

#if defined(DEBUG) && 0
      {
        U3_ALIGN_DEFAULT std::int16_t deb_src_block[::dlls::codecs::consts::count_elements_macroblock];
        memcpy (deb_src_block, src_block, sizeof (deb_src_block));
        ASSERT (0 == memcmp (deb_src_block, src_block, sizeof (deb_src_block)));

        vcodec_test::zigzag::forward (deb_src_block);
        vcodec_test::zigzag::backward (deb_src_block);

        ASSERT (0 == memcmp (deb_src_block, src_block, sizeof (deb_src_block)));
        volatile bool test = false;
        test;
      }
#endif

      helpers::zigzag::forward (src_block);

      params.pquanter_->forward (src_block);

#if defined(DEBUG) && 0
      {
        U3_ALIGN_DEFAULT std::int16_t deb_src_block[::dlls::codecs::consts::count_elements_macroblock];
        memcpy (deb_src_block, src_block, sizeof (deb_src_block));
        ASSERT (0 == memcmp (deb_src_block, src_block, sizeof (deb_src_block)));

        quant_.forward (deb_src_block);
        quant_.backward (deb_src_block);

        // ASSERT(0 == memcmp( deb_src_block, src_block, sizeof( deb_src_block) ) );
        volatile bool test = false;
        test;
      }
#endif
#if 0
        helpers::pack::forward64 ( src_block, byte_src_block);

#  if defined(DEBUG) && 0
        {
          U3_ALIGN_DEFAULT std::int16_t deb_src_block[ ::dlls::codecs::consts::count_elements_macroblock ];
          //memcpy( deb_src_block, src_block, sizeof( deb_src_block) );
          //ASSERT(0 == memcmp( deb_src_block, src_block, sizeof( deb_src_block) ) );          
          //quant_.forward( deb_src_block );
          mem::pack::backward64( byte_src_block, deb_src_block );

          U3_CHECK(0 == memcmp( deb_src_block, src_block, sizeof( deb_src_block) ) );
          volatile bool test = false;
        }
#  endif
#endif
      /*
        тут же сжимаем полученный блок с помощью RLE недостатком данного расположения текущего алгоритма
        является изыбтоная трата времени на сжатие не ключевых кадров
        плюсом - возмодность использользования кеша, стоит все-такти протестировать оба варианта
        т.е. фактически мы формируем полностью сжатый ключевой кадр, на более позднем этапе
        если есть возможность сформировать неключевой кадр, мы простро затрем ненужные данные
        */
      int size_rle = 0;
#if 1
      size_rle = b8x8::consts::count_elements_macroblock * sizeof (std::int16_t);
      ::libs::helpers::mem::u3copy (src_block, dbuf + out_size, size_rle);

#elif 0
      size_rle = 65;
      ::libs::helpers::mem::u3copy (byte_src_block, dbuf + out_size, size_rle);
#else
      ::dlls::codecs::entropy::rle::forward65 (byte_src_block, dbuf + out_size, &size_rle);
#endif

      U3_ASSERT (size_rle > 0);

#if defined(DEBUG) && 0
      {
        U3_ALIGN_DEFAULT std::uint8_t deb_byte_src_block[::dlls::codecs::consts::count_elements_macroblock + 4];
        // U3_ALIGN_DEFAULT std::int16_t deb_src_block[ ::dlls::codecs::consts::count_elements_macroblock ];
        // memcpy( deb_src_block, src_block, sizeof( deb_src_block) );
        // ASSERT(0 == memcmp( deb_src_block, src_block, sizeof( deb_src_block) ) );
        // quant_.forward( deb_src_block );
        int temp_comp = 0;
        ::dlls::codecs::entropy::rle::backward (dbuf + out_size, &temp_comp, 65, deb_byte_src_block);

        ASSERT (0 == memcmp (deb_byte_src_block, byte_src_block, sizeof (deb_byte_src_block)));
        ASSERT (temp_comp == size_rle);
        volatile bool test = false;
        test;
      }
#endif

      out_size += size_rle;
      cur_buf += b8x8::consts::dim_elements_macroblock;
    }

    U3_FAST_MOVE_CPTR (cur_buf, (b8x8::consts::dim_elements_macroblock - 1) * params.psrc_->stride_ + lsleak_width);
  }

  U3_ASSERT ((*params.prets_)[info.indx_thread_].check ());
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::forward
