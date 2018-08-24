//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       exception-logger.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      empty brief
*/

namespace modules { namespace uuu_log { namespace appl { namespace thread {
/**
  \brief      Общий каркас для функции фиксации исключений в произвольном потоке системы.
  \tparam     TExceptionLogger  тип для логирования в функции потока.
  \param[in]  _logger           реализация логирования.
  \param[in]  _text             текст сообщения об исключении.
  */
template <
  typename TExceptionLogger>
struct ExceptionLogger
{
  ExceptionLogger (TExceptionLogger _logger) :
    logger_ (_logger)
  {}

  void
  operator() (const std::string& _text)
  {
    if (!logger_ || _text.empty ())
      {
        return;
      }
    EXCEPT_LOG (logger_, _text.c_str (), "uuu_exception_xxx");
    return;
  }


  private:
  TExceptionLogger logger_;      //< Реализация логгирования.
};

}}}}      // namespace modules::uuu_log::appl::thread
