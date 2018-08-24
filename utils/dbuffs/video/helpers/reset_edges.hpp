//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       reset_edges.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление вспомогательных функций сброса данных в видео буфере.
*/

namespace utils { namespace dbuffs { namespace video { namespace helpers {
/**
  \brief      Вспомогательная функция сброса-отчистки "краев" изображения в 0.
  \param[in]  _buff буфер, края которого сбрасываются.
  */
inline void
reset_edges (IVideoBuff::raw_ptr _buff)
{
  XULOG_TRACE ("reset_edges: beg");
  CHECK_STATE (_buff, "failed, empty buff for reset edges");

  if (_buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      smem::set_buff<unsigned char> (_buff->get_buff (), 0, (*_buff)[TypeMemVar::size_buffer]);
      XULOG_TRACE ("reset_edges: empty buff, skip");
      return;
    }

  const auto _buff_format = _buff->get_format ();

  if (!::libs::helpers::uids::helpers::is_raw_format (_buff_format))
    {
      XULOG_WARNING ("try reset compressed format");
      return;
    }

  const auto _off_leak = (*_buff)[TypeMemVar::offset_data] + (*_buff)[TypeMemVar::size_data];

  CHECK_STATE ((*_buff)[utils::dbuffs::TypeMemVar::size_buffer] >= _off_leak, "failed, off leak negative");

  //  заполняем начало.
  smem::set_buff<unsigned char> (_buff->get_buff (), 0, (*_buff)[TypeMemVar::offset_data]);
  //  заполняем конец.
  smem::set_buff<unsigned char> (_buff->get_buff () + _off_leak, 0, (*_buff)[TypeMemVar::size_buffer] - _off_leak);

  const auto _height     = _buff->get_dim_var (TypeDimVar::height);
  const auto _data_width = _buff->get_dim_var (TypeDimVar::width) * ::libs::helpers::uids::helpers::get_count_bytes_from_format (_buff_format);
  const auto _leak_width = _buff->get_dim_var (TypeDimVar::stride) - _data_width;
  //  заполняем каждый остаток строки.
  for (std::remove_cv<decltype (_height)>::type _indxy = 0; _indxy < _height; ++_indxy)
    {
      unsigned char* _str_data = get_line_data_as<unsigned char*> (_buff, _indxy) + _data_width;
      smem::set_buff<unsigned char> (_str_data, 0, _leak_width);
    }
  XULOG_TRACE ("reset_edges: end");
  return;
}

}}}}      // namespace utils::dbuffs::video::helpers
