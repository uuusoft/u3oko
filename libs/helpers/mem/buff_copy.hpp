#pragma once
/**
\file       buff_copy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace mem {
/*
  \brief  empty brief
  */
template <
  typename TTSrcElement,
  typename TTDstElement>
void
buff_copy (
  TTSrcElement _src,
  const int    _swidth,
  const int    _sheight,
  const int    _sstride,
  TTDstElement _dst,
  const int    _dwidth,
  const int    _dheight,
  const int    _dstride)
{
  CHECK_STATE (_src, "failed, null src");
  CHECK_STATE (_dst, "failed, null dst");

  const int _cheight = std::min<int> (_sheight, _dheight);
  const int _cstride = std::min<int> (_sstride, _dstride);

  for (int _indxy = 0; _indxy < _cheight; ++_indxy)
    {
      acopy (_src, _dst, UUU_ICAST_SIZE_T (_cstride));

      FAST_MOVE_CPTR (_src, _sstride);
      FAST_MOVE_PTR (_dst, _dstride);
    }
  return;
}

}}}      // namespace libs::helpers::mem
