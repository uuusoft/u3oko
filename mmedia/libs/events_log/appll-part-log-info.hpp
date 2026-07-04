#pragma once
/**
\file       appll-part-log-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/

namespace libs::events_log::syn
{
using LogLevels = ::libs::events_base::props::modules::log::LogLevels;
}

namespace libs::events_log
{
struct AppllPartLogInfo final {
  explicit AppllPartLogInfo (
    const syn::LogLevels&       msg_state = syn::LogLevels::info,
    std::string                 subsys    = "xsybx",
    std::string                 version   = "xverx",
    const std::source_location& place     = std::source_location::current ());

  virtual ~AppllPartLogInfo () = default;

  syn::LogLevels msg_state_;   //< Тип сообщения
  std::string    subsys_;      //< Идентификатор подсистемы
  std::string    version_;     //< Версия
  std::string    func_;        //< Имя функции, которая генерирует сообщение
  std::string    file_;        //< Имя файла в котором находится функция
  std::uint32_t  line_;        //< Номер строки файла, в которой сгенерированно сообщение

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events_log

BOOST_CLASS_EXPORT_KEY (::libs::events_log::AppllPartLogInfo);
