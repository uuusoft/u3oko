#pragma once
/**
\file       defines-add-disable-move-copy.hpp
\author     Erashov Anton erashov2026@proton.me
\date       02.03.2022
\project    u3_defines
*/

#ifndef U3_ADD_DELETE_MOVE_COPY
#  define U3_ADD_DELETE_MOVE_COPY(u3def_param)                \
    u3def_param (const u3def_param&)                = delete; \
    u3def_param& operator= (const u3def_param&)     = delete; \
    u3def_param (u3def_param&&) noexcept            = delete; \
    u3def_param& operator= (u3def_param&&) noexcept = delete;
#endif
