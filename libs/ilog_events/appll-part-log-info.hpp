#pragma once
/**
\file       appll-part-log-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/

namespace libs { namespace ilog_events {
/**
\brief  Empty description
*/
struct AppllPartLogInfo
{
  explicit AppllPartLogInfo (
    const std::string& _subsys = "x0x",
    const std::string& _funct  = __FILE__,
    const int          _line   = __LINE__);

  virtual ~AppllPartLogInfo ();

  std::string subsys_;      //< Идентификатор подсистемы.
  std::string funct_;       //< Имя функции, которая генерирует сообщение.
  int         line_;        //< Номер строки функции.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}      // namespace libs::ilog_events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::AppllPartLogInfo);
