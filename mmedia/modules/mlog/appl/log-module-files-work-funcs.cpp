/**
\file       log-module-files-work-funcs.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mlog
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-log-includes_int.hpp"
#include "log-module.hpp"

namespace modules::mlog::appl
{
void
LogModule::make_dir_for_logs ()
{
  U3_ASSERT (path2logs_.empty ());
  U3_ASSERT (path2sessions_.empty ());

  const boost::posix_time::ptime sys_time = boost::posix_time::microsec_clock::universal_time ();

  active_session_folder_ = boost::posix_time::to_iso_string (sys_time);
  path2sessions_         = paths_->get_path (::libs::iproperties::appl_paths::Paths::logs);
  path2logs_             = ::libs::helpers::files::make_path (path2sessions_, active_session_folder_);

  ::libs::helpers::files::create_folder (path2logs_);
  U3_ASSERT (!path2logs_.empty ());
  U3_ASSERT (!path2sessions_.empty ());
}


void
LogModule::open_log_file ()
{
  U3_ASSERT (!file_for_store_events_.is_open ());
  U3_ASSERT (!path2logs_.empty ());

  const std::string file_log_path = ::libs::helpers::files::make_path (path2logs_, std::to_string (indx_file_) + std::string (".log"));
  file_for_store_events_.open (file_log_path.c_str (), std::ios_base::out | std::ios_base::app);

  U3_CHECK (file_for_store_events_.is_open (), ("open log file" + file_log_path).c_str ());
}


void
LogModule::delete_folders (const syn::list_folders_type& folders)
{
  U3_XLOG_DBG ("LogModule::delete_folders::---->" + VTOLOG (folders.size ()) + TOLOG (active_session_folder_));
  for (const auto& folder : folders)
  {
    U3_XLOG_DBG ("delete check" + TOLOG (folder.session_id_));
    if (folder.session_id_ == active_session_folder_)
    {
      // нельзя удалять директорию текущего сеанса логирования.
      continue;
    }

    const std::string path2logs = ::libs::helpers::files::make_path (path2sessions_, folder.session_id_);
    if (!::boost::filesystem::is_directory (path2logs) || !::boost::filesystem::exists (path2logs))
    {
      U3_XLOG_WARN ("not exist or not folder" + TOLOG (path2logs));
      continue;
    }

    ::boost::system::error_code error;
    U3_MARK_UNUSED const auto   count_removed_items = ::boost::filesystem::remove_all (path2logs, error);
    U3_XLOG_DBG ("remove all status for " + path2logs + " msg:" + error.message () + VTOLOG (count_removed_items));
    if (error)
    {
      U3_XLOG_ERROR ("error remove logs: " + path2logs + " error:" + error.message ());
    }
  }
}


std::uint64_t
LogModule::fill_tab (
  const std::uint64_t len,
  const std::uint64_t max_count_tabs,
  const std::uint64_t uint64_tab)
{
  const std::uint64_t diff_tabs  = std::min< std::uint64_t > (len / uint64_tab, max_count_tabs);
  const std::uint64_t count_tabs = max_count_tabs - diff_tabs;

  for (std::uint64_t i = 0; i < count_tabs; ++i)
  {
    file_for_store_events_ << "\t";
  }
  return count_tabs;
}


void
LogModule::flush_events ()
{
  for (syn::IEvent::ptr& evnt : events_for_save_)
  {
    flush_event (evnt);
  }

  file_for_store_events_.flush ();
  events_for_save_.clear ();

  auto*      log_prop = ::libs::iproperties::helpers::cast_event< syn::PropertyLogModuleEvent > (appl_event_props_.module_log_);
  const auto max_size = log_prop->get_val (syn::LogVals::max_size_one_log_file_byte);

  if (max_size && file_for_store_events_.tellg () >= max_size)
  {
    ++indx_file_;
    file_for_store_events_.close ();
    open_log_file ();
  }
}


std::uint64_t
flush_long_descr_event (
  std::fstream&                    file,
  const syn::InfoLogEvent::raw_ptr cevnt)
{
  std::uint64_t ret = 0;
  std::string   txt;

  txt = cevnt->text (libs::ilog_events::LogTexts::file);
  ret += txt.length ();
  file << txt;

  file << ":";
  txt = cevnt->text (libs::ilog_events::LogTexts::line);
  ret += txt.length ();
  file << txt;

  // file << "  ";
  // txt = cevnt->text (libs::ilog_events::LogTexts::function);
  // ret += txt.length ();
  // file << txt;
  return ret;
}


void
LogModule::flush_event (syn::IEvent::ptr& evnt)
{
  std::string   txt;
  auto*         cevnt = ::libs::iproperties::helpers::cast_event< syn::InfoLogEvent > (evnt);
  std::uint64_t len   = 0;
  std::uint64_t tabs  = 0;

  txt = boost::posix_time::to_simple_string (cevnt->get_time ());
  len += txt.length ();
  file_for_store_events_ << txt;

  tabs += fill_tab (len, consts::g_max_count_tabs_date, consts::g_size_tab);

  txt = cevnt->text (::libs::ilog_events::LogTexts::subsys);
  len += txt.length ();
  file_for_store_events_ << txt;

  tabs += fill_tab (txt.length (), consts::g_max_count_tabs_subsys, consts::g_size_tab);

  txt = cevnt->text (::libs::ilog_events::LogTexts::level);
  len += txt.length ();
  file_for_store_events_ << txt;

  tabs += fill_tab (txt.length (), consts::g_max_count_tabs_level, consts::g_size_tab);

  {
    txt = cevnt->text (::libs::ilog_events::LogTexts::text);

    std::replace_if (
      txt.begin (), txt.end (), [] (const char& val) -> bool { return '\t' == val ? true : false; }, ' ');

    const std::uint64_t length_txt = txt.length ();
    const std::uint64_t max_symbol = consts::g_size_tab * (consts::g_max_count_tabs_info - 1);
    std::uint64_t       indx_first = 0;
    std::uint64_t       size_last  = 0;
    std::string         sub_txt;

    do
    {
      std::uint64_t indx_end = txt.find ('\n', indx_first);

      if (std::string::npos == indx_end)
      {
        indx_end = indx_first + max_symbol;
      }
      else
      {
        txt[indx_end++] = ' ';
      }

      indx_end = indx_end - indx_first > max_symbol ? indx_first + max_symbol : indx_end;
      sub_txt  = txt.substr (indx_first, std::min< std::uint64_t > (length_txt - indx_first, indx_end - indx_first));

      if (sub_txt.empty ())
      {
        break;
      }

      file_for_store_events_ << sub_txt;

      size_last = sub_txt.length ();
      indx_first += size_last;

      if (indx_first < length_txt)
      {
        file_for_store_events_ << '\n';
        tabs += fill_tab (0, consts::g_info_off_tabs, consts::g_size_tab);
      }
    } while (true);

    tabs += fill_tab (size_last, consts::g_max_count_tabs_info, consts::g_size_tab);
  }

  auto* log_prop = ::libs::iproperties::helpers::cast_event< syn::PropertyLogModuleEvent > (appl_event_props_.module_log_);
  if (log_prop->get_val (syn::LogVals::enable_store_call_place))
  {
    len += flush_long_descr_event (file_for_store_events_, cevnt);
  }

  file_for_store_events_ << '\n';
}
}   // namespace modules::mlog::appl
