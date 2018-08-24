//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       log_module_files_work_functs.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "log-module.hpp"

namespace modules { namespace uuu_log { namespace appl {

void
LogModule::make_dir_for_logs ()
{
  UASSERT (path2logs_.empty ());
  UASSERT (path2sessions_.empty ());

  const boost::posix_time::ptime _sys_time = boost::posix_time::microsec_clock::universal_time ();

  name_folder_current_session_ = boost::posix_time::to_iso_string (_sys_time);
  path2sessions_               = paths_->get_path (::libs::iproperties::appl_paths::TypePath::logs);
  path2logs_                   = ::libs::helpers::files::make_path (path2sessions_, name_folder_current_session_);

  XULOG_TRACE ("uuu_log::LogModule::init:: prefix=" + path2sessions_);
  XULOG_TRACE ("uuu_log::LogModule::init:: log=" + path2logs_);

  ::libs::helpers::files::create_folder (path2logs_);
  UASSERT (!path2logs_.empty ());
  UASSERT (!path2sessions_.empty ());
  return;
}


void
LogModule::open_log_file ()
{
  UASSERT (!file_.is_open ());
  UASSERT (!path2logs_.empty ());
  const std::string _file_log_path = ::libs::helpers::files::make_path (path2logs_, to_str (indx_file_) + std::string (".log"));
  file_.open (_file_log_path.c_str (), std::ios_base::out | std::ios_base::app);
  CHECK_CALL (file_.is_open (), ("failed open log file" + _file_log_path).c_str ());
  return;
}


void
LogModule::delete_folders (const list_folders_type& _folders)
{
  for (const auto& _folder : _folders)
    {
      if (_folder == name_folder_current_session_)
        {
          // нельзя удалять директорию текущего сеанса логирования.
          continue;
        }

      const std::string _path2logs = ::libs::helpers::files::make_path (path2sessions_, _folder);
      if (!bfs::is_directory (_path2logs) || !bfs::exists (_path2logs))
        {
          continue;
        }

      ::boost::system::error_code _error;
      bfs::remove_all (_path2logs, _error);

      if (_error)
        {
          XULOG_ERROR ("failed remove logs, " << _path2logs << ", " << _error.message ());
        }
    }
  return;
}


std::size_t
LogModule::fill_tab (const std::size_t _len, const std::size_t _max_count_tabs, const std::size_t _size_tab)
{
  const std::size_t _diff_tabs  = std::min<std::size_t> (_len / _size_tab, _max_count_tabs);
  const std::size_t _count_tabs = _max_count_tabs - _diff_tabs;

  for (std::size_t _indx_tab = 0; _indx_tab < _count_tabs; ++_indx_tab)
    {
      file_ << "\t";
    }
  return _count_tabs;
}


void
LogModule::flush_events ()
{
  for (::libs::events::IEvent::ptr& _evnt : events_)
    {
      flush_event (_evnt);
    }

  events_.clear ();

  auto       _log_prop = ::libs::iproperties::helpers::cast_event<::libs::ievents::props::modules::log::PropertyLogModuleEvent> (event_props_.module_log_);
  const auto _max_size = _log_prop->get_val (ValsLogModule::max_size_one_log_file_byte);
  if (_max_size && file_.tellg () >= _max_size)
    {
      ++indx_file_;
      file_.close ();
      open_log_file ();
    }
  return;
}


std::size_t
flush_long_descr_event (std::fstream& _file, const InfoLogEvent::raw_ptr _cevnt)
{
  std::size_t _ret = 0;
  std::string _txt;

  _txt = _cevnt->text (libs::ilog_events::TypeLogText::function);
  _ret += _txt.length ();
  _file << _txt;
  _file << " ";

  _txt = _cevnt->text (libs::ilog_events::TypeLogText::line);
  _ret += _txt.length ();
  _file << _txt;
  return _ret;
}


void
LogModule::flush_event (::libs::events::IEvent::ptr& _evnt)
{
  std::string _txt;
  auto        _cevnt = ::libs::iproperties::helpers::cast_event<InfoLogEvent> (_evnt);
  std::size_t _len   = 0;
  std::size_t _tabs  = 0;

  _txt = boost::posix_time::to_simple_string (_cevnt->get_time ());
  _len += _txt.length ();
  file_ << _txt;

  _tabs += fill_tab (_len, consts::max_count_tabs_date, consts::size_tab);

  _txt = _cevnt->text (::libs::ilog_events::TypeLogText::subsys);
  _len += _txt.length ();
  file_ << _txt;
  XULOG_TRACE (_txt);

  _tabs += fill_tab (_txt.length (), consts::max_count_tabs_subsys, consts::size_tab);

  {
    _txt = _cevnt->text (::libs::ilog_events::TypeLogText::text);

    std::replace_if (_txt.begin (), _txt.end (), [](const char& _val) -> bool { return '\t' == _val ? true : false; }, ' ');

    const std::size_t _length_txt = _txt.length ();
    const std::size_t _max_symbol = consts::size_tab * (consts::max_count_tabs_info - 1);
    std::size_t       _indx_first = 0;
    std::size_t       _size_last  = 0;
    std::string       _sub_txt;

    do
      {
        std::size_t _indx_end = _txt.find ('\n', _indx_first);

        if (std::string::npos == _indx_end)
          {
            _indx_end = _indx_first + _max_symbol;
          }
        else
          {
            _txt[_indx_end++] = ' ';
          }

        _indx_end = _indx_end - _indx_first > _max_symbol ? _indx_first + _max_symbol : _indx_end;
        _sub_txt  = _txt.substr (_indx_first, std::min<size_t> (_length_txt - _indx_first, _indx_end - _indx_first));

        if (_sub_txt.empty ())
          {
            break;
          }

        file_ << _sub_txt;

        _size_last = _sub_txt.length ();
        _indx_first += _size_last;

        if (_indx_first < _length_txt)
          {
            file_ << std::endl;
            _tabs += fill_tab (0, consts::max_count_tabs_subsys + consts::max_count_tabs_date, consts::size_tab);
          }
      }
    while (true);

    _tabs += fill_tab (_size_last, consts::max_count_tabs_info, consts::size_tab);
  }

  auto _log_prop = ::libs::iproperties::helpers::cast_event<::libs::ievents::props::modules::log::PropertyLogModuleEvent> (event_props_.module_log_);
  if (_log_prop->get_val (ValsLogModule::enable_store_call_place))
    {
      _len += flush_long_descr_event (file_, _cevnt);
    }

  file_ << std::endl;
  return;
}

}}}      // namespace modules::uuu_log::appl
