/**
\file       http-module.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mhttp
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../module-http-includes_int.hpp"
#include "http-module-syn.hpp"
#include "http-module.hpp"

namespace modules::mhttp::appl
{
HttpModule::HttpModule ()
{
  U3_XLOG_DBG ("HttpModule::HttpModule::---->");
  try
  {
    isys_ = ::libs::iproperties::helpers::get_shared_prop_os ();

    auto iappl = isys_->get_paths_lockfree ();

    resource_loader_ = std::make_shared< syn::Loader > (::libs::iproperties::xml::InitLoaderInfo (iappl));
    text_id_module_  = ::libs::ilink::consts::id_http;
    shared_state_    = std::make_shared< WebSharedState > ();
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_HTTP_EXCEPT (excpt.what ());
  }
  U3_XLOG_DBG ("HttpModule::HttpModule::<----");
}


void
HttpModule::check_process ()
{
}


void
HttpModule::load_def_resource2mem ()
{
  //  Загружаем данные по умолчанию из хранилища.
  auto&      bufs     = shared_ids2bufs_[appl::consts::id_zip_buf2http];
  const auto path2res = ::libs::utility::files::make_path (temp_folder_, std::string (appl::consts::id_zip_buf2http));

  ::libs::utility::files::load_file2mem (path2res, bufs.buf_);

  bufs.off_data_       = 0;
  bufs.number_frame_   = 0;
  bufs.counter_frames_ = 0;
}


void
HttpModule::delete_rw_copy ()
{
  U3_XLOG_DBG ("HttpModule::delete_rw_copy::---->");
  if (!temp_folder_.empty ())
  {
    //  Удаляем старые временные данные.
    if (::libs::utility::files::is_folder (temp_folder_))
    {
      ::libs::utility::files::delete_folder (temp_folder_);
    }
    temp_folder_.clear ();
  }
  U3_XLOG_DBG ("HttpModule::delete_rw_copy::<----");
}


void
HttpModule::prepare_resources ()
{
  U3_XLOG_DBG ("HttpModule::prepare_resources::---->");
  delete_rw_copy ();
  create_rw_copy ();
  load_def_resource2mem ();
  U3_XLOG_DBG ("HttpModule::prepare_resources::<----");
}


void
HttpModule::create_rw_copy ()
{
  auto       iappl    = isys_->get_paths_lockfree ();
  const auto temppath = iappl->get_path (libs::iproperties::appl_paths::Paths::temp);

  temp_folder_ = ::libs::utility::files::make_path (temppath, consts::temp_folder_name);

  U3_LOG_HTTP_MARK ("copy http resources to a temporary folder" + TOLOG (temp_folder_));
  ::libs::iproperties::xml::helpers::copy_files (
    *resource_loader_,
    libs::iproperties::appl_paths::Paths::templates_http_module,
    "",
    temp_folder_);
}


void
HttpModule::process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr props)
{
  U3_XLOG_DBG ("HttpModule::process_change_state_process::---->");
  try
  {
    if (!props->is_start ())
    {
      U3_LOG_HTTP_MARK ("stop http module");
      stop_http_server ();
      stop_module_ = true;
    }
    else
    {
      U3_LOG_HTTP_MARK ("start http module");
      // stop_http_server ();
      start_http_server ();
    }
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_HTTP_EXCEPT (excpt.what ());
  }
  U3_XLOG_DBG ("HttpModule::process_change_state_process::<----");
}


void
HttpModule::process_zip_data_event (syn::ZipDataEvent::raw_ptr props)
{
  try
  {
    auto       buf          = props->get_zip ();
    const auto sending_size = shared_state_->get_size_pending_send ();
    if (sending_size >= consts::max_size_sending_data)
    {
      const auto now = std::chrono::high_resolution_clock::now ();
      skip_state_.skip_send_bytes_ += sending_size;
      ++skip_state_.skip_send_request_;
      if (now - skip_state_.last_send_time_ >= consts::inform_period_about_skip_data)
      {
        skip_state_.last_send_time_ = now;
        U3_LOG_HTTP_WRN ("max size limit send data1" + VTOLOG (sending_size) + VTOLOG (consts::max_size_sending_data));
        U3_LOG_HTTP_WRN ("max size limit send data2" + VTOLOG (skip_state_.skip_send_request_) + VTOLOG (skip_state_.skip_send_bytes_));
      }
      U3_CHECK (U3_CAST_INT64 (buf.size ()) <= consts::max_size_sending_data, "max sending size too small" + VTOLOG (buf.size ()) + VTOLOG (consts::max_size_sending_data));
      return;
    }

    const auto  off_data  = helpers::get_offset_iframe (buf.data ());
    const auto& source_id = props->get_id ();
    auto        tempbuf   = std::vector< char > { buf.data (), buf.data () + buf.size () };
    U3_CHECK (off_data <= 255, "off_data <= 255" + VTOLOG (off_data));
    U3_CHECK (U3_CAST_INT32 (source_id.length ()) <= off_data, "source_id.length () <= off_data" + VTOLOG (source_id.length ()) + VTOLOG (off_data));
    U3_CHECK (source_id.length () <= 253, "source_id.length () <= 253" + VTOLOG (source_id.length ()));
    constexpr std::uint32_t count_sizes = 2;

    tempbuf[0] = off_data;
    tempbuf[1] = source_id.length ();
    std::ranges::copy (source_id, tempbuf.data () + count_sizes);
    shared_state_->broadcast_send (std::move (tempbuf));
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_HTTP_EXCEPT (excpt.what ());
  }
}


void
HttpModule::debug ()
{
}


auto
HttpModule::process_http_request (const std::string& req, const std::string& body) -> HttpModule::process_res_type
{
  U3_XLOG_DBG ("HttpModule::process_http_request::---->" + TOLOG (req));
  // events
  if (std::regex_match (req, std::regex ("^/string$")))
  {
    U3_LOG_HTTP_DBG ("process_request_event for" + TOLOG (req) + TOLOG (body));
    return process_request_event (req, body);
  }
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // runtime data
  if (std::regex_match (req, std::regex ("^/mem_resource.*")))
  {
    U3_LOG_HTTP_DBG ("process_request_memory for" + TOLOG (req) + TOLOG (body));
    return process_request_memory (req, body);
  }
#endif
  // files
  return process_request_file (req, body);
}


auto
HttpModule::process_request_event_debug (
  const std::string& id_event,
  const std::string& content,
  const std::string& id_data) -> bool
{
  if ("libs/events_http/events/mem-resource-http-event" == id_event)
  {
    return false;
  }
  // if (::libs::events_media::events::ListDevicesDataEvent::gen_get_mid () == id_event)
  if (::libs::events_msg::events::GetEventsFromBase::gen_get_mid () == id_event)
  {
    // U3_LOG_HTTP_DEV (TOLOG (id_event) + TOLOG (content) + TOLOG (id_data));
    // return true;
  }
  return false;
}


auto
HttpModule::process_request_event (const std::string&, const std::string& body) -> HttpModule::process_res_type
{
  U3_XLOG_DBG ("HttpModule::process_request_event::---->");
  syn::http::status bstatus = syn::http::status::ok;

  std::string mime = "text/plain";
  std::string content;
  std::string id_event;
  std::string event_data;

  try
  {
    content = helpers::http2json (body);

    std::stringstream           strcontent (content);
    boost::property_tree::ptree pt;

    boost::property_tree::read_json (strcontent, pt);

    const auto url_id_event   = pt.get< std::string > ("id_event", "/libs/events/event");
    const auto id_data        = pt.get< std::string > ("id_data", "xml");
    const auto url_xml_event  = pt.get< std::string > ("event");
    const auto url_id_request = pt.get< std::string > ("id_request", "request");
    const auto type_request   = ::libs::link::details::to_request (url_id_request);
    const auto xml_type_data  = "xml" == id_data ? true : false;

    U3_CHECK_NT (!xml_type_data, "xml_type_data rised!")
    U3_CHECK (helpers::url_decode (url_id_event, id_event), "URL decode id event, " + url_id_event);
    U3_CHECK (helpers::url_decode (url_xml_event, event_data), "URL decode utrl, " + url_xml_event);

    const auto dbg_enable = process_request_event_debug (id_event, content, id_data);
    if (dbg_enable)
    {
      U3_LOG_HTTP_DEV ("post " + ::libs::link::details::to_string (type_request) + TOLOG (url_id_event) + TOLOG (id_event));
      U3_LOG_HTTP_DEV ("post" + TOLOG (event_data) + VTOLOG (xml_type_data));
    }

    auto idemons     = ::libs::iproperties::helpers::cast_prop_demons ();
    auto events_base = idemons->get_events_lockfree ();
    auto recv_event  = events_base->impl ()->get (id_event);

    U3_CHECK (recv_event, "null decode event" + STOLOG (id_event));
    U3_CHECK (id_event == recv_event->get_mid (), id_event + "!=" + STOLOG (recv_event->get_mid ()));

    if (syn::Calls::generate == type_request)
    {
      // запрос на генерацию события (в данном случае это http клиент, поэтому на генерацию xml схемы события) удовлетворяем сразу.
      content = xml_type_data ? ::libs::iproperties::helpers::event2xml (recv_event) : recv_event->save_json ();
    }
    else
    {
      if (!event_data.empty ())
      {
        if (xml_type_data)
        {
          U3_CHECK (::libs::iproperties::helpers::xml2event (event_data, recv_event), "convert to event" + TOLOG (event_data));
        }
        else
        {
          recv_event->load_json (event_data);
        }
      }

      syn::IEvent::ptr send_event;
      //  Если сообщение можно обработать внутри htpp сервера делаем это без пересылки в другие модули.
      auto ffinger = int_catch_funcs_.find (recv_event->get_mid ());
      if (int_catch_funcs_.end () != ffinger)
      {
        send_event = ffinger->second (recv_event, true, current_seq_);
      }
      // Иначе пересылаем сообщение в основной модуль системы, запросы всегда синхронные
      if (!send_event)
      {
        const auto call_type = (type_request == syn::Calls::request) ? syn::CallSyncs::sync : syn::CallSyncs::async;
        send_event           = links_.get (syn::mids::http2appl)->send_msg (recv_event, call_type, type_request);
      }

      content.clear ();
      if (send_event)
      {
        content = xml_type_data ? ::libs::iproperties::helpers::event2xml (send_event) : send_event->save_json ();
      }
      if (dbg_enable)
      {
        U3_LOG_HTTP_DEV (TOLOG (content));
      }
    }
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_HTTP_EXCEPT (excpt.what () + TOLOG (id_event));
    U3_LOG_HTTP_MARK (TOLOG (event_data));
    content.clear ();
    bstatus = syn::http::status::internal_server_error;
  }
  return { std::vector< char > (content.begin (), content.end ()), mime, bstatus };
}


auto
get_resource_id_from_query (const std::string& query) -> std::string
{
  const auto beg = query.find ('?');
  const auto end = query.rfind ('?');

  if (std::string::npos == beg ||
      std::string::npos == end ||
      end <= beg)
  {
    return appl::consts::id_zip_buf2http;
  }
  return query.substr (beg + 1, end - beg - 1);
}


auto
HttpModule::process_request_file (const std::string& req, const std::string& body) -> HttpModule::process_res_type
{
  U3_XLOG_DBG ("HttpModule::process_request_file::---->");
  lock_type lock (mtx_);

  impl::beast::handler_data_type::value_type mem;
  syn::http::status                          bstatus = syn::http::status::ok;

  std::string mime     = "text/html";
  auto        req_path = req.substr (0, req.find ('?'));

  if ("/" == req_path)
  {
    req_path = consts::index_html_id;
  }

  std::string full_path;
  try
  {
    full_path = ::libs::utility::files::make_path (consts::temp_folder_name, req_path);

    auto       iappl     = isys_->get_paths_lockfree ();
    const auto dir_path  = iappl->get_path (::libs::iproperties::appl_paths::Paths::temp);
    const auto file_path = ::libs::utility::files::make_path (dir_path, full_path);

    ::libs::utility::files::load_file2mem (file_path, mem);
    if (mem.empty ())
    {
      bstatus = syn::http::status::not_found;
    }
    else
    {
      const auto ext = std::filesystem::path (file_path).extension ();
      mime           = helpers::file_ext2mime (ext.string ());
    }
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_HTTP_EXCEPT (excpt.what ());
    bstatus = syn::http::status::bad_request;
  }
  return { mem, mime, bstatus };
}


void
HttpModule::start_http_server ()
{
  U3_XLOG_DBG ("HttpModule::start_http_server::---->");
  prepare_resources ();
  debug ();

  impl_state_.impl_thread_ = std::thread (
    [this] () -> void {
      U3_XLOG_DEV ("HttpModule::start_http_server::thread---->");
      try
      {
        const auto address  = boost::asio::ip::make_address ("0.0.0.0");
        const auto endpoint = boost::asio::ip::tcp::endpoint { address, consts::port };

        impl_state_.impl_ = std::make_shared< impl::beast::listener > (
          impl_state_.ioc_,
          impl_state_.ctx_,
          endpoint,
          modules::mhttp::impl::beast::handler_func_type (
            [this] (auto&& ph1, auto&& ph2) {
              return process_http_request (std::forward< decltype (ph1) > (ph1), std::forward< decltype (ph2) > (ph2));
            }),
          shared_state_);

        impl_state_.impl_->run ();
        impl_state_.work_threads_.reserve (consts::count_work_threads);

        for (auto i = consts::count_work_threads; i > 0; --i)
        {
          impl_state_.work_threads_.emplace_back (
            [this] -> void {
              impl_state_.ioc_.run ();
            });
        }

        impl_state_.ioc_.run ();
      }
      catch (const std::exception& excpt)
      {
        U3_LOG_HTTP_EXCEPT (excpt.what ());
      }
      U3_XLOG_DEV ("HttpModule::start_http_server::thread<----");
    });

#if 0
  impl_ssl_thread_ = std::thread (
    [this] () -> void {
      U3_XLOG_DEV ("HttpModule::start_http_server::sslthread---->");
      try
      {
        const auto                address  = boost::asio::ip::make_address ("0.0.0.0");
        const auto                endpoint = boost::asio::ip::tcp::endpoint { address, consts::ssl_port };
        boost::asio::io_context   ioc { consts::count_work_threads };
        boost::asio::ssl::context ctx { boost::asio::ssl::context::tlsv12 };

        // This holds the self-signed certificate used by the server
        load_server_certificate (ctx);

        ssl_impl_ = std::make_shared< impl::beast::listener > (
          ioc,
          ctx,
          endpoint,
          modules::mhttp::impl::beast::handler_func_type (
            std::bind (&HttpModule::process_http_request, this, std::placeholders::_1, std::placeholders::_2)),
          shared_state_);

        impl_ssl_->run ();

        ssl_work_threads_.reserve (consts::count_work_threads);

        for (auto i = consts::count_work_threads; i > 0; --i)
        {
          ssl_work_threads_.emplace_back (
            [&ioc_] {
              ioc_.run ();
            });
        }

        ioc_.run ();
      }
      catch (const std::exception& excpt)
      {
        U3_LOG_HTTP_EXCEPT (excpt.what ());
      }
      U3_XLOG_DEV ("HttpModule::start_http_server::sslthread<----");
    });
#endif
  U3_XLOG_DBG ("HttpModule::start_http_server::<----");
}


void
HttpModule::stop_http_server ()
{
  U3_XLOG_DEV ("HttpModule::stop_http_server::---->");
  skip_state_.reset ();

  // EAI-BOOST-BEAST
  // work_threads_???
  // impl_.stop ();
  if (impl_state_.impl_)
  {
    impl_state_.ioc_.stop ();
    U3_XLOG_DEV ("wait stop impl http thread");
    impl_state_.impl_thread_.join ();
  }
  U3_XLOG_DEV ("HttpModule::stop_http_server::<----");
}
}   // namespace modules::mhttp::appl
