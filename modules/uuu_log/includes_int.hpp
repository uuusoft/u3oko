//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes_int.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      Внутренний интерфейс включения данного модуля.
*/
#include "../includes_int.hpp"
#include "includes.hpp"

#include "log_defines.hpp"

#include "appl/syn_types.hpp"
#include "appl/consts/vals.hpp"
#include "appl/log-module.hpp"
#include "appl/helpers/get_sort_files_functs.hpp"

#undef UUU_LOG_TAG
#define UUU_LOG_TAG ::libs::ilink::consts::id_log
