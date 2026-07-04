#pragma once
/**
\file       defines-add-pointers-to-self.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
\brief      Объявление макроса для декларирования типов-указателей на объекты  заданного типа
*/

#ifndef U3_ADD_POINTERS_TO_SELF
#  define U3_ADD_POINTERS_TO_SELF(u3def_param)              \
    using ptr       = std::shared_ptr< u3def_param >;       \
    using cptr      = std::shared_ptr< const u3def_param >; \
    using weak_ptr  = std::weak_ptr< u3def_param >;         \
    using cweak_ptr = std::weak_ptr< const u3def_param >;   \
    using uniq_ptr  = std::unique_ptr< u3def_param >;       \
    using cuniq_ptr = std::unique_ptr< const u3def_param >; \
    using raw_ptr   = u3def_param*;                         \
    using craw_ptr  = const u3def_param*;
#endif
