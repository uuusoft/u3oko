#pragma once
/**
\file       throw-exceptions-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
*/

/// Макрос для стандартной генерации исключения, в данной реализации используем исключение boost
#ifndef U3_THROW_EXCEPTION
#  define U3_THROW_EXCEPTION(u3def_param)                                               \
    {                                                                                   \
      std::stringstream temp_info_exception;                                            \
      temp_info_exception << (u3def_param);                                             \
      BOOST_THROW_EXCEPTION (std::runtime_error (temp_info_exception.str ().c_str ())); \
    }
#endif
