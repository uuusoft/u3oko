#pragma once
/**
\file       arm_cpu.hpp
\brief      Class for checking CPU
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.10.2016.
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs {
namespace helpers {
namespace sys {
namespace cpu {
namespace arm {
#if defined(UUU_CPU_ARM)

/**
  \brief  получаем расширенную строчку идентификатора процессора, если процессор поддерживает эту функцию
  */
std::string get_text_about_cpu ();
/**
  \brief    Метод для возврата информации о возможностях процессора по поддержке MMX,SSE,SSE2,SSE3,SSE4,EM64
  \param[in]  _ret  ???
  \return   ???
  */
bool get_exts_cpu (SupportExtensionCPU& _ret);
/**
  \brief  29.05.2016 - возращает описание типа процессора через инструкцию cpuid
  */
bool get_all_info_cpu (SupportExtensionCPU& _ret);
#endif
}
}}}}      // namespace libs::helpers::sys::cpu::arm
