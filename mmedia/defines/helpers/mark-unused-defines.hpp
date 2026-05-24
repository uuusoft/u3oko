#pragma once
/**
\file       mark-unused-defines.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       03.10.2024
\project    u3_defines
*/

#ifndef U3_MARK_UNUSED
#  define U3_MARK_UNUSED [[maybe_unused]]
#endif

#ifndef U3_MARK_UNUSED_HERE
#  define U3_MARK_UNUSED_HERE(obj) (void) obj
#endif
