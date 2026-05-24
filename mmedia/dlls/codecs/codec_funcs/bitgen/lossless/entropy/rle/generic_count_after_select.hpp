#pragma once
/**
\file       generic_count_after_select.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_codec_funcs
\brief      Объявление обобщенной реализации RLE (метод подсчет после выбора ключа)
*/

namespace dlls::codecs::bitgen::lossless::entropy::rle
{
template< typename TElement >
class CGenericObj
{
  public:
  //  ext types
  using value_type = TElement;

  CGenericObj () :
    key_symbol_ (0)
  {
  }

  ~CGenericObj ()
  {
  }

  void
  forward (
    const void*    src,
    std::uint32_t  count_byte_src,
    void*          dst,
    std::uint32_t& count_byte_dst)
  {
    U3_ASSERT (0 == count_byte_dst);

    const value_type* usrc    = U3_CAST_CODECS< const value_type* > (src);
    value_type*       udst    = U3_CAST_CODECS< value_type* > (dst);
    value_type        counter = 0;

    U3_ASSERT (count_byte_src / sizeof (value_type) * sizeof (value_type) == count_byte_src);

    count_byte_src = count_byte_src / sizeof (value_type);

    for (std::uint32_t indx = 0; indx < count_byte_src; ++indx)
    {
      if (key_symbol_ == usrc[indx])
      {
        if (std::numeric_limits< value_type >::max () == counter)
        {
          udst[count_byte_dst++] = counter;
          counter                = 0;
        }

        if (0 == counter)
        {
          udst[count_byte_dst++] = key_symbol_;
        }

        ++counter;
      }
      else
      {
        if (counter)
        {
          udst[count_byte_dst++] = counter;
          counter                = 0;
        }

        udst[count_byte_dst++] = usrc[indx];
      }
    }

    if (counter)
    {
      udst[count_byte_dst++] = counter;
      counter                = 0;
    }

    count_byte_dst = count_byte_dst * sizeof (value_type);
  }


  void
  backward (
    const void*    src,
    std::uint32_t  count_byte_src,
    void*          dst,
    std::uint32_t& count_byte_dst)
  {
    const value_type* usrc = U3_CAST_CODECS< const value_type* > (src);
    value_type*       udst = U3_CAST_CODECS< value_type* > (dst);

    U3_ASSERT (count_byte_src / sizeof (value_type) * sizeof (value_type) == count_byte_src);

    count_byte_src = count_byte_src / sizeof (value_type);

    for (std::uint32_t indx = 0; indx < count_byte_src; ++indx)
    {
      if (key_symbol_ == usrc[indx])
      {
        const value_type counter = usrc[indx + 1];
        U3_ASSERT (counter);

        std::fill (
          udst + count_byte_dst,
          udst + count_byte_dst + counter,
          key_symbol_);

        count_byte_dst += counter;
        ++indx;
      }
      else
      {
        udst[count_byte_dst++] = usrc[indx];
      }
    }

    count_byte_dst = count_byte_dst * sizeof (value_type);
  }

  private:
  const value_type key_symbol_;   //<
};
}   // namespace dlls::codecs::bitgen::lossless::entropy::rle
