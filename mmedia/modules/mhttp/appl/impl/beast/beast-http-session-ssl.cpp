/**
\file       beast-http-session.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       31.03.2026
\project    mhttp
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/
#include "../../../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "../../http-module-syn.hpp"

namespace modules::mhttp::impl::beast::adv
{
http_session_ssl::http_session_ssl (
  boost::asio::ip::tcp::socket&& socket,
  boost::asio::ssl::context&     ctx,
  const handler_func_type&       http_handler,
  const shared_state_ptr_type&   shared_state) :
  stream_ (std::move (socket), ctx),
  ctx_ (ctx),
  http_handler_ (http_handler),
  shared_state_ (shared_state)
{
  U3_XLOG_DEV ("http_session_ssl::http_session_ssl::on_create" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)));
  static_assert (modules::mhttp::appl::consts::queue_limit > 0, "queue limit must be positive");
}


void
http_session_ssl::run ()
{
  // We need to be executing within a strand to perform async operations
  // on the I/O objects in this session. Although not strictly necessary
  // for single-threaded contexts, this example code is written to be
  // thread-safe by default.
  boost::asio::dispatch (
    stream_.get_executor (),
    boost::beast::bind_front_handler (
      &http_session_ssl::on_run,
      this->shared_from_this ()));
}


void
http_session_ssl::on_run ()
{
  // Set the timeout.
  boost::beast::get_lowest_layer (stream_).expires_after (std::chrono::seconds (modules::mhttp::appl::consts::expires_after));

  // Perform the SSL handshake
  stream_.async_handshake (
    boost::asio::ssl::stream_base::server,
    boost::beast::bind_front_handler (
      &http_session_ssl::on_handshake,
      shared_from_this ()));
}


void
http_session_ssl::on_handshake (boost::beast::error_code ec)
{
  if (ec)
  {
    return fail (ec, "handshake");
  }
  do_read ();
}


void
http_session_ssl::do_read ()
{
  // Construct a new parser for each message
  parser_.emplace ();

  // Apply a reasonable limit to the allowed size
  // of the body in bytes to prevent abuse.
  parser_->body_limit (modules::mhttp::appl::consts::body_limit);

  // Make the request empty before reading,
  // otherwise the operation behavior is undefined.
  // EAI-!!!!!!!!!!!!!!!1
  // req_ = {};

  // Set the timeout.
  boost::beast::get_lowest_layer (stream_).expires_after (std::chrono::seconds (modules::mhttp::appl::consts::expires_after));
  // Read a request
  // EAI-!!!!!!!!!!!!!!!!!!!!!!!1
  // boost::beast::http::async_read (stream_, buf_, req_, boost::beast::bind_front_handler (&http_session_ssl::on_read, shared_from_this ()));

#ifdef U3_FAKE_DISABLE
  // Set the timeout.
  boost::beast::get_lowest_layer (stream_).expires_after (std::chrono::seconds (modules::mhttp::appl::consts::expires_after));

  // Perform the SSL handshake
  stream_.async_handshake (
    boost::asio::ssl::stream_base::server,
    boost::beast::bind_front_handler (
      &http_session_ssl::on_handshake,
      shared_from_this ()));
#endif
#if 1
  // Read a request using the parser-oriented interface
  boost::beast::http::async_read (
    stream_,
    buf_,
    *parser_,
    boost::beast::bind_front_handler (
      &http_session_ssl::on_read,
      shared_from_this ()));
#endif
}


void
http_session_ssl::on_read (boost::beast::error_code ec, std::size_t bytes_transferred)
{
  U3_XLOG_DBG ("http_session_ssl::on_read" + VTOLOG (bytes_transferred));
  boost::ignore_unused (bytes_transferred);

  // This means they closed the connection
  if (ec == boost::beast::http::error::end_of_stream)
  {
    return do_close ();
  }

  if (ec)
  {
    return fail (ec, "read");
  }

#if 1
  // See if it is a WebSocket Upgrade
  if (boost::beast::websocket::is_upgrade (parser_->get ()))
  {
    U3_XLOG_DEV ("http_session_ssl::on_read UPGRADE to websocket" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)));
    // Create a websocket session, transferring ownership
    // of both the socket and the HTTP request.
    std::make_shared< websocket_session_ssl > (
      std::move (stream_),
      // boost::beast::get_lowest_layer (stream_).release_socket (),
      //     stream_.release_socket (),
      ctx_,
      shared_state_)
      //->run (parser_->release ());
      ->do_accept (parser_->release ());
    return;
  }
#endif

  // EAI-!!!!!!!!!!!!!!!
  // send_response( handle_request(http_handler_, std::move(req_)));

#if 1
  // Send the response
  queue_write (handle_request (http_handler_, parser_->release ()));

  // If we aren't at the queue limit, try to pipeline another request
  if (response_queue_.size () < modules::mhttp::appl::consts::queue_limit)
  {
    do_read ();
  }
#endif
}


void
http_session_ssl::queue_write (boost::beast::http::message_generator response)
{
  // Allocate and store the work
  response_queue_.push (std::move (response));

  // If there was no previous work, start the write loop
  if (response_queue_.size () == 1)
  {
    do_write ();
  }
}


void
http_session_ssl::do_write ()
{
  if (!response_queue_.empty ())
  {
    bool keep_alive = response_queue_.front ().keep_alive ();

    boost::beast::async_write (
      stream_,
      std::move (response_queue_.front ()),
      boost::beast::bind_front_handler (
        &http_session_ssl::on_write,
        shared_from_this (),
        keep_alive));
  }
}


void
http_session_ssl::on_write (
  bool                     keep_alive,
  boost::beast::error_code ec,
  std::size_t              bytes_transferred)
{
  U3_XLOG_DBG ("http_session_ssl::on_write" + VTOLOG (bytes_transferred));
  boost::ignore_unused (bytes_transferred);

  if (ec)
  {
    return fail (ec, "write");
  }

  if (!keep_alive)
  {
    // This means we should close the connection, usually because
    // the response indicated the "Connection: close" semantic.
    return do_close ();
  }
  // Resume the read if it has been paused
  if (response_queue_.size () == modules::mhttp::appl::consts::queue_limit)
  {
    do_read ();
  }

  response_queue_.pop ();
  do_write ();
}


void
http_session_ssl::do_close ()
{
  U3_XLOG_DEV ("http_session_ssl::http_session_ssl::do_close" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)));

  // Set the timeout.
  boost::beast::get_lowest_layer (stream_).expires_after (std::chrono::seconds (30));

  // Perform the SSL shutdown
  stream_.async_shutdown (
    boost::beast::bind_front_handler (
      &http_session_ssl::on_shutdown,
      shared_from_this ()));

  // Send a TCP shutdown
  // boost::beast::error_code ec;
  // stream_.socket ().shutdown (boost::asio::ip::tcp::socket::shutdown_send, ec);
  // At this point the connection is closed gracefully
}


void
http_session_ssl::on_shutdown (boost::beast::error_code ec)
{
  if (ec)
  {
    return fail (ec, "shutdown");
  }
  // At this point the connection is closed gracefully
}
}   // namespace modules::mhttp::impl::beast::adv
