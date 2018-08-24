//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file     motion_est1_sse1.cpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date     28.08.2016
\project  uuu_optim_motion
\brief    Оценка движения в кадре.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "motion_est1.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buff_helpers_functs.hpp"
#include "move_alg.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace motion { namespace est1 {
/**
  \brief  empty brief
  */
struct TAvx2CalcObj
{
  UUU_SET_TARGET_CPU (avx2)
  TAvx2CalcObj () :
    init_ (false), max_mask_ (0)
  {
    masks_[0] = _mm256_setzero_si256 ();
    masks_[1] = masks_[0];
    return;
  }


  void
  init (::libs::optim::MCallInfo& _info)
  {
    return;
  }


  UUU_SET_TARGET_CPU (avx2)
  int
  get_res (
    const short*      _src1,
    const short*      _src2,
    const short       _size_block,
    const std::size_t _stride)
  {
    int _ret = 0;

    UASSERT (_size_block <= 32);
    UASSERT (_size_block <= 16);

    update_mask (_size_block);

    __m256i _iymm0     = _mm256_setzero_si256 ();
    __m256i _iymm1     = _mm256_setzero_si256 ();
    __m256i _iymm2     = _mm256_setzero_si256 ();
    __m256i _iymm4     = masks_[1];
    __m128i _iymm0_128 = _mm_setzero_si128 ();
    __m128i _iymm2_128 = _mm_setzero_si128 ();

    for (std::size_t _indxy = 0; _indxy < UUU_ICAST_SIZE_T (_size_block); ++_indxy)
      {
        const __m256i* _isrc1 = UUU_MEM_CAST<const __m256i*> (_src1);
        const __m256i* _isrc2 = UUU_MEM_CAST<const __m256i*> (_src2);

        //Р±Р°Р·РѕРІРѕРµ СЃСЂР°РІРЅРµРЅРёРµ РїРѕ РіРѕСЂРёР·РѕРЅС‚Р°Р»Рё, РєРѕС‚РѕСЂРѕРµ РµСЃС‚СЊ РІСЃРµРіРґР°
        {
          _iymm0 = _mm256_lddqu_si256 (_isrc1);
          //_iymm0 = _mm256_and_si256( _iymm0, _iymm3);

          _iymm1 = _mm256_lddqu_si256 (_isrc2);
          //_iymm1 = _mm256_and_si256( _iymm1, _iymm3);

          _iymm0 = _mm256_subs_epi16 (_iymm0, _iymm1);
          _iymm0 = _mm256_abs_epi16 (_iymm0);
          _iymm2 = _mm256_add_epi16 (_iymm2, _iymm0);
        }
        //РґРѕРїРѕР»РЅРёС‚РµР»СЊРЅРѕРµ СЃСЂР°РІРЅРµРЅРёРµ РїРѕ РіРѕСЂРёР·РѕРЅС‚Р°Р»Рё, РµСЃР»Рё СЂР°Р·РјРµСЂ Р±Р»РѕРєР° Р±РѕР»СЊС€Рµ 16.
        if (2 == max_mask_)
          {
            _iymm0 = _mm256_lddqu_si256 (_isrc1 + 1);
            _iymm0 = _mm256_and_si256 (_iymm0, _iymm4);

            _iymm1 = _mm256_lddqu_si256 (_isrc2 + 1);
            _iymm1 = _mm256_and_si256 (_iymm1, _iymm4);

            _iymm0 = _mm256_subs_epi16 (_iymm0, _iymm1);
            _iymm0 = _mm256_abs_epi16 (_iymm0);
            _iymm2 = _mm256_add_epi16 (_iymm2, _iymm0);
          }

        FAST_MOVE_CPTR (_src1, _stride);
        FAST_MOVE_CPTR (_src2, _stride);
      }


    _iymm1     = _mm256_permute2f128_si256 (_iymm2, _iymm2, 1);
    _iymm0_128 = _mm256_castsi256_si128 (_iymm1);
    _iymm2_128 = _mm256_castsi256_si128 (_iymm2);
    _iymm0     = _mm256_cvtepi16_epi32 (_iymm0_128);
    _iymm1     = _mm256_cvtepi16_epi32 (_iymm2_128);

    _iymm0 = _mm256_hadd_epi32 (_iymm0, _iymm1);      // 4
    _iymm0 = _mm256_hadd_epi32 (_iymm0, _iymm0);      // 2
    _iymm0 = _mm256_hadd_epi32 (_iymm0, _iymm0);      // 1


#if defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)
    _ret += _mm256_extract_epi32 (_iymm0, 0);
    _ret += _mm256_extract_epi32 (_iymm0, 4);
#else
    _ret += _iymm0.m256i_i32[0];
    _ret += _iymm0.m256i_i32[4];
#endif

    return _ret;
  }

  protected:
  UUU_SET_TARGET_CPU (avx2)
  void
  update_mask (const short _size_block)
  {
    if (init_)
      {
        return;
      }

    init_     = true;
    max_mask_ = 0;

    short _calc_size_block = _size_block;

    for (std::size_t _fill_mask = 0; _calc_size_block > 0 && _fill_mask < COUNT_OF (masks_); ++_fill_mask)
      {
        masks_[_fill_mask] = _mm256_setzero_si256 ();

        for (short _findx = 0; _findx < _calc_size_block; ++_findx)
          {
#if defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)
            UASSERT_SIGNAL_OPTIM;
            //masks_[ _fill_mask ] = _mm256_insert_epi16( masks_[ _fill_mask ], 0xFFFF, _findx );
#else
            masks_[_fill_mask].m256i_u16[_findx] = 0xFFFF;
#endif
          }

        _calc_size_block -= 16;
        ++max_mask_;
      }

    return;
  }


  private:
  bool        init_;          //<  ???
  __m256i     masks_[2];      //<  Р Р°Р·РјРµСЂ Р±Р»РѕРєР° РЅРµ РјРѕР¶РµС‚ Р±С‹С‚СЊ Р±РѕР»СЊС€Рµ 32 short, СЌС‚Рѕ 64 byte, РёР»Рё 512 bit, РёР»Рё 2 _m256
  std::size_t max_mask_;      //<  ???
};


UUU_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::MCallInfo& _info)
{
  _mm256_zeroupper ();
  move_alg<TAvx2CalcObj> (_info);
  _mm256_zeroupper ();
  return;
}

}}}}}      // namespace libs::optim::s16bit::motion::est1

#endif
