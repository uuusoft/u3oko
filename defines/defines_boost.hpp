//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_boost.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
*/
#ifndef BOOST_THREAD_USE_LIB
#define BOOST_THREAD_USE_LIB
#endif

#ifndef BOOST_NO_RVALUE_REFERENCES
#define BOOST_NO_RVALUE_REFERENCES
#endif

#ifndef BOOST_THREADS_NO_LIB
//# define  BOOST_THREADS_NO_LIB
#endif

#ifndef BOOST_SYSTEM_NO_DEPRECATED
//# define BOOST_SYSTEM_NO_DEPRECATED
#endif


#if defined(UUU_OS_WIN32_DESKTOP)

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef BOOST_USE_WINDOWS_H
#define BOOST_USE_WINDOWS_H
#endif

#endif


#if defined(UUU_OS_ANDROID)

#ifndef BOOST_INTERPROCESS_SHARED_DIR_PATH
#define BOOST_INTERPROCESS_SHARED_DIR_PATH "/sdcard"
#endif

#endif


#ifndef BOOST_DLL_FORCE_NO_WEAK_EXPORTS
#define BOOST_DLL_FORCE_NO_WEAK_EXPORTS
#endif

#ifndef BOOST_DLL_FORCE_ALIAS_INSTANTIATION
#define BOOST_DLL_FORCE_ALIAS_INSTANTIATION
#endif

#ifndef BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
//#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#endif
