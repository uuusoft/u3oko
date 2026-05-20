#pragma once
/**
\file       module-http-includes-special.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_http_module
*/
#ifndef BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#  define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#endif

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#  define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#  define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef BOOST_ASIO_DISABLE_STD_STRING_VIEW
#  define BOOST_ASIO_DISABLE_STD_STRING_VIEW
#endif

#ifndef BOOST_ASIO_DISABLE_STRING_VIEW
#  define BOOST_ASIO_DISABLE_STRING_VIEW
#endif

#include <boost/asio.hpp>
