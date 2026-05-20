#pragma once
/**
\file       module-log-exception-logger.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_module_log
*/

namespace modules::uuu_log::appl::thread
{
/// Общий каркас для фиксации исключений в произвольном потоке системы
/// \tparam     TTLogger  тип для логирования в потоке
/// \param[in]  logger    реализация логирования
/// \param[in]  text      текст сообщения об исключении
template< typename TTLogger >
struct ExceptionLogger final {
  ExceptionLogger (const TTLogger& logger) :
    logger_ (logger)
  {
  }

  void
  operator() (const std::string& text) noexcept
  {
    try
    {
      if (!logger_ || text.empty ())
      {
        return;
      }

      // EAI-DISABLED-03.05.2026
      U3_XLOG_DEV ("EXCEPTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      //~U~3_MSG2LOGGER (logger_, text.c_str (), "u3exception_xxx", "wtfversion", ::libs::ievents::props::modules::log::LogLevels::exception);
    }
    catch (...)
    {
      U3_XLOG_ERROR ("Except in ExceptionLogger");
    }
  }

  private:
  TTLogger logger_;   //< Реализация логирования
};
}   // namespace modules::uuu_log::appl::thread
