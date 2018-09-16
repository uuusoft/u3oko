//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       functs_for_optim.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_appl
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
// old shit
#if 0

UUU_SET_TARGET_CPU ( avx2 )
void rgb24_to_l_avx2_test (
std::size_t       _size,
short*          _l,
const unsigned int*   _rgb24,
const std::size_t   _width,
const std::size_t   _height,
std::size_t       _stride_src,
std::size_t       _stride_dst )
{
  const unsigned int    _ppc = _size;
  //short*          _l        = _info.dsts_[0].buff();                        
  //const unsigned int*   _rgb24      = UUU_MEM_CAST<const unsigned int*>( _info.srcs_[0].ubuff() );      
  //const std::size_t   _width      = _info.srcs_[0].width_;                        
  //const std::size_t   _height     = _info.srcs_[0].height_;                       
  const unsigned int    _raw_cycle = _width / _ppc;
  const unsigned int    _cycle = ( _raw_cycle * _ppc < _width) ? _raw_cycle + 1 : _raw_cycle;
  const unsigned int    _leak_rgb = _stride_src - _cycle * _ppc * sizeof (unsigned char) * 3;
  const unsigned int    _req_stride_hsl = _cycle * sizeof (unsigned short ) * _ppc;
  const unsigned int    _leak_hsl = _stride_dst - _req_stride_hsl;

  _mm256_zeroall ();

  const __m256  _const_1_to_255 = _mm256_broadcast_ss ( ::libs::optim::s16bit::consts::f_all_d1_to_255 );
  const __m256  _const_1_to_2 = _mm256_broadcast_ss ( ::libs::optim::s16bit::consts::f_all_d1_to_2 );
  const __m256  _const_255 = _mm256_broadcast_ss ( ::libs::optim::s16bit::consts::f_all_d255 );
  const __m256i _permute32 = _mm256_setr_epi32 (0, 1, 2, 0, 3, 4, 5, 3);

  const __m256i _permute_b8 = _mm256_setr_epi8 (
    UUU_ICAST_UCHAR(0x00), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80),
    UUU_ICAST_UCHAR(0x03), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80),
    UUU_ICAST_UCHAR(0x86), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80),
    UUU_ICAST_UCHAR(0x89 ), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80),
    UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80),
    UUU_ICAST_UCHAR(0x83), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80),
    UUU_ICAST_UCHAR(0x86), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80),
    UUU_ICAST_UCHAR(0x89 ), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80), UUU_ICAST_UCHAR(0x80) );

  const __m256i _permute_g8 = _permute_b8;
  const __m256i _permute_r8 = _permute_b8;

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
  {
    for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
    {
      __m256i _i256_1 = _mm256_loadu_si256 (UUU_MEM_CAST<const __m256i*> ( _rgb24 ) );  //BOG0R0 B1G1R1 B2G2R2 B3G3R3 B4G4R4 B5G5R5 B6G6R6 B7G7R7
      __m256i _ir8 = _mm256_setzero_si256 ();
      __m256i _ig8 = _mm256_setzero_si256 ();
      __m256i _ib8 = _mm256_setzero_si256 ();

      _i256_1 = _mm256_permutevar8x32_epi32 ( _i256_1, _permute32 );          //BOG0R0B1 G1R1B2G2 R2B3G3R3 B4G4R4B5 G5R5B6G6 R6B7G7R7
      _ib8 = _mm256_shuffle_epi8 ( _i256_1, _permute_b8);             //BO000000 B1000000 B2000000 B3000000 B4000000 B5000000 B6000000 B7000000 
      _ig8 = _mm256_shuffle_epi8 ( _i256_1, _permute_g8);
      _ir8 = _mm256_shuffle_epi8 ( _i256_1, _permute_r8);
      //_ib8.
      //_mm_insert
      //_mm256_castsi128_si256
#if 0
      _ib8.m256i_u32[0] = _i256_1.m256i_u8[0];
      _ib8.m256i_u32[1] = _i256_1.m256i_u8[3];
      _ib8.m256i_u32[2] = _i256_1.m256i_u8[6];
      _ib8.m256i_u32[3] = _i256_1.m256i_u8[9];
      _ib8.m256i_u32[4] = _i256_1.m256i_u8[12];
      _ib8.m256i_u32[5] = _i256_1.m256i_u8[15];
      _ib8.m256i_u32[6] = _i256_1.m256i_u8[18];
      _ib8.m256i_u32[7] = _i256_1.m256i_u8[21];

      _ig8.m256i_u32[0] = _i256_1.m256i_u8[1];
      _ig8.m256i_u32[1] = _i256_1.m256i_u8[4];
      _ig8.m256i_u32[2] = _i256_1.m256i_u8[7];
      _ig8.m256i_u32[3] = _i256_1.m256i_u8[10];
      _ig8.m256i_u32[4] = _i256_1.m256i_u8[13];
      _ig8.m256i_u32[5] = _i256_1.m256i_u8[16];
      _ig8.m256i_u32[6] = _i256_1.m256i_u8[19];
      _ig8.m256i_u32[7] = _i256_1.m256i_u8[22];

      _ir8.m256i_u32[0] = _i256_1.m256i_u8[2];
      _ir8.m256i_u32[1] = _i256_1.m256i_u8[5];
      _ir8.m256i_u32[2] = _i256_1.m256i_u8[8];
      _ir8.m256i_u32[3] = _i256_1.m256i_u8[11];
      _ir8.m256i_u32[4] = _i256_1.m256i_u8[14];
      _ir8.m256i_u32[5] = _i256_1.m256i_u8[17];
      _ir8.m256i_u32[6] = _i256_1.m256i_u8[20];
      _ir8.m256i_u32[7] = _i256_1.m256i_u8[23];
#endif
      //convert RGB double word from 8 pixel to float;
      __m256 _temp_r = _mm256_cvtepi32_ps ( _ir8);
      __m256 _temp_g = _mm256_cvtepi32_ps ( _ig8);
      __m256 _temp_b = _mm256_cvtepi32_ps ( _ib8);
#if 1
      //normalization from 0..255 to 0.0f..1.0f;
      _temp_r = _mm256_mul_ps ( _temp_r, _const_1_to_255 );
      _temp_g = _mm256_mul_ps ( _temp_g, _const_1_to_255 );
      _temp_b = _mm256_mul_ps ( _temp_b, _const_1_to_255 );
#endif
      _rgb24 += 6;
#if 1
      //float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
      __m256 _var_min = _temp_r;

      _var_min = _mm256_min_ps ( _temp_g, _var_min);
      _var_min = _mm256_min_ps ( _temp_b, _var_min);

      //float _max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
      __m256 _max = _mm256_max_ps ( _temp_g, _temp_r);
      _max = _mm256_max_ps ( _temp_b, _max );

      //_max_min = _max + var_Min;
      __m256 _max_min = _mm256_add_ps ( _var_min, _max );

      //L = ( _max + var_Min ) / 2.0f;
      __m256 _l8 = _mm256_mul_ps ( _const_1_to_2, _max_min);

      //converting from float HSL to word HSL and saved to buffers
      _l8 = _mm256_mul_ps ( _l8, _const_255 );
      _i256_1 = _mm256_cvtps_epi32 ( _l8);
      __m256i _i256_2 = _mm256_permute2f128_si256 ( _i256_1, _i256_1, 1 );
      _i256_1 = _mm256_packs_epi32 ( _i256_1, _i256_2 );
      _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> ( _l), _i256_1 );

      _l += 8;
#endif
    }

    FAST_MOVE_CPTR ( _rgb24, _leak_rgb );
    FAST_MOVE_PTR ( _l, _leak_hsl);
  }

  return;
}

#if 0
UUU_SET_TARGET_CPU ( avx2 )
void conv3x3_test (
  //std::size_t       _size,
  const short*      _sbuff,
  short*          _dbuff,
  const std::size_t   _width,
  const std::size_t   _height,
  std::size_t       _stride )
{
  std::size_t       size_core = 3;
  const std::size_t   count_ppc = 1;
  //const cores::TCore*   _mask = 0;
  short         _mul_koeff = 0;
  //TTParams<cores::TCore>  _params;

  UASSERT ( count_ppc > 0);
  UASSERT ( count_ppc <= 16);

  //_params.get_params ( _info, _mask, _mul_koeff );

  int         _tres[count_ppc];
  //TPostProcessor    _post_obj;
  //const std::size_t _width = _info.srcs_[0].width_;
  //const std::size_t _height = _info.srcs_[0].height_;
  //const short*    _sbuff = _info.srcs_[0].buff ();
  //short*        _dbuff = _info.dsts_[0].buff ();
  //const std::size_t _stride = _info.srcs_[0].stride_;
  const short*    _sstr = _sbuff;
  short*        _dstr = _dbuff;
  const std::size_t _hmsize = size_core >> 1;
  const std::size_t _move_size = _hmsize * _stride;
  const short     _fake_raw_mask[16]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
  const short*    _raw_mask = _fake_raw_mask;//_mask->raw_vals ();
  const std::size_t _fake_aligned = 0;
  const std::size_t _aligned = _fake_aligned;//_mask->aligned_;

  std::fill ( &_tres[0], &_tres[count_ppc], 0);

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
  {
    for (std::size_t _indxx = 0; _indxx < _width; _indxx += count_ppc)
    {
      const short* _csstr = _sstr + _indxx - _hmsize;

      FAST_MOVE_CPTR_BACK ( const short*, _csstr, _move_size );

      _tres[0] = 0;

      _tres[0] += _csstr[0] * _raw_mask[0 * _aligned + 0];
      _tres[0] += _csstr[1] * _raw_mask[0 * _aligned + 1];
      _tres[0] += _csstr[2] * _raw_mask[0 * _aligned + 2];
      FAST_MOVE_CPTR ( const short*, _csstr, _stride );

      _tres[0] += _csstr[0] * _raw_mask[1 * _aligned + 0];
      _tres[0] += _csstr[1] * _raw_mask[1 * _aligned + 1];
      _tres[0] += _csstr[2] * _raw_mask[1 * _aligned + 2];
      FAST_MOVE_CPTR ( const short*, _csstr, _stride );

      _tres[0] += _csstr[0] * _raw_mask[2 * _aligned + 0];
      _tres[0] += _csstr[1] * _raw_mask[2 * _aligned + 1];
      _tres[0] += _csstr[2] * _raw_mask[2 * _aligned + 2];
      FAST_MOVE_CPTR ( const short*, _csstr, _stride );

      _tres[0] = std::abs ( _tres[0] );

      _tres[0] = ( _tres[0] * _mul_koeff ) >> SHIFT_MUL_KOEFF_CONVOLUTION;

      _tres[0] = _tres[0] > 255 ? 255 : _tres[0];
      _tres[0] = _tres[0] < -255 ? -255 : _tres[0];

      _dstr[_indxx] = UUU_ICAST_SHORT( _tres[0] );
    }

    FAST_MOVE_CPTR ( const short*, _sstr, _stride );
    FAST_MOVE_PTR ( _dstr, _stride );
  }
}


#elif 0


const int   pxs_per_cycle = 5;

#define LOAD_STR(_data, _permute16, _permute8)                                                \
  _data = _mm256_lddqu_si256 (UUU_MEM_CAST<const __m256i*> (_csstr)); /*0123 456x xxxx xxxx*/ \
  _data = _mm256_permutevar8x32_epi32 (_data, _permute16);            /*0123 2323 2345 456x*/ \
  _data = _mm256_shuffle_epi8 (_data, _permute8);                     /*0121 2323 4345 456x*/ \
  FAST_MOVE_CPTR (_csstr, _stride);


#define PROCESS_STR(_str_mask)                     \
  _himul = _mm256_mulhi_epi16 (_data, _str_mask);  \
  _lomul = _mm256_mullo_epi16 (_data, _str_mask);  \
  _mul1  = _mm256_unpacklo_epi16 (_lomul, _himul); \
  _mul2  = _mm256_unpackhi_epi16 (_lomul, _himul); \
  _akk1  = _mm256_add_epi32 (_mul1, _akk1);        \
  _akk2  = _mm256_add_epi32 (_mul2, _akk2);


UUU_SET_TARGET_CPU ( avx2 )
void clone_core_str ( __m256i& _str)
{
  const __m256i _permute = _mm256_set_epi8 (
    0, 0, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 5, 4,
    3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0);

  _str = _mm256_permute4x64_epi64 ( _str, BOOST_BINARY (00000000) );  //0, 1, 2, x, 0, 1, 2, x,   0, 1, 2, x,   0, 1, 2, x
  _str = _mm256_shuffle_epi8 ( _str, _permute );            //0, 1, 2, 0, 1, 2, 0, 1,   2, 0, 1, 2,   0, 1, 2, x
}


UUU_SET_TARGET_CPU ( avx2 )
void conv3x3_test (
  const short*      _sbuff,
  short*          _dbuff,
  const std::size_t   _width,
  const std::size_t   _height,
  std::size_t       _stride )
{
  std::size_t       size_core = 3;
  const std::size_t   count_ppc = 5;
  //const cores::TCore*   _mask = 0;
  short         _mul_koeff = 20;
  //TTParams<cores::TCore>  _params;

  UASSERT ( count_ppc > 0);
  UASSERT ( count_ppc <= 16);

  //_params.get_params ( _info, _mask, _mul_koeff );

  __m256i   str1_core_;
  __m256i   str2_core_;
  __m256i   str3_core_;
  __m256i   permute16_;
  __m256i   permute8_;

  permute16_ = _mm256_set_epi32 ( 3, 2, 2, 1, 1, 1, 1, 0);

  permute8_ = _mm256_set_epi8 (
    15, 14, 13, 12, 11, 10, 9, 8,
    7, 6, 5, 4, 3, 2, 5, 4,
    15, 14, 13, 12, 11, 10, 9, 4,
    3, 2, 5, 4, 3, 2, 1, 0);

  const short _fake_mask[ 16 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

  str1_core_ = _mm256_lddqu_si256 (UUU_MEM_CAST<const __m256i*> ( _fake_mask) );//&(**_pmask).get (0, 0) ) );
  str2_core_ = _mm256_lddqu_si256 (UUU_MEM_CAST<const __m256i*> ( _fake_mask) );//&(**_pmask).get (0, 1 ) ) );
  str3_core_ = _mm256_lddqu_si256 (UUU_MEM_CAST<const __m256i*> ( _fake_mask) );//&(**_pmask).get (0, 2 ) ) );

  clone_core_str (str1_core_ );
  clone_core_str (str2_core_ );
  clone_core_str (str3_core_ );


  UUU_DEFAULT_ALIGNED int   _tres[count_ppc + 16];
  //TPostProcessor    _post_obj;
  //const std::size_t _width = _info.srcs_[0].width_;
  //const std::size_t _height = _info.srcs_[0].height_;
  //const short*    _sbuff = _info.srcs_[0].buff ();
  //short*        _dbuff = _info.dsts_[0].buff ();
  //const std::size_t _stride = _info.srcs_[0].stride_;
  const short*    _sstr = _sbuff;
  short*        _dstr = _dbuff;
  const std::size_t _hmsize = size_core >> 1;
  //const std::size_t _move_size = _hmsize * _stride;
  /*
  const short     _fake_raw_mask[16 * 3 ] = 
  {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
  };
  */

  //const short*    _raw_mask = _fake_raw_mask;//_mask->raw_vals ();
  //const std::size_t _aligned = 16;//_mask->aligned_;

  std::fill ( &_tres[0], &_tres[count_ppc], 0);

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
  {
    for (std::size_t _indxx = 0; _indxx < _width; _indxx += count_ppc)
    {
      const short* _csstr = _sstr + _indxx - _hmsize;
      __m256i   _data;
      __m256i   _himul;
      __m256i   _lomul;
      __m256i   _mul1;
      __m256i   _mul2;
      __m256i   _akk1 = _mm256_setzero_si256();
      __m256i   _akk2 = _mm256_setzero_si256();
      
      LOAD_STR( _data, permute16_, permute8_ );
      PROCESS_STR( str1_core_ );

      LOAD_STR( _data, permute16_, permute8_ );
      PROCESS_STR( str2_core_ );

      LOAD_STR( _data, permute16_, permute8_ );
      PROCESS_STR( str3_core_ );

      __m256i     _fakk   = _mm256_setzero_si256();
      const __m256i _fpermute1  = _mm256_setr_epi32( 0, 3, 4, 5, 7, 7, 7, 7 );
      const __m256i _fmask    = _mm256_setr_epi32( -1, -1, -1, -1, -1, -1, -1, 0 );
      __m256i     _ftemp;

      _ftemp  = _akk1;                        //A1A2A3B1  C1D1D2D3
      _ftemp  = _mm256_and_si256( _ftemp, _fmask );         //A1A2A3B1  C1D1D200
      _ftemp  = _mm256_permutevar8x32_epi32( _ftemp, _fpermute1 );  //A1B1C1D1  00000000
      _fakk = _mm256_add_epi32( _fakk, _ftemp );

      const __m256i _fpermute2  = _mm256_setr_epi32( 0, 7, 7, 5, 7, 7, 7, 7 );

      _akk1 = _mm256_srli_si256( _akk1, 4 );            //A2A3B100  D1D2D300
      _ftemp  = _mm256_permutevar8x32_epi32( _akk1, _fpermute2 );   //A20000D2  00000000
      _fakk = _mm256_add_epi32( _fakk, _ftemp );

      const __m256i _fpermute3  = _mm256_setr_epi32( 1, 7, 7, 6, 7, 7, 7, 7 );

      _ftemp  = _mm256_permutevar8x32_epi32( _akk1, _fpermute3 );   //A30000D3  00000000
      _fakk = _mm256_add_epi32( _fakk, _ftemp );

      const __m256i _fpermute4  = _mm256_setr_epi32( 7, 0, 2, 7, 4, 7, 7, 7 );

      _akk2 = _mm256_and_si256( _akk2, _fmask );          //B2B3C2C3  E1E2E300
      _ftemp  = _mm256_permutevar8x32_epi32( _akk2, _fpermute4 );   //00B2C200  E1000000
      _fakk = _mm256_add_epi32( _fakk, _ftemp );

      const __m256i _fpermute5  = _mm256_setr_epi32( 7, 1, 3, 7, 5, 7, 7, 7 );

      _ftemp  = _mm256_permutevar8x32_epi32( _akk2, _fpermute5 );   //00B3C300  E2000000
      _fakk = _mm256_add_epi32( _fakk, _ftemp );

      const __m256i _fpermute6  = _mm256_setr_epi32( 7, 7, 7, 7, 6, 7, 7, 7 );

      _ftemp  = _mm256_permutevar8x32_epi32( _akk2, _fpermute6 );   //00000000  E3000000
      _fakk = _mm256_add_epi32( _fakk, _ftemp );

      const __m256i _mulkoeff = _mm256_setr_epi32( _mul_koeff, _mul_koeff, _mul_koeff, _mul_koeff, _mul_koeff, _mul_koeff, _mul_koeff, _mul_koeff );

      _akk1 = _mm256_abs_epi32( _fakk);
      _akk1 = _mm256_mullo_epi32( _akk1, _mulkoeff );
      _akk1 = _mm256_srai_epi32( _akk1, SHIFT_MUL_KOEFF_CONVOLUTION );
      _akk2 = _mm256_permute2x128_si256( _akk1, _akk1, 1 );
      _akk1 = _mm256_packus_epi32( _akk1, _akk2 );

      _mm256_storeu_si256( UUU_MEM_CAST<__m256i*>( _dstr + _indxx ), _akk1 );
    }

    FAST_MOVE_CPTR ( const short*, _sstr, _stride );
    FAST_MOVE_PTR ( _dstr, _stride );
  }
}

#endif

#if 0

void debug_funct_for_optim1( const ::libs::properties::vers::links::links_type* _plinks )
{
  ::libs::helpers::statistic::ExpandedTimeStatistic _timer;
  std::list<std::string>                _times;
  const std::size_t                 _count_cycles = 10;
  const std::size_t                 _width = 1280;
  const std::size_t                 _height = 720;
  const std::size_t                 _stride_src = _width * 3;
  const std::size_t                 _stride_dst = ::libs::helpers::mem::get_align32( _width * sizeof (short ) );
  ::utils::mem_functs::IBlockMem::ptr _rgb24 = ::libs::iproperties::helpers::cast_prop_demons()->get_mem_lockfree()->alloc ( _stride_src * 2 * _height );
  ::utils::mem_functs::IBlockMem::ptr _l1 = ::libs::iproperties::helpers::cast_prop_demons()->get_mem_lockfree()->alloc ( _stride_dst * 2 * _height );
  ::utils::mem_functs::IBlockMem::ptr _l2 = ::libs::iproperties::helpers::cast_prop_demons()->get_mem_lockfree()->alloc ( _stride_dst * 2 * _height );

  _timer.begin ("debug");

  for (std::size_t _indx = 0; _indx < _count_cycles; ++_indx )
  {
#if 1
    conv3x3_test (
      _l1->get_as<short> () + _stride_dst * 3,
      _l2->get_as<short> () + _stride_dst * 3,
      _width,
      _height,
      _stride_dst );

#elif 1
    rgb24_to_l_avx2_test (
      8,
      _l1->get_as<short> (),
      _rgb24->get_as<unsigned int> (),
      _width,
      _height,
      _stride_src,
      _stride_dst );

#else
    _mm256_zeroall ();

    memset( _mem->get(), 1, _mem->size() );

    short*      _vals1    = _mem->get_as<short>();
    const __m256i _addreg1  = _mm256_setr_epi16( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 );
    const __m256i _addreg2  = _mm256_setr_epi16( -1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 );

    for( std::size_t _indxe = 0; _indxe < _count_elements; _indxe+= 4 )
    {
      __m256i _data1 = _mm256_lddqu_si256( UUU_MEM_CAST<__m256i*>( &_vals1[_indxe] ) );
      _data1 = _mm256_adds_epi16( _data1, _addreg1 );
      _data1 = _mm256_mulhi_epi16( _data1, _addreg2 );
      _mm256_storeu_si256( UUU_MEM_CAST<__m256i*>( &_vals1[_indxe] ), _data1 );
    }
#endif
  }

  _timer.end ();
  _timer.get ( _times);

  ELOGIT2LINK ( _plinks->all2log_, _times.begin ()->c_str () );
}

#endif

#endif
