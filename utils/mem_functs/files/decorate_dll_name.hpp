//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       decorate_dll_name.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      empty brief
*/

namespace utils { namespace mem_functs { namespace files {
/**
\brief      Функция для корректировки имени файла загружаемого кода в зависимости от типа ОС.
            Требуется, т.к. имя задается в конфигурационных файлах (xml,etc) без учета ОС.
\param[in]  _dll  базовое имя библиотеки.
\return     имя библиотеки, совместимое с ОС.
*/
inline std::string
decorate_dll_name (const std::string& _dll)
{
#if defined(UUU_OS_ANDROID) || defined(UUU_OS_GNU_LINUX) || defined(UUU_OS_RASPBERRY)
  const std::string _prefix = "lib";
  const std::string _suffix = ".so";
#elif defined(UUU_OS_WIN32_DESKTOP)
  const std::string _prefix = "";
  const std::string _suffix = ".dll";
#else
#error select OS
#endif

  const bool        _prefix_exist = (0 == _dll.find (_prefix) ? true : false);
  const bool        _suffix_exist = (_dll.length () - _suffix.length () == _dll.find (_suffix) ? true : false);
  const std::string _res          = (_prefix_exist ? "" : _prefix) + _dll + (_suffix_exist ? "" : _suffix);
  return _res;
}

}}}      // namespace utils::mem_functs::files
