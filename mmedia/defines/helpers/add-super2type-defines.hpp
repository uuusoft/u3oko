#pragma once
/**
\file       add-super2type-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
\brief      Объявление вспомогательного макроса для декларирования типа на суперкласс внутри производного
*/

//  Вспомогательный макрос для декларирования типа на суперкласс
#ifndef U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS
#  if defined(U3_COMPILER_GNUC)
#    define U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS(u3def_param) using super = u3def_param;
#  else
#    define U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS(u3def_param) using super = u3def_param;
#  endif
#endif
