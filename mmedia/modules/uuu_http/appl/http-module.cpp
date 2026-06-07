/**
\file       http-module.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_http_module
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../module-http-includes_int.hpp"
#include "http-module-syn.hpp"
#include "http-module.hpp"

namespace modules::uuu_http::appl
{
HttpModule::HttpModule ()
{
  try
  {
    isys_      = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ());
    auto iappl = isys_->get_paths_lockfree ();

    resource_loader_ = std::make_shared< syn::Loader > (::libs::iproperties::xml::InitLoaderInfo (iappl));
    text_id_module_  = ::libs::ilink::consts::id_http;
    shared_state_    = std::make_shared< WebSharedState > ();
  }
  catch (const std::exception& e)
  {
    U3_LOG_HTTP_EXCEPT (e.what ());
  }
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
  const auto path2res = ::libs::helpers::files::make_path (temp_folder_, std::string (appl::consts::id_zip_buf2http));

  ::libs::helpers::files::load_file2mem (path2res, bufs.buf_);

  bufs.off_data_       = 0;
  bufs.number_frame_   = 0;
  bufs.counter_frames_ = 0;
}


void
HttpModule::delete_rw_copy ()
{
  if (temp_folder_.empty ())
  {
    return;
  }
  //  Удаляем старые временные данные.
  if (::libs::helpers::files::is_folder (temp_folder_))
  {
    ::libs::helpers::files::delete_folder (temp_folder_);
  }

  temp_folder_.clear ();
}


void
HttpModule::prepare_resources ()
{
  delete_rw_copy ();
  create_rw_copy ();
  load_def_resource2mem ();
}


void
HttpModule::create_rw_copy ()
{
  auto       iappl    = isys_->get_paths_lockfree ();
  const auto temppath = iappl->get_path (libs::iproperties::appl_paths::Paths::temp);

  temp_folder_ = ::libs::helpers::files::make_path (temppath, consts::temp_folder_name);

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
  try
  {
    if (!props->is_start ())
    {
      U3_LOG_HTTP_MARK ("stop http module");
      stop_module_ = true;
      stop_http_server ();
      return;
    }

    U3_LOG_HTTP_MARK ("start http module");
    stop_http_server ();
    run_http_server ();
  }
  catch (const std::exception& e)
  {
    U3_LOG_HTTP_EXCEPT (e.what ());
  }
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

    const auto off_data  = helpers::get_offset_iframe (buf.data ());
    const auto source_id = props->get_id ();
    auto       tempbuf   = std::vector< char > { buf.data (), buf.data () + buf.size () };
    U3_CHECK (off_data <= 255, "off_data <= 255" + VTOLOG (off_data));
    U3_CHECK (U3_CAST_INT32 (source_id.length ()) <= off_data, "source_id.length () <= off_data" + VTOLOG (source_id.length ()) + VTOLOG (off_data));
    U3_CHECK (source_id.length () <= 253, "source_id.length () <= 253" + VTOLOG (source_id.length ()));
    constexpr std::uint32_t count_sizes = 2;

    tempbuf[0] = off_data;
    tempbuf[1] = source_id.length ();
    std::copy (source_id.begin (), source_id.end (), tempbuf.data () + count_sizes);
    shared_state_->broadcast_send (std::move (tempbuf));
  }
  catch (const std::exception& e)
  {
    U3_LOG_HTTP_EXCEPT (e.what ());
  }
}


void
HttpModule::debug ()
{
#if 1
  return;
#else
  {
    std::string      content;
    syn::IEvent::ptr rmsg = std::make_shared< ::libs::ievents::TimedEvent > ();
    ::libs::iproperties::helpers::event2xml (rmsg, content);
  }
  {
    std::string      content;
    syn::IEvent::ptr rmsg;

    auto dmsg = ::libs::iproperties::helpers::create_event< ::libs::ievents::TimedEvent > (rmsg);
    ::libs::iproperties::helpers::event2xml (rmsg, content);
  }
#endif
}


HttpModule::process_res_type
HttpModule::process_http_request (const std::string& req, const std::string& body)
{
  // events
  if (std::regex_match (req, std::regex ("^/string$")))
  {
    U3_LOG_HTTP_DBG ("process_request_event for" + TOLOG (req) + TOLOG (body));
    return process_request_event (req, body);
  }
#ifdef U3_FAKE_DISABLE
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


bool
HttpModule::process_request_event_debug (
  const std::string& id_event,
  const std::string& content,
  const std::string& id_data)
{
#if 1
  return false;
#else
  if ("libs/ihttp_events/events/mem-resource-http-event" == id_event)
  {
    return false;
  }
  if (::libs::imdata_events::events::ListDevicesDataEvent::gen_get_mid () == id_event)
  {
    U3_LOG_HTTP_DEV (TOLOG (id_event) + TOLOG (content) + TOLOG (id_data));
    return true;
  }
  return false;
#endif
}


HttpModule::process_res_type
HttpModule::process_request_event (const std::string&, const std::string& body)
{
  boost::beast::http::status bstatus = boost::beast::http::status::ok;

  std::string content;
  std::string id_event;
  std::string recv_event_data;
  std::string mime = "text/plain";

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

    U3_CHECK (helpers::url_decode (url_id_event, id_event), "URL decode id event, " + url_id_event);
    U3_CHECK (helpers::url_decode (url_xml_event, recv_event_data), "URL decode utrl, " + url_xml_event);
    const auto enable_debug = process_request_event_debug (id_event, content, id_data);
    if (enable_debug)
    {
      U3_LOG_HTTP_DEV ("post " + ::libs::link::details::to_string (type_request) + TOLOG (url_id_event) + TOLOG (id_event));
      U3_LOG_HTTP_DEV ("post" + TOLOG (recv_event_data) + VTOLOG (xml_type_data));
    }

    auto idemons    = ::libs::iproperties::helpers::cast_prop_demons ();
    auto ievents    = idemons->get_events_lockfree ();
    auto recv_event = ievents->impl ()->get (id_event);
    U3_CHECK (recv_event, "null decode event" + TOLOG (id_event));
    U3_CHECK (id_event == recv_event->get_mid (), id_event + "!=" + recv_event->get_mid ());

    if (syn::Calls::generate == type_request)
    {
      // запрос на генерацию события (в данном случае это http клиент, поэтому на генерацию xml схемы события) удовлетворяем сразу.
      content = xml_type_data ? ::libs::iproperties::helpers::event2xml (recv_event) : recv_event->save_json ();
    }
    else
    {
      if (!recv_event_data.empty ())
      {
        if (xml_type_data)
        {
          U3_CHECK (::libs::iproperties::helpers::xml2event (recv_event_data, recv_event), "convert to event" + TOLOG (recv_event_data));
        }
        else
        {
          recv_event->load_json (recv_event_data);
        }
      }

      syn::IEvent::ptr send_event;
      //  Если сообщение можно обработать внутри htpp сервера делаем это без пересылки в другие модули.
      auto finger2intfunc = int_catch_funcs_.find (recv_event->get_mid ());
      if (int_catch_funcs_.end () != finger2intfunc)
      {
        send_event = finger2intfunc->second (recv_event, true, current_seq_);
      }

      //  аче пересылаем сообщение в основной модуль системы, запросы всегда синхронные
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
      if (enable_debug)
      {
        U3_LOG_HTTP_DEV (TOLOG (content));
      }
    }
  }
  catch (const std::exception& e)
  {
    U3_LOG_HTTP_EXCEPT (e.what () + TOLOG (recv_event_data) + TOLOG (content));
    content.clear ();
    bstatus = boost::beast::http::status::internal_server_error;
  }
  return { std::vector< char > (content.begin (), content.end ()), mime, bstatus };
}


std::string
get_resource_id_from_query (const std::string& query)
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


HttpModule::process_res_type
HttpModule::process_request_file (const std::string& req, const std::string& body)
{
  lock_type                                  lock (mtx_);
  impl::beast::handler_data_type::value_type mem;
  boost::beast::http::status                 bstatus = boost::beast::http::status::ok;

  std::string mime     = "text/html";
  auto        req_path = req.substr (0, req.find ('?'));

  if ("/" == req_path)
  {
    req_path = consts::index_html_id;
  }

  std::string full_path;
  try
  {
    full_path = ::libs::helpers::files::make_path (consts::temp_folder_name, req_path);

    auto       iappl     = isys_->get_paths_lockfree ();
    const auto dir_path  = iappl->get_path (::libs::iproperties::appl_paths::Paths::temp);
    const auto file_path = ::libs::helpers::files::make_path (dir_path, full_path);

    ::libs::helpers::files::load_file2mem (file_path, mem);
    if (mem.empty ())
    {
      bstatus = boost::beast::http::status::not_found;
    }
    else
    {
      const auto ext = std::filesystem::path (file_path).extension ();
      mime           = helpers::file_ext2mime (ext.string ());
    }
  }
  catch (const std::exception& e)
  {
    U3_LOG_HTTP_EXCEPT (e.what ());
    bstatus = boost::beast::http::status::bad_request;
  }
  return { mem, mime, bstatus };
}


void
HttpModule::run_http_server ()
{
  prepare_resources ();
  debug ();

  impl_thread_ = std::thread (
    [this] () -> void {
      try
      {
        const auto                address  = boost::asio::ip::make_address ("0.0.0.0");
        const auto                endpoint = boost::asio::ip::tcp::endpoint { address, consts::port };
        boost::asio::io_context   ioc { consts::count_work_threads };
        boost::asio::ssl::context ctx { boost::asio::ssl::context::tlsv12 };

        impl_ = std::make_shared< impl::beast::listener > (
          ioc,
          ctx,
          endpoint,
          modules::uuu_http::impl::beast::handler_func_type (
            std::bind (&HttpModule::process_http_request, this, std::placeholders::_1, std::placeholders::_2)),
          shared_state_);

        impl_->run ();

        work_threads_.reserve (consts::count_work_threads);

        for (auto i = consts::count_work_threads; i > 0; --i)
          work_threads_.emplace_back (
            [&ioc] {
              ioc.run ();
            });

        ioc.run ();
      }
      catch (const std::exception& e)
      {
        U3_LOG_HTTP_EXCEPT (e.what ());
      }
    });
#if 1
  ssl_impl_thread_ = std::thread (
    [this] () -> void {
      try
      {
        const auto                address  = boost::asio::ip::make_address ("0.0.0.0");
        const auto                endpoint = boost::asio::ip::tcp::endpoint { address, consts::ssl_port };
        boost::asio::io_context   ioc { consts::count_work_threads };
        boost::asio::ssl::context ctx { boost::asio::ssl::context::tlsv12 };

        // This holds the self-signed certificate used by the server
        load_server_certificate (ctx);

        impl_ = std::make_shared< impl::beast::listener > (
          ioc,
          ctx,
          endpoint,
          modules::uuu_http::impl::beast::handler_func_type (
            std::bind (&HttpModule::process_http_request, this, std::placeholders::_1, std::placeholders::_2)),
          shared_state_);

        impl_->run ();

        ssl_work_threads_.reserve (consts::count_work_threads);

        for (auto i = consts::count_work_threads; i > 0; --i)
          ssl_work_threads_.emplace_back (
            [&ioc] {
              ioc.run ();
            });

        ioc.run ();
      }
      catch (const std::exception& e)
      {
        U3_LOG_HTTP_EXCEPT (e.what ());
      }
    });
#endif
}


void
HttpModule::stop_http_server ()
{
  skip_state_.reset ();

  // EAI-BOOST-BEAST
  // work_threads_???
  // impl_.stop ();
}
}   // namespace modules::uuu_http::appl
