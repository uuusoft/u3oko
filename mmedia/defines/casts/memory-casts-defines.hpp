#pragma once
/**
\file       memory-casts-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_defines
\brief      Набор макросов преобразований указателя, чтобы контролировать применение reinterpret_cast.
*/
#ifndef U3_CAST_STATIC
#  define U3_CAST_STATIC static_cast
#endif

#ifndef U3_CAST_CONST
#  define U3_CAST_CONST const_cast
#endif

#ifndef U3_CAST_REINTERPRET
#  define U3_CAST_REINTERPRET reinterpret_cast
#endif

#ifndef U3_CAST_2VOID
#  define U3_CAST_2VOID(u3def_val) reinterpret_cast< void** > (u3def_val)
#endif

#ifndef U3_CAST_PTR2INT
#  define U3_CAST_PTR2INT(u3def_val) reinterpret_cast< std::uint64_t > (u3def_val)
#endif
