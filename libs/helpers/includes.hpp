//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes.hpp
\date       10.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Внешний интерфейс включения модуля.
*/
#include "consts/vals.hpp"

#include "utils/int2type.hpp"
#include "utils/cuuid.hpp"
#include "utils/check_functs.hpp"
#include "utils/values-storage.hpp"

#include "sys/isys-info.hpp"
#include "sys/factory_about_sys.hpp"

#include "sys/cpu/type-ext-cpu.hpp"
#include "sys/cpu/support-extension-cpu.hpp"
#include "sys/cpu/text-ext-cpu.hpp"
#include "sys/cpu/cpu-info.hpp"

#include "statistic/time_types_statistics.hpp"
#include "statistic/element-stat-info.hpp"
#include "statistic/expanded-time-statistic.hpp"

#include "dlls/forever-load-dlls.hpp"
#include "process/process_functs.hpp"
#include "proxy/mem-proxy-base.hpp"
#include "hboost/name-remover.hpp"
#include "thread/generic_thread_funct.hpp"

#include "mem/defines_check_buff.hpp"
#include "mem/aligned_mem_functs.hpp"
#include "mem/move_mem_ptr_functs.hpp"
#include "mem/acopy.hpp"
#include "mem/buff_copy.hpp"
#include "mem/check_buff.hpp"
#include "mem/set_buff.hpp"

#include "fps/fps-controller.hpp"

#include "windows/process_gen_functs.hpp"
#include "windows/window_gen_functs.hpp"

#include "win32/safe_clear_functs.hpp"
#include "win32/guarde-gdi.hpp"

#include "uids/minor.hpp"
#include "uids/cat.hpp"
#include "uids/major.hpp"
#include "uids/interf.hpp"
#include "uids/codecs.hpp"
#include "uids/helpers/uids2bytes_functs.hpp"

#include "files/includes.hpp"

#include "sorting/includes.hpp"

#include "strings/w16_to_u8.hpp"

#if 0
//  Дожны включаться отдельно, пока так.
#include "dshow/consts/vals.hpp"
#include "dshow/com-ptr.hpp"
#include "dshow/dshow_interfaces.hpp"
#include "dshow/interf_ptrs.hpp"
#include "dshow/convert-format-functs.hpp"
#include "dshow/dump-functs.hpp"
#endif
