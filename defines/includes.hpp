#pragma once
/**
\file       includes.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Базовый интерфейс включения для всех файлов системы.
*/
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <sys/types.h>

#include <typeinfo>
#include <typeindex>

#include "includes_for_android.hpp"

#include <string>
#include <locale>

#include <sstream>
#include <iostream>
#include <fstream>

#include <vector>
#include <deque>
#include <array>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <algorithm>
#include <functional>
#include <iterator>

#include <csignal>
#include <atomic>

#include <memory>
#include <math.h>
#include <numeric>
#include <chrono>
#include <random>

#include <thread>
#include <future>

#include <mutex>
#include <condition_variable>

#include <type_traits>

#include <cmath>

#include "include_intrunsic.hpp"

#include "boost_includes.hpp"


//  helpers
#include "defines_int_casts.hpp"
#include "defines_log_utrace.hpp"
#include "defines_string2obj.hpp"

#include "defines_tassert.hpp"
#include "get_place_call_funct.hpp"
#include "defines_uassert.hpp"
#include "defines_debuassert.hpp"

#include "defines_exceptions.hpp"
#include "defines_check_state.hpp"
#include "define-check-mem.hpp"
#include "defines_temp_asserts.hpp"
#include "defines_class_ptrs.hpp"
#include "defines_super_type.hpp"
#include "defines_count_of.hpp"
#include "defines_mem_cast.hpp"
#include "defines_aligned_mem.hpp"

#include "mmedia/utils/mem_functs/includes.hpp"
#include "mmedia/libs/helpers/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_conv/vals.hpp"
#include "mmedia/utils/dbuffs/includes.hpp"
#include "mmedia/libs/buffs/includes.hpp"

#include "include_pugixml.hpp"
//#include "defines_win32.hpp"
