#pragma once
/**
\file       x86_cpu.hpp
\brief      Class for checking CPU
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_helpers_lib
*/

#ifdef U3_CPU_X86

namespace libs::utility::sys::cpu::x86
{
/// получаем расширенную строчку идентификатора процессора, если процессор поддерживает эту функцию
std::string get_text_about_cpu ();

/// Метод для возврата информации о возможностях процессора по поддержке MMX,SSE,SSE2,SSE3,SSE4,EM64
bool get_exts_cpu (SupportExtensionCPU& ret);

/// 29.05.2016 - возращает описание типа процессора через инструкцию cpuid
bool get_all_info_cpu (SupportExtensionCPU& ret);
}   // namespace libs::utility::sys::cpu::x86

#endif
