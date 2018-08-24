//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       register_events_in_archives.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      ќбъ€вление функции дл€ гарантированного присутстви€ всех событий и их кода архивного сохранени€/восстановлени€ в бинарных файлах системы.
*/

namespace libs { namespace ievents {
/// ‘ункци€, обеспечивает сохранность событий в бинарных файлах, даже если событи€ не используютс€ в них.
void register_events_in_archives ();

}}      // namespace libs::ievents
