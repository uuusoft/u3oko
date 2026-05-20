#pragma once
/**
\file       appll-part-log-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    uuu_ilog_events
*/

namespace libs::ilog_events::syn
{
using LogLevels = ::libs::ievents::props::modules::log::LogLevels;
}

namespace libs::ilog_events
{
struct AppllPartLogInfo final {
  explicit AppllPartLogInfo (
    const syn::LogLevels&       msg_state = syn::LogLevels::info,
    const std::string&          subsys    = "xsybx",
    const std::string&          version   = "xverx",
    const std::source_location& place     = std::source_location::current ());

  virtual ~AppllPartLogInfo ();

  syn::LogLevels msg_state_;   //< Тип сообщения
  std::string    subsys_;      //< Идентификатор подсистемы
  std::string    version_;     //< Версия
  std::string    func_;        //< Имя функции, которая генерирует сообщение
  std::string    file_;        //< Имя файла в котором находится функция
  std::uint32_t  line_;        //< Номер строки файла, в которой сгенерированно сообщение

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};
}   // namespace libs::ilog_events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::AppllPartLogInfo);
