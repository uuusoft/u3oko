#pragma once
/**
\file       defines-add-super-type.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
\brief      Объявление вспомогательного макроса для декларирования типа на суперкласс внутри производного
*/

#ifndef U3_ADD_SUPER_CLASS
#  if defined(U3_COMPILER_GNUC)
#    define U3_ADD_SUPER_CLASS(u3def_param) using super = u3def_param;
#  else
#    define U3_ADD_SUPER_CLASS(u3def_param) using super = u3def_param;
#  endif
#endif
