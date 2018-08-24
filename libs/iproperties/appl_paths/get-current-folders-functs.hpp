//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       get-current-folders-functs.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/

namespace libs { namespace iproperties { namespace appl_paths {
/**
  \brief  Функция возвращает текущую директорию системы.
  \return путь текущей директории.
  */
std::string get_current_folder ();
/**
  \brief  Функция возвращает текущую директорию системы с библиотеками расширения.
  \return путь текущей директории c dll.
  */
std::string get_current_lib_folder ();

}}}      // namespace libs::iproperties::appl_paths
