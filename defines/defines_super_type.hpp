//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_super_type.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Объявление вспомогательного макроса для декларирования типа на суперкласс внутри производного.
*/
#ifndef UUU_THIS_TYPE_HAS_SUPER_CLASS
//  Вспомогательный макрос для декларирования типа на суперкласс.
#if defined(UUU_COMPILER_GNUC)
#define UUU_THIS_TYPE_HAS_SUPER_CLASS(super_type) using super = super_type;
#else
#define UUU_THIS_TYPE_HAS_SUPER_CLASS(super_type) using super = super_type;
#endif

#endif
