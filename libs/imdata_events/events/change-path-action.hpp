//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       change-path-action.hpp
\date       14.09.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/

namespace libs { namespace imdata_events { namespace events {
/**
\brief  ѕеречисление различных действий, которые можно произвести над списком графов обработки данных.
*/
enum struct ChangePathAction
{
  get    = 0,      //< ѕолучить список активных графов по обработке данных.
  add    = 1,      //< ƒобавить указанный список к активным.
  remove = 2       //< ”далить указанный список из активных.
};

}}}      // namespace libs::imdata_events::events
