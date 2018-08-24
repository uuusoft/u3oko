#pragma once
/**
\file       invert_rows.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление вспомогательных функций для манипулирования блоками буфера.
*/

namespace utils { namespace dbuffs { namespace video { namespace helpers {

inline void
invert_rows (IVideoBuff::raw_ptr _buff)
{
  CHECK_STATE (_buff, "failed, empty buff for fill");

  if (!_buff->get_buff () || !(*_buff)[TypeMemVar::size_buffer] || _buff->get_flag (TypeFlagsBuff::empty))
    {
      return;
    }

  const auto _height = _buff->get_dim_var (TypeDimVar::height);
  const auto _width  = _buff->get_dim_var (TypeDimVar::width);

  for (int _indxy1 = 0, _indxy2 = _height - 1; _indxy1 < _indxy2; ++_indxy1, --_indxy2)
    {
      auto _line1 = get_line_data_as<short*> (_buff, _indxy1);
      auto _line2 = get_line_data_as<short*> (_buff, _indxy2);

      for (int _indxx = 0; _indxx < _width; ++_indxx)
        {
          std::swap (_line1[_indxx], _line2[_indxx]);
        }
    }
  return;
}

}}}}      // namespace utils::dbuffs::video::helpers
