#pragma once
/**
\file       convert-vals2string-log-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       25.02.2022
\project    u3_defines
*/
#ifndef TOLOG
#  define TOLOG(u3def_param) std::string (" " #u3def_param) + "=" + u3def_param
#endif

#ifndef FTOLOG
#  define FTOLOG(u3def_param) std::string (#u3def_param) + "=" + u3def_param
#endif

#ifndef VTOLOG
#  define VTOLOG(u3def_param) std::string (" " #u3def_param) + "=" + std::to_string (u3def_param)
#endif

#ifndef FVTOLOG
#  define FVTOLOG(u3def_param) std::string (#u3def_param) + "=" + std::to_string (u3def_param)
#endif

#ifndef PTR_TOLOG
#  define PTR_TOLOG(u3def_param) std::string (" " #u3def_param) + "=0x?" + std::to_string (U3_CAST_PTR2INT (u3def_param))
#endif

#ifndef PTR_TOLOG
#  define PTR_TOLOG(u3def_param) std::string (#u3def_param) + "=0x?" + std::to_string (U3_CAST_PTR2INT (u3def_param))
#endif
