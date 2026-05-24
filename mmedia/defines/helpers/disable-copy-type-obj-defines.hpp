#pragma once
/**
\file       disable-copy-type-obj-defines.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       02.03.2022
\project    u3_defines
*/

#ifndef U3_HELPER_DISABLE_ACOPY_TYPE
#  define U3_HELPER_DISABLE_ACOPY_TYPE(u3def_param)           \
    u3def_param (const u3def_param& src)            = delete; \
    u3def_param& operator= (const u3def_param& src) = delete;
#endif
