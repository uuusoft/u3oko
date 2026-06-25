/**
\file       beast-listener.cpp
\author     Erashov Anton erashov2026@proton.me
\date       31.03.2026
\project    mhttp
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../../../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "../../http-module-syn.hpp"

namespace modules::mhttp::impl::beast
{
listener::listener (
  boost::asio::io_context&       ioc,
  boost::asio::ssl::context&     ctx,
  boost::asio::ip::tcp::endpoint endpoint,
  handler_func_type              http_handler,
  const shared_state_ptr_type&   shared_state) :
  ioc_ (ioc),
  ctx_ (ctx),
  acceptor_ (boost::asio::make_strand (ioc)),
  http_handler_ (http_handler),
  shared_state_ (shared_state),
  ssl_enable_ (endpoint.port () == appl::consts::ssl_port)
{
  U3_XLOG_DBG ("listener::listener");
  boost::beast::error_code ec;

  acceptor_.open (endpoint.protocol (), ec);
  if (ec)
  {
    u3beast_fail (ec, "listener::open");
    return;
  }

  acceptor_.set_option (boost::asio::socket_base::reuse_address (true), ec);
  if (ec)
  {
    u3beast_fail (ec, "listener::set_option");
    return;
  }

  acceptor_.bind (endpoint, ec);
  if (ec)
  {
    u3beast_fail (ec, "listener::bind");
    return;
  }

  acceptor_.listen (boost::asio::socket_base::max_listen_connections, ec);
  if (ec)
  {
    u3beast_fail (ec, "listener::listen");
    return;
  }
}


void
listener::run ()
{
  do_accept ();
}


void
listener::do_accept ()
{
  U3_XLOG_DBG ("listener::do_accept---->");
  // The new connection gets its own strand
  acceptor_.async_accept (
    boost::asio::make_strand (ioc_),
    boost::beast::bind_front_handler (
      &listener::on_accept,
      shared_from_this ()));
  U3_XLOG_DBG ("listener::do_accept<----");
}


void
listener::on_accept (
  boost::beast::error_code     ec,
  boost::asio::ip::tcp::socket socket)
{
  U3_XLOG_DBG ("listener::on_accept---->");
  if (ec)
  {
    u3beast_fail (ec, "listener::on_acceptaccept");
    return;   // To avoid infinite loop
  }

  U3_XLOG_DEV ("listener::on_accept" + PTR_TOLOG (this) + VTOLOG (ssl_enable_));
  // Create the session and run it
  if (ssl_enable_)
  {
    std::make_shared< selected_session_ssl_type > (
      std::move (socket), ctx_, http_handler_, shared_state_)
      ->run ();
  }
  else
  {
    std::make_shared< selected_session_type > (
      std::move (socket), http_handler_, shared_state_)
      ->run ();
  }

  // Accept another connection
  do_accept ();
}
}   // namespace modules::mhttp::impl::beast
