#pragma once
/**
\file       buff-filling-functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление вспомогательных функций для манипулирования блоками буфера.
*/

namespace utils { namespace dbuffs { namespace video { namespace helpers {
/**
\brief  ???
*/
inline void
fill (IVideoBuff::raw_ptr _buff, unsigned char _val)
{
  CHECK_STATE (_buff, "failed, empty buff for fill");
  if (!_buff->get_buff () || !(*_buff)[TypeMemVar::size_buffer])
    {
      return;
    }

  memset (_buff->get_buff (), _val, (*_buff)[TypeMemVar::size_buffer]);
  return;
}
/**
\brief  ???
*/
template <typename TPx>
void
fill (IVideoBuff::raw_ptr _buff, const std::function<void(int indxx, int indxy, TPx& val)>& funct)
{
  CHECK_STATE (_buff, "failed, empty buff for fill");
  if (!_buff->get_buff () || 0 == (*_buff)[TypeMemVar::size_buffer] || _buff->get_flag (TypeFlagsBuff::empty))
    {
      return;
    }

  const auto _height = _buff->get_dim_var (TypeDimVar::height);
  const auto _width  = _buff->get_dim_var (TypeDimVar::width);

  for (int _indxy = 0; _indxy < _height; ++_indxy)
    {
      auto _line = get_line_data_as<TPx*> (_buff, _indxy);
      for (int _indxx = 0; _indxx < _width; ++_indxx)
        {
          funct (_indxx, _indxy, _line[_indxx]);
        }
    }
  return;
}
/**
\brief  ???
*/
template <typename TPx>
void
fill_buffer (IVideoBuff::raw_ptr _buff, const std::function<void(long long indx, TPx& val)>& funct)
{
  CHECK_STATE (_buff, "failed, empty buff for fill");
  const auto _size    = (*_buff)[TypeMemVar::size_data];
  auto       _begbuff = get_buff_as<TPx*> (_buff);

  if (!_begbuff || 0 == _size || _buff->get_flag (TypeFlagsBuff::null))
    {
      return;
    }

  for (long long _indx = 0; _indx < _size; ++_indx)
    {
      funct (_indx, _begbuff[_indx]);
    }
  return;
}
/**
\brief  ???
*/
inline void
raw_copy (
  const unsigned char* _rbuff,
  int                  _size,
  IVideoBuff::raw_ptr  _buff,
  int                  _off_dest = 0)
{
  CHECK_STATE (_buff, "failed, empty buff for raw copy");
  CHECK_STATE (_rbuff, "failed, empty source for raw copy");
  CHECK_STATE (_size, "failed, null for raw copy");
  CHECK_STATE ((*_buff)[TypeMemVar::size_buffer] >= _size + _off_dest, "failed, failed size too small");

  _buff->set_mem_var (TypeMemVar::size_data, _size);
  _buff->set_mem_var (TypeMemVar::offset_data, 0);

  smem::acopy (_rbuff, _buff->get_buff () + _off_dest, _size);
  return;
}

}}}}      // namespace utils::dbuffs::video::helpers
