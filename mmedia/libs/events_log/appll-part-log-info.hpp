#pragma once
/**
\file       appll-part-log-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace libs::events_log::syn
{
using LogLevels = ::libs::events_base::props::modules::log::LogLevels;
}

namespace libs::events_log
{
struct AppllPartLogInfo final {
  explicit AppllPartLogInfo (
    const syn::LogLevels&       = syn::LogLevels::info,
    const std::string_view      = "xsybx",
    const std::string_view      = "xverx",
    const std::string_view      = std::to_string (std::hash< std::thread::id > {}(std::this_thread::get_id ())),
    const std::source_location& = std::source_location::current ());

  virtual ~AppllPartLogInfo () = default;

  syn::LogLevels msg_state_;   //< Тип сообщения
  std::string    subsys_;      //< Идентификатор подсистемы
  std::string    version_;     //< Версия
  std::string    thread_id_;   //< Идентификатор потока исполнения
  std::string    func_;        //< Имя функции, которая генерирует сообщение
  std::string    file_;        //< Имя файла в котором находится функция
  std::uint32_t  line_;        //< Номер строки файла, в которой сгенерированно сообщение

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events_log

U3_BOOST_CLASS_EXPORT_KEY (::libs::events_log::AppllPartLogInfo);
