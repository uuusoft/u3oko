#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      empty brief
*/

namespace dlls { namespace sources { namespace gen_vgen { namespace consts {

#if defined(UUU_OS_WIN32_DESKTOP) || defined(UUU_OS_GNU_LINUX)
const int mc_delay_skip_cycle = 1;
#elif defined(UUU_OS_ANDROID)
const int mc_delay_skip_cycle = 5;
#elif defined(UUU_OS_RASPBERRY)
const int mc_delay_skip_cycle = 10;
#else
#error select OS
#endif

const int min_size_buffer = 1024 * 1024;

}}}}      // namespace dlls::sources::gen_vgen::consts
