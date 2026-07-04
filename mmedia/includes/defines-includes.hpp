#pragma once
/**
\file       defines-includes.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_includes
\brief      Базовые определения для включения во все файлы сборки
*/
#include "../defines/logs/defines-xlog-trace.hpp"
#include "../defines/logs/defines-file-log-id-vals.hpp"
#include "../defines/logs/defines-convert-vals2string.hpp"

#include "../defines/checks/defines-asserts.hpp"
#include "../defines/checks/defines-throw-except.hpp"
#include "../defines/checks/defines-check-state.hpp"

#include "../defines/helpers/defines-mark-unused.hpp"
#include "../defines/helpers/defines-add-pointers-to-self.hpp"
#include "../defines/helpers/defines-add-make-shared-this.hpp"
#include "../defines/helpers/defines-add-super-type.hpp"
#include "../defines/helpers/defines-add-disable-move-copy.hpp"
#include "../defines/helpers/defines-mem-aligned.hpp"

#include "../defines/boost/defines-boost-lib-serialize-to-archive.hpp"
