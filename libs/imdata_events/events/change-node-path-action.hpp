//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       change-node-path-action.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/

namespace libs { namespace imdata_events { namespace events {
/**
\brief  Перечисление различных действий, которые можно произвести над узлом графа обработки данных.
*/
enum struct ChangeNodePathAction
{
  get = 0,      //< Получить список событий-свойств у узла обработки данных.
  set = 1       //< Установить (заместить) список событий-свойств у узла обработки данных.
};

}}}      // namespace libs::imdata_events::events
