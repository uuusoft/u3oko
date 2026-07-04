#pragma once
/**
\file       defines-mark-unused.hpp
\author     Erashov Anton erashov2026@proton.me
\date       03.10.2024
\project    u3_defines
*/

#ifndef U3_MARK_UNUSED
#  define U3_MARK_UNUSED [[maybe_unused]]
#endif

#ifndef U3_MARK_UNUSED_HERE
#  define U3_MARK_UNUSED_HERE(obj) (void) obj
#endif
