#pragma once
/**
\file       defines-add-make-shared-this.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
\brief      Объявление макроса для контроля создания объектов указанного типа (для примера только через данную функцию)
*/

#ifndef U3_ADD_MAKE_SHARED_THIS
#  define U3_ADD_MAKE_SHARED_THIS(u3def_param)                                                    \
    template< typename... Args >                                                                  \
    static ::std::shared_ptr< u3def_param >                                                       \
    make_shared_this (Args&&... args)                                                             \
    {                                                                                             \
      return ::std::make_shared< u3def_param > (Acessor { 0 }, ::std::forward< Args > (args)...); \
    }
#endif
