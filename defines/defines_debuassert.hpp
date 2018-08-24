//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_debuassert.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
*/
/**
\brief  Вспомогательные дополнительные проверки для уточнения области ошибки.
*/
#if defined(ENABLE_DEBUG_ASSERTS)

//  Проверка утверждений для отладочного режима.
#define DEB_UASSERT(cond) UASSERT (cond)
//  Сигнализация об безусловном сбое в работе программы.
#define DEB_UASSERT_SIGNAL UASSERT_SIGNAL

#else

#define DEB_UASSERT(cond)
#define DEB_UASSERT_SIGNAL

#endif
