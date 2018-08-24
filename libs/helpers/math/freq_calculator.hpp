#pragma once
/**
\file       freq_calculator.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace math {
/**
  \brief  empty brief
  */
template <
  typename TTSrcElement>
fill_freq_by_symb (
  const TTSrcElement* _src,
  const std::size_t   _count_src,
  unsigned int*       _dst,
  const std::size_t   _max_size_elements_dst)
{
  UASSERT (_src);
  UASSERT (_count_src);
  UASSERT (_dst);
  UASSERT (_max_size_elements_dst);
  UASSERT( _max_size_elements_dst >= std::pow( 2, sizeof(TTSrcElement ) * 8 );
  
  std::fill<unsigned int>( _dst, _dst + _max_size_elements_dst, 0 );
  
  for( std::size_t _indx = 0; _indx < _count_src; ++_indx )
  {
    const TTSrcElement _symb = _src[_indx];
    ++_dst[_symb];
    UASSERT (_dst[_symb] < _dst[_symb] + 1);
  }
  return;
}

}}}      // namespace libs::helpers::math
