#pragma once
/**
\file       add-ptrs2type-defines.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_defines
\brief      Объявление макроса для декларирования типов-указателей на объекты  заданного типа
*/

/// Вспомогательный макрос для декларирования указателей на экземпляры типа внутри типа
#ifndef U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF
#  define U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF(u3def_param) \
    using ptr       = std::shared_ptr< u3def_param >;           \
    using cptr      = std::shared_ptr< const u3def_param >;     \
    using weak_ptr  = std::weak_ptr< u3def_param >;             \
    using cweak_ptr = std::weak_ptr< const u3def_param >;       \
    using uniq_ptr  = std::unique_ptr< u3def_param >;           \
    using cuniq_ptr = std::unique_ptr< const u3def_param >;     \
    using raw_ptr   = u3def_param*;                             \
    using craw_ptr  = const u3def_param*;
#endif

#ifndef U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE
#  define U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE(u3def_param)                               \
    template< typename... T >                                                                  \
    static ::std::shared_ptr< u3def_param >                                                    \
    make_shared_this (T&&... args)                                                             \
    {                                                                                          \
      return ::std::make_shared< u3def_param > (Acessor { 0 }, ::std::forward< T > (args)...); \
    }
#endif
