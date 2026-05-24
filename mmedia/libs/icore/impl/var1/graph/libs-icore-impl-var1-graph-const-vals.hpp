#pragma once
/**
\file       libs-icore-impl-var1-graph-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::graph::consts
{
constexpr std::uint32_t max_count_objs            = 1 * 128;   //< Максимальное количество объектов в одном графе
constexpr std::uint32_t max_helper_objs           = 2;         //<
constexpr std::uint32_t indx_source_interf_helper = 0;         //<

constexpr std::uint32_t max_count_frames_without_sleep      = 5;   //< Максимальное количество обработанных кадров без засыпания. Для предупреждения "подзависания" системы на одноядерной системе
constexpr std::uint32_t max_count_frames_by_externa_request = 3;   //< Максимальное количество обработанных кадров при необработанном внешнем запросе. Для предупреждения "подзависания" системы

constexpr std::uint32_t ms_add_sleep_work_thread_by_external_request     = 30;         //< Добавленное время засыпания рабочего потока графа в ms на каждую итерацию, если графу обработки данных требуется обработать внешний запрос
constexpr std::uint32_t ms_max_add_sleep_work_thread_by_external_request = 5 * 1000;   //< Максимальное добавленное время засыпания рабочего потока графа в ms на каждую итерацию, если графу обработки данных требуется обработать внешний запрос
constexpr std::uint32_t ms_sleep_work_thread_force                       = 100;        //< Время засыпания рабочего потока графа в ms, если система не успевает обрабатывать буфера
constexpr std::uint32_t ms_sleep_work_thread_soft                        = 1;          //< Время засыпания рабочего потока графа в ms, если в системе нет достаточного количества буферов для обработки.
constexpr std::uint32_t ms_max_working_time_per_node_graph               = 2 * 1000;   //< Максимальное время, которое может затратить узел графа на обработку данных. См проблему с dlib в debug, которая обрабатывает один кадр больше минуты
}   // namespace libs::icore::impl::var1::graph::consts
