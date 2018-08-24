//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       str2eoffbuff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Фунция конвертации строки в тип-индекс назначения буфера.
*/

namespace utils { namespace dbuffs { namespace video { namespace consts { namespace offs {
/**
  \brief      Вспомогательная свободная функция для конвертации строки в тип-индекс буфера.
  \param[in]  _str  строка.
  \return     тип буфера.
  */
inline off_buff_type
str2eoffbuff (const std::string& _str)
{
  const static std::pair<std::string, off_buff_type> _vals[] = {
    std::pair<std::string, off_buff_type> ("", invalid),
    std::pair<std::string, off_buff_type> ("-", invalid),
    std::pair<std::string, off_buff_type> ("?", invalid),
    std::pair<std::string, off_buff_type> ("??", invalid),
    std::pair<std::string, off_buff_type> ("???", invalid),
    std::pair<std::string, off_buff_type> (invalid, invalid)
  };

  for (const auto& _val : _vals)
    {
      if (_val.first == _str)
        {
          return _val.second;
        }
    }
  return _str;
}

}}}}}      // namespace utils::dbuffs::video::consts::offs
