#pragma once
/**
\file       defines-throw-except.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
*/

/// Макрос для стандартной генерации исключения, в данной реализации используем исключение boost
#ifndef U3_THROW_EXCEPT
#  define U3_THROW_EXCEPT(u3def_param)                                     \
    {                                                                      \
      std::stringstream sexcpt;                                            \
      sexcpt << (u3def_param);                                             \
      BOOST_THROW_EXCEPTION (std::runtime_error (sexcpt.str ().c_str ())); \
    }
#endif
