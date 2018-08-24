#pragma once
/**
\file       aligned_mem_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
namespace libs { namespace helpers { namespace mem { namespace consts {

const std::size_t align_ptr8  = ~UUU_ICAST_SIZE_T (0x7);
const std::size_t align_ptr16 = ~UUU_ICAST_SIZE_T (0xF);
const std::size_t align_ptr32 = ~UUU_ICAST_SIZE_T (0x1F);
const std::size_t align_ptr64 = ~UUU_ICAST_SIZE_T (0x3F);

}}}}      // namespace libs::helpers::mem::consts

namespace libs { namespace helpers { namespace mem {

template <
  typename TTVal>
bool
check_align (const TTVal& _val, const TTVal& _align)
{
  volatile TTVal _aval = (_val / _align) * _align;

  return _aval == _val ? true : false;
}


template <
  typename TTVal>
bool
check_align8 (TTVal _val)
{
  if (UUU_ICAST_SIZE_T (_val) & 0x07)
    {
      return false;
    }

  return true;
}


inline bool
check_align8_ptr (const void* _buff)
{
  if (UUU_ALIGNED_MEM_CAST<const std::size_t> (_buff) & 0x07)
    {
      return false;
    }

  return true;
}


template <
  typename TVal>
void
align8 (TVal& _val, bool expand = true)
{
  UASSERT (sizeof (TVal) <= sizeof (std::size_t));

  if (check_align8 (_val))
    {
      return;
    }

  _val = static_cast<TVal> ((UUU_ICAST_SIZE_T (_val) + (expand ? 7 : 0)) & consts::align_ptr8);
  UASSERT (check_align8 (_val));
  return;
}


template <
  typename TTVal>
TTVal
get_align8 (const TTVal& _val, bool expand = true)
{
  TTVal _ret = _val;
  align8<TTVal> (_ret, expand);
  return _ret;
}


template <
  typename TTVal>
bool
check_align16 (TTVal _val)
{
  if (UUU_ICAST_SIZE_T (_val) & 0x0F)
    {
      return false;
    }
  return true;
}


inline bool
check_align16_ptr (const void* _buff)
{
  if (UUU_ALIGNED_MEM_CAST<const std::size_t> (_buff) & 0x0F)
    {
      return false;
    }
  return true;
}


template <
  typename TTVal>
void
align16 (TTVal& _val, bool expand = true)
{
  UASSERT (sizeof (TTVal) <= sizeof (std::size_t));

  if (check_align16 (_val))
    {
      return;
    }

  _val = static_cast<TTVal> ((UUU_ICAST_SIZE_T (_val) + (expand ? 15 : 0)) & consts::align_ptr16);
  UASSERT (check_align16 (_val));
  return;
}


template <
  typename TTVal>
TTVal
get_align16 (const TTVal& _val, bool expand = true)
{
  TTVal _ret = _val;
  align16<TTVal> (_ret, expand);
  return _ret;
}


template <
  typename TTVal>
bool
check_align32 (TTVal _val)
{
  if (UUU_ICAST_SIZE_T (_val) & 0x1F)
    {
      return false;
    }
  return true;
}


inline bool
check_align32_ptr (const void* _buff)
{
  if (UUU_ALIGNED_MEM_CAST<const std::size_t> (_buff) & 0x1F)
    {
      return false;
    }
  return true;
}


template <
  typename TTVal>
void
align32 (TTVal& _val, bool expand = true)
{
  UASSERT (sizeof (TTVal) <= sizeof (std::size_t));

  if (check_align32 (_val))
    {
      return;
    }

  _val = static_cast<TTVal> ((UUU_ICAST_SIZE_T (_val) + (expand ? 31 : 0)) & consts::align_ptr32);
  UASSERT (check_align32 (_val));
  return;
}


template <
  typename TTVal>
TTVal
get_align32 (const TTVal& _val, bool expand = true)
{
  TTVal _ret = _val;
  align32<TTVal> (_ret, expand);
  return _ret;
}


template <
  typename TTVal>
bool
check_align64 (TTVal _val)
{
  if (UUU_ICAST_SIZE_T (_val) & 0x3F)
    {
      return false;
    }
  return true;
}


inline bool
check_align64_ptr (const void* _buff)
{
  if (UUU_ALIGNED_MEM_CAST<const std::size_t> (_buff) & 0x3F)
    {
      return false;
    }
  return true;
}


template <
  typename TTVal>
void
align64 (TTVal& _val, bool expand = true)
{
  UASSERT (sizeof (TTVal) <= sizeof (std::size_t));

  if (check_align64 (_val))
    {
      return;
    }

  _val = static_cast<TTVal> ((UUU_ICAST_SIZE_T (_val) + (expand ? 63 : 0)) & consts::align_ptr64);
  UASSERT (check_align64 (_val));
  return;
}


template <
  typename TTVal>
TTVal
get_align64 (const TTVal& _val, bool expand = true)
{
  TTVal _ret = _val;
  align64<TTVal> (_ret, expand);
  return _ret;
}

}}}      // namespace libs::helpers::mem
