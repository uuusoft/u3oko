#pragma once
/**
\file       move_mem_ptr_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace mem {

template <
  typename T>
T
move_ptr (T _ptr, std::size_t _off)
{
  unsigned char* _ret = UUU_MEM_CAST<unsigned char*> (_ptr);
  _ret += _off;
  return UUU_MEM_CAST<T> (_ret);
}


template <
  typename T>
T
move_cptr (T _ptr, std::size_t _off)
{
  const unsigned char* _ret = UUU_MEM_CAST<const unsigned char*> (_ptr);
  _ret += _off;
  return UUU_MEM_CAST<T> (_ret);
}


template <
  typename T>
T
move_ptr_back (T _ptr, std::size_t _off)
{
  unsigned char* _ret = UUU_MEM_CAST<unsigned char*> (_ptr);
  _ret -= _off;
  return UUU_MEM_CAST<T> (_ret);
}


template <
  typename T>
T
move_cptr_back (T _ptr, std::size_t _off)
{
  const unsigned char* _ret = UUU_MEM_CAST<const unsigned char*> (_ptr);
  _ret -= _off;
  return UUU_MEM_CAST<T> (_ret);
}

}}}      // namespace libs::helpers::mem


#if !defined(FAST_MOVE_PTR)
#define FAST_MOVE_PTR(_ptr, _off) _ptr = UUU_MEM_CAST<decltype (_ptr)> (UUU_MEM_CAST<unsigned char*> (_ptr) + UUU_ICAST_SIZE_T (_off));
#endif

#if !defined(FAST_MOVE_CPTR)
#define FAST_MOVE_CPTR(_ptr, _off) _ptr = UUU_MEM_CAST<decltype (_ptr)> (UUU_MEM_CAST<const unsigned char*> (_ptr) + UUU_ICAST_SIZE_T (_off));
#endif

#if !defined(FAST_MOVE_PTR_BACK)
#define FAST_MOVE_PTR_BACK(_ptr, _off) _ptr = UUU_MEM_CAST<decltype (_ptr)> (UUU_MEM_CAST<unsigned char*> (_ptr) - UUU_ICAST_SIZE_T (_off));
#endif

#if !defined(FAST_MOVE_CPTR_BACK)
#define FAST_MOVE_CPTR_BACK(_ptr, _off) _ptr = UUU_MEM_CAST<decltype (_ptr)> (UUU_MEM_CAST<const unsigned char*> (_ptr) - UUU_ICAST_SIZE_T (_off));
#endif
