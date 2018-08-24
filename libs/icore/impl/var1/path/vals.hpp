//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Объявление констант данной реализации графа обработки данных
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace path { namespace consts {

const int         max_count_objs                 = 1 * 1024;      //< Максимальное количество объектов в одном графе.
const int         max_helper_objs                = 2;             //< ???
const std::size_t indx_source_interf_helper      = 0;             //< ???
const int         max_count_frames_without_sleep = 5;             //< Максимальное количество обработанных кадров без засыпания. Для предупреждения "подзависания" системы на одноядерной системе.
const int         ms_sleep_work_thread_force     = 50;            //< Время засыпания рабочего потока графа в ms, если система не успевает обрабатывать буфера.
const int         ms_sleep_work_thread_soft      = 10;            //< Время засыпания рабочего потока графа в ms, если в системе нет достаточного количества буферов для обработки..

}}}}}}      // namespace libs::icore::impl::var1::path::consts
