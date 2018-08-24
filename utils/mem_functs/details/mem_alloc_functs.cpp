//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mem_functs.cpp
\brief      функции работы с памятью
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      Файл реализации низкоуровных функций для работы с памятью.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"

#if 0
#if defined(UUU_COMPILER_MSC)
#define UUU_ALIGNED_ALLOC _aligned_malloc
#define UUU_ALIGNED_REALLOC _aligned_realloc
#define UUU_ALIGNED_FREE _aligned_free
#else
#define UUU_ALIGNED_ALLOC aligned_alloc
#define UUU_ALIGNED_REALLOC realloc
#define UUU_ALIGNED_FREE free
#endif
#endif

namespace utils { namespace mem_functs { namespace details { namespace consts {

const unsigned int count_add_blocks = 3;       //< Расширение памяти на утроенный размер указателя платформы, чтобы гарантировать увеличение на размер указателя (реальный размер) + 1 байт на смещение настоящего указателя.
const unsigned int size_align       = 64;      //< требуемое выравнивание, должно быть больше или равно размеру указателя платформы.

}}}}      // namespace utils::mem_functs::details::consts

namespace utils { namespace mem_functs { namespace details {

void
afree (void** _pptr)
{
  UASSERT (_pptr);
  if (nullptr == *_pptr)
    {
      return;
    }

  const std::size_t _int_ptr = UUU_MEM_CAST<std::size_t> (*_pptr);
  const std::size_t _offset  = *UUU_MEM_CAST<unsigned char*> (_int_ptr - 1);

  if ((0 == _offset) || (_offset > consts::count_add_blocks * consts::size_align))
    {
      XULOG_ERROR ("failed block memory for free");
      UASSERT_SIGNAL ("failed");
      free (*_pptr);
    }
  else
    {
      UASSERT (_int_ptr > _offset);
      void* _real_ptr = UUU_MEM_CAST<void*> (_int_ptr - _offset);
      free (_real_ptr);
    }

  *_pptr = nullptr;
  return;
}


void
aalloc (void** _pptr, const std::size_t _size)
{
  UASSERT (_pptr);
  UASSERT (nullptr == *_pptr);
  UASSERT (_size > 0);

  if (0 == _size)
    {
      return;
    }

  const std::size_t _real_size   = _size + consts::count_add_blocks * consts::size_align;
  unsigned char     _offset      = 0;
  void*             _raw_ptr     = malloc (_real_size);
  const std::size_t _int_raw_ptr = UUU_MEM_CAST<std::size_t> (_raw_ptr);

  if (nullptr == _raw_ptr)
    {
      UASSERT_SIGNAL ("failed");
      *_pptr = nullptr;
      return;
    }

  *_pptr  = UUU_MEM_CAST<void*> ((_int_raw_ptr + 2 * consts::size_align) & ::libs::helpers::mem::consts::align_ptr64);
  _offset = UUU_ICAST_UCHAR (UUU_MEM_CAST<std::size_t> (*_pptr) - _int_raw_ptr);

  if (_offset < 1)
    {
      UASSERT_SIGNAL ("failed");
      free (_raw_ptr);
      _raw_ptr = nullptr;
      *_pptr   = nullptr;
    }
  else
    {
      *UUU_MEM_CAST<unsigned char*> ((UUU_MEM_CAST<std::size_t> (*_pptr)) - 1) = _offset;
      *UUU_MEM_CAST<std::size_t*> (_raw_ptr)                                   = _size;
    }
  return;
}


void
arealloc (void** _pptr, const std::size_t _size)
{
  UASSERT (_pptr);
  UASSERT (_size > 0);

  if (nullptr == *_pptr)
    {
      aalloc (_pptr, _size);
      return;
    }

  if (_size <= 0)
    {
      afree (_pptr);
      return;
    }

  void*       _new_ptr   = nullptr;
  std::size_t _size_copy = 0;

  aalloc (&_new_ptr, _size);

  if (!_new_ptr)
    {
      UASSERT_SIGNAL ("failed");
      afree (_pptr);
      return;
    }

  const std::size_t _int_ptr  = UUU_MEM_CAST<std::size_t> (*_pptr);
  unsigned char     _offset   = *UUU_MEM_CAST<unsigned char*> (_int_ptr - 1);
  void*             _real_ptr = UUU_MEM_CAST<void*> (_int_ptr - _offset);
  const std::size_t _old_size = *UUU_MEM_CAST<std::size_t*> (_real_ptr);

  _size_copy = _old_size - _offset;
  _size_copy = _size_copy > _size ? _size : _size_copy;

  memcpy (_new_ptr, *_pptr, _size_copy);

  afree (_pptr);
  *_pptr = _new_ptr;
  return;
}

}}}      // namespace utils::mem_functs::details
