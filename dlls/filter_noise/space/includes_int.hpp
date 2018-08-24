//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes_int.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      Внутренний интерфейс включения данного модуля.
*/
#include "../../includes_int.hpp"
#include "mmedia/libs/helpers/statistic/helpers/functors_with_statistic.hpp"
#include "syn_types.hpp"
#include "info-filter-dll.hpp"
#include "ifilter-impl.hpp"
#include "impl/includes.hpp"
#include "filter-dll.hpp"

#undef UUU_LOG_TAG
#define UUU_LOG_TAG "uuu_space_domain"
