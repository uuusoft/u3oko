/**
\file       beast-listener.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       31.03.2026
\project    mhttp
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/
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
  boost::beast::error_code ec;

  acceptor_.open (endpoint.protocol (), ec);
  if (ec)
  {
    fail (ec, "open");
    return;
  }

  acceptor_.set_option (boost::asio::socket_base::reuse_address (true), ec);
  if (ec)
  {
    fail (ec, "set_option");
    return;
  }

  acceptor_.bind (endpoint, ec);
  if (ec)
  {
    fail (ec, "bind");
    return;
  }

  acceptor_.listen (boost::asio::socket_base::max_listen_connections, ec);
  if (ec)
  {
    fail (ec, "listen");
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
  // The new connection gets its own strand
  acceptor_.async_accept (
    boost::asio::make_strand (ioc_),
    boost::beast::bind_front_handler (
      &listener::on_accept,
      shared_from_this ()));
}

void
listener::on_accept (
  boost::beast::error_code     ec,
  boost::asio::ip::tcp::socket socket)
{
  if (ec)
  {
    fail (ec, "accept");
    return;   // To avoid infinite loop
  }

  U3_XLOG_DEV ("listener::on_accept" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)));
  // Create the session and run it
  if (ssl_enable_)
  {
    std::make_shared< selected_session_ssl_type > (
      std::move (socket),
      ctx_,
      http_handler_,
      shared_state_)
      ->run ();
  }
  else
  {
    std::make_shared< selected_session_type > (
      std::move (socket),
      // ctx_,
      http_handler_,
      shared_state_)
      ->run ();
  }

  // Accept another connection
  do_accept ();
}
}   // namespace modules::mhttp::impl::beast
