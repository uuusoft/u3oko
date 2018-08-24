//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes_int.hpp
\date       11.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Внутренний интерфейс включения данного модуля.
*/
#include "sys/isys-info.hpp"

#include "sys/cpu/x86/x86cpu_id.hpp"
#include "sys/cpu/mips/mipscpu_id.hpp"
#include "sys/cpu/arm/armcpu_id.hpp"

#include "sys/os/win32/sys-info-impl.hpp"
#include "sys/os/android/sys-info-impl.hpp"
#include "sys/os/lnux/sys-info-impl.hpp"

#undef UUU_LOG_TAG
#define UUU_LOG_TAG "uuu_lib_helpers"
