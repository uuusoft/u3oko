//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_exceptions.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      empty brief
*/
/**
\brief  Макрос для стандартной генерации исключения.
        В данной реализации используем исключение boost.
*/
#ifndef UUU_THROW_EXCEPTION
#define UUU_THROW_EXCEPTION(info)                                                      \
  {                                                                                    \
    UASSERT_SIGNAL ("exception, " << info);                                            \
    std::stringstream _temp_info_exception;                                            \
    _temp_info_exception << info;                                                      \
    BOOST_THROW_EXCEPTION (std::runtime_error (_temp_info_exception.str ().c_str ())); \
  }
#endif
/**
\brief  Макрос для стандартной генерации исключения-уведомления.
*/
#ifndef UUU_THROW_INFO_EXCEPTION
#define UUU_THROW_INFO_EXCEPTION(info) BOOST_THROW_EXCEPTION (std::logic_error (info));
#endif
