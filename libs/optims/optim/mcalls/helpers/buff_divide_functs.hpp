#pragma once
/**
\file       buff_divide_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief    
*/

namespace libs { namespace optim { namespace mcalls { namespace helpers {
/**
\brief  empty brief
*/
inline bool
split_height (
  const std::size_t _max_block,
  const std::size_t _align_block,
  std::size_t       _height,
  std::size_t&      _ret)
{
  UASSERT (_align_block > 0);
  UASSERT (_max_block > 0);
  UASSERT (((_height % _align_block) == 0));

  std::size_t _aligned_height = _height / _align_block;

  _ret = _max_block;

  std::size_t _min_size = std::numeric_limits<std::size_t>::max ();
  std::size_t _cur      = _max_block;

  do
    {
      const std::size_t _full_size = _aligned_height / _cur;
      const std::size_t _leak_size = _full_size + _aligned_height - _full_size * _cur;
      const std::size_t _max_size  = std::max<std::size_t> (_full_size, _leak_size);

      if (_min_size > _max_size)
        {
          _min_size = _max_size;
          _ret      = _cur;
        }
    }
  while (--_cur > 1);

  return true;
}

}}}}      // namespace libs::optim::mcalls::helpers
