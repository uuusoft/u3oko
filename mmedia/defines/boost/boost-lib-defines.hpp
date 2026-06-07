#pragma once
/**
\file       boost-lib-defines.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_defines
*/
#ifndef BOOST_ALLOW_DEPRECATED_HEADERS
#  define BOOST_ALLOW_DEPRECATED_HEADERS
#endif

#ifndef BOOST_THREAD_USE_LIB
#  define BOOST_THREAD_USE_LIB
#endif

#ifndef BOOST_NO_CXX98_FUNCTION_BASE
// #  define BOOST_NO_CXX98_FUNCTION_BASE
#endif

#ifndef BOOST_NO_RVALUE_REFERENCES
#  define BOOST_NO_RVALUE_REFERENCES
#endif

#ifndef BOOST_THREADS_NO_LIB
// # define  BOOST_THREADS_NO_LIB
#endif

#ifndef BOOST_SYSTEM_NO_DEPRECATED
// # define BOOST_SYSTEM_NO_DEPRECATED
#endif

#ifdef U3_OS_WIN32_DESKTOP
#  ifndef _SCL_SECURE_NO_WARNINGS
#    define _SCL_SECURE_NO_WARNINGS
#  endif

#  ifndef BOOST_USE_WINDOWS_H
#    define BOOST_USE_WINDOWS_H
#  endif
#endif

#ifdef U3_OS_ANDROID
#  ifndef BOOST_INTERPROCESS_SHARED_DIR_PATH
// #define BOOST_INTERPROCESS_SHARED_DIR_PATH "/sdcard"
#  endif

#  ifndef BOOST_INTERPROCESS_SHARED_DIR_FUNC
#    define BOOST_INTERPROCESS_SHARED_DIR_FUNC
#  endif
#endif

#ifndef BOOST_DLL_FORCE_NO_WEAK_EXPORTS
#  define BOOST_DLL_FORCE_NO_WEAK_EXPORTS
#endif

#ifndef BOOST_DLL_FORCE_ALIAS_INSTANTIATION
#  define BOOST_DLL_FORCE_ALIAS_INSTANTIATION
#endif

#ifndef BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
// #define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#endif

#ifndef U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP
#  define U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP(U3XML_NAME_TYPE, U3BASE_TYPE) \
    boost::serialization::make_nvp (U3XML_NAME_TYPE, boost::serialization::base_object< U3BASE_TYPE > (*this));
#endif
