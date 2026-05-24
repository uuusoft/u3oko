#pragma once
/**
\file       helpers-lib-includes.hpp
\date       10.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
*/
#include "consts/helpers-lib-const-vals.hpp"

#include "check/check-ptr-funcs.hpp"

#include "utils/int2type.hpp"
#include "utils/cuuid.hpp"
#include "utils/check-bounds-funcs.hpp"
#include "utils/values-storage.hpp"
#include "utils/transform-value-helper.hpp"

#include "sys/isys-info.hpp"
#include "sys/factory_about_sys.hpp"

#include "sys/cpu/type-ext-cpu.hpp"
#include "sys/cpu/type-minor-ext-cpu.hpp"
#include "sys/cpu/type-ext-dsp.hpp"
#include "sys/cpu/support-extension-cpu.hpp"
#include "sys/cpu/text-ext-cpu.hpp"
#include "sys/cpu/text-minor-ext-cpu.hpp"
#include "sys/cpu/text-ext-dsp.hpp"
#include "sys/cpu/cpu-info.hpp"

#include "statistic/expanded-times-types.hpp"
#include "statistic/expanded-time.hpp"
#include "statistic/expanded-times.hpp"

#include "mem/helpers-lib-aligned-mem-funcs.hpp"
#include "mem/helpers-lib-move-mem-ptr-funcs.hpp"
#include "mem/helpers-lib-u3copy-func.hpp"
#include "mem/helpers-lib-buf-copy-func.hpp"
#include "mem/helpers-lib-check-buf-funcs.hpp"
#include "mem/helpers-lib-set-buf-funcs.hpp"
#include "mem/iblock-mem.hpp"

#include "dlls/dll-mock.hpp"
#include "dlls/forever-load-dlls.hpp"
#include "dlls/helpers-lib-decorate-dll-name-funcs.hpp"

#include "proxy/mem-proxy-base.hpp"

#include "process/process-helper-funcs.hpp"

#include "hboost/name-remover.hpp"

#include "thread/empty-mutex.hpp"
#include "thread/priorities-enum.hpp"

#include "fps/fps-controller.hpp"

#if defined(U3_OS_WIN32_DESKTOP)
#  include "platforms/win32/last-error-funcs.hpp"
#  include "platforms/win32/process_gen_funcs.hpp"
#  include "platforms/win32/window_gen_funcs.hpp"
#  include "platforms/win32/safe_clear_funcs.hpp"
#  include "platforms/win32/guarde-gdi.hpp"
#  include "platforms/win32/handler-gdi-obj.hpp"
#endif

#include "uids/minor.hpp"

#include "uids/helpers/fourcc-const-vals.hpp"
#include "uids/helpers/uids2bytes_funcs.hpp"

#include "sorting/includes.hpp"

#include "strings/codepage-convert-funcs.hpp"
#include "strings/work-with-string-bufs-funcs.hpp"

#include "files/libs-helpers-files-includes.hpp"

#include "base64/base64_encoding_funcs.hpp"

#include "time/time-point.hpp"
#include "time/timer.hpp"

#include "json/convert-json-helper-funcs.hpp"

#include "log/log-source-place-func.hpp"
#include "log/suppressor-verbose-log-msg.hpp"
#include "log/get-module-version-func.hpp"

#if 0
// EAI-REFACT чтобы не тянуть зависимость от sqlite этот файл включается отдельно для каждого модуля, в котором есть потребность в sqlite.
#  include "sqlite/sql-resource-managment-helpers.hpp"
#  include "sqlite/sqlite-call-helper-funcs.hpp"
#endif
