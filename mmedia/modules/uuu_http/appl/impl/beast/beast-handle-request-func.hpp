#pragma once
/**
\file       beast-handle-request-func.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.03.2026
\project    u3_http_module
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/

namespace modules::uuu_http::impl::beast
{
using handler_data_type     = boost::beast::http::vector_body< char >;                                                //< data
using handler_func_res_type = std::tuple< handler_data_type::value_type, std::string, boost::beast::http::status >;   //< data + mime + status
using handler_func_type     = std::function< handler_func_res_type (const std::string&, const std::string&) >;        //< target + body (post)
using shared_state_type     = modules::uuu_http::appl::WebSharedState;                                                //<
using shared_state_ptr_type = std::shared_ptr< shared_state_type >;                                                   //<

template< class Body, class Allocator >
boost::beast::http::message_generator
handle_request (
  const handler_func_type&                                                             handler_func,
  boost::beast::http::request< Body, boost::beast::http::basic_fields< Allocator > >&& req)
{
  // Returns a bad request response
  auto const bad_request =
    [&req] (boost::beast::string_view why) {
      boost::beast::http::response< boost::beast::http::string_body > res { boost::beast::http::status::bad_request, req.version () };
      res.set (boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
      res.set (boost::beast::http::field::content_type, "text/html");
      res.keep_alive (req.keep_alive ());
      res.body () = std::string (why);
      res.prepare_payload ();
      return res;
    };
#ifdef U3_FAKE_DISABLE
  // Returns a not found response
  auto const not_found =
    [&req] (boost::beast::string_view target) {
      boost::beast::http::response< boost::beast::http::string_body > res { boost::beast::http::status::not_found, req.version () };
      res.set (boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
      res.set (boost::beast::http::field::content_type, "text/html");
      res.keep_alive (req.keep_alive ());
      res.body () = "The resource '" + std::string (target) + "' was not found.";
      res.prepare_payload ();
      return res;
    };
#endif
#ifdef U3_FAKE_DISABLE
  // Returns a server error response
  auto const server_error =
    [&req] (boost::beast::string_view what) {
      boost::beast::http::response< boost::beast::http::string_body > res { boost::beast::http::status::internal_server_error, req.version () };
      res.set (boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
      res.set (boost::beast::http::field::content_type, "text/html");
      res.keep_alive (req.keep_alive ());
      res.body () = "An error occurred: '" + std::string (what) + "'";
      res.prepare_payload ();
      return res;
    };
#endif
  // Make sure we can handle the method
  if (req.method () != boost::beast::http::verb::post &&
      req.method () != boost::beast::http::verb::get &&
      req.method () != boost::beast::http::verb::head)
  {
    U3_XLOG_DEV ("Unknown HTTP-method:1" + TOLOG (std::string (to_string (req.method ()))));
    return bad_request ("Unknown HTTP-method:1");
  }

  // Request path must be absolute and not contain "..".
  if (req.target ().empty () ||
      req.target ()[0] != '/' ||
      req.target ().find ("..") != boost::beast::string_view::npos)
  {
    U3_XLOG_DEV ("Illegal request-target");
    // return bad_request ("Illegal request-target");
  }

  auto       result = handler_func (req.target (), req.body ());
  auto const size   = std::get< 0 > (result).size ();

  // Respond to HEAD request
  if (req.method () == boost::beast::http::verb::head)
  {
    boost::beast::http::response< boost::beast::http::empty_body > res { boost::beast::http::status::ok, req.version () };
    res.set (boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set (boost::beast::http::field::content_type, std::get< 1 > (result));
    res.content_length (size);
    res.keep_alive (req.keep_alive ());
    return res;
  }

  if (req.method () == boost::beast::http::verb::get ||
      req.method () == boost::beast::http::verb::post)
  {
    boost::beast::http::response< handler_data_type > res {
      std::piecewise_construct,
      std::make_tuple (std::move (std::get< 0 > (result))),
      std::make_tuple (std::get< 2 > (result), req.version ())
    };

    U3_XLOG_DBG ("out (get/post)" + VTOLOG (size) + TOLOG (std::get< 1 > (result)) + VTOLOG (U3_CAST_UINT32_FORCE (std::get< 2 > (result))));
    res.set (boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set (boost::beast::http::field::content_type, std::get< 1 > (result));
    res.content_length (size);
    res.keep_alive (req.keep_alive ());
    return res;
  }
  U3_XLOG_DEV ("Unknown HTTP-method:2" + TOLOG (std::string (to_string (req.method ()))));
  return bad_request ("Unknown HTTP-method:2");
}

// Report a failure
inline void
fail (boost::beast::error_code ec, char const* what)
{
  U3_XLOG_ERROR ("fail http server: " + ec.message ());
}
}   // namespace modules::uuu_http::impl::beast
