#pragma once
/**
\file       includes.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_defines
\brief      Базовый интерфейс включения для всех файлов системы
*/
// controls
#include "control-defines-includes.hpp"

// startdard libs
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <sys/types.h>
#include <filesystem>
#include <codecvt>
#include <ctime>

#include <typeinfo>
#include <typeindex>

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
#include <ranges>

#include <csignal>
#include <atomic>

#include <memory>
#include <math.h>
#include <numeric>
#include <chrono>
#include <random>

#include <thread>
#include <future>
#include <barrier>
#include <mutex>
#include <condition_variable>

#include <type_traits>

#include <cmath>

// 3rd libs
#include "os-android-specific-includes.hpp"
#include "intrunsic-files-include.hpp"
#include "boost-lib-includes.hpp"
#include <pugixml.hpp>

// configs
#include "project_config.hpp"
#include "defines-includes.hpp"

// impls
#include "mmedia/libs/utility/utility-lib-includes.hpp"
#include "mmedia/utils/mems/mems-includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_conv/optim-conv-const-vals.hpp"
#include "mmedia/utils/dbufs/dbufs-includes.hpp"
#include "mmedia/libs/bufs/libs-bufs-includes.hpp"
