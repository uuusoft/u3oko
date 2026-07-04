/**
\file       beast-http-session.cpp
\author     Erashov Anton erashov2026@proton.me
\date       31.03.2026
\project    mhttp
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../../../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "../../http-module-syn.hpp"

namespace modules::mhttp::impl::beast::adv
{
http_session::http_session (
  boost::asio::ip::tcp::socket&& socket,
  const handler_func_type&       http_handler,
  shared_state_ptr_type          shared_state) :
  stream_ (std::move (socket)),
  http_handler_ (http_handler),
  shared_state_ (std::move (shared_state))
{
  U3_XLOG_DEV ("http_session::http_session::on_create" + VTOLOG (::libs::utility::casts::reinterpret_cast_helper< std::uint64_t > (this)));
  static_assert (modules::mhttp::appl::consts::requests_queue_limit > 0, "queue limit must be positive");
}


void
http_session::run ()
{
  // We need to be executing within a strand to perform async operations
  // on the I/O objects in this session. Although not strictly necessary
  // for single-threaded contexts, this example code is written to be
  // thread-safe by default.
  boost::asio::dispatch (
    stream_.get_executor (),
    boost::beast::bind_front_handler (
      &http_session::do_read,
      this->shared_from_this ()));
}


void
http_session::do_read ()
{
  // Construct a new parser for each message
  parser_.emplace ();

  // Apply a reasonable limit to the allowed size
  // of the body in bytes to prevent abuse.
  parser_->body_limit (modules::mhttp::appl::consts::body_limit);

  // Set the timeout.
  stream_.expires_after (std::chrono::seconds (modules::mhttp::appl::consts::expires_after));

  // Read a request using the parser-oriented interface
  appl::syn::http::async_read (
    stream_,
    buf_,
    *parser_,
    boost::beast::bind_front_handler (
      &http_session::on_read,
      shared_from_this ()));
}


void
http_session::on_read (boost::beast::error_code ec, std::size_t bytes_transferred)
{
  U3_XLOG_DBG ("http_session::on_read" + VTOLOG (bytes_transferred));
  boost::ignore_unused (bytes_transferred);

  // This means they closed the connection
  if (ec == appl::syn::http::error::end_of_stream)
  {
    return do_close ();
  }

  if (ec)
  {
    return u3beast_fail (ec, "http_session::read");
  }

  // See if it is a WebSocket Upgrade
  if (appl::syn::websocket::is_upgrade (parser_->get ()))
  {
    U3_XLOG_DEV ("http_session::on_read UPGRADE to websocket" + VTOLOG (::libs::utility::casts::reinterpret_cast_helper< std::uint64_t > (this)));
    // Create a websocket session, transferring ownership
    // of both the socket and the HTTP request.
    std::make_shared< websocket_session > (
      stream_.release_socket (),
      // ws_handler_,
      shared_state_)
      ->do_accept (parser_->release ());
    return;
  }

  // Send the response
  queue_write (handle_request (http_handler_, parser_->release ()));

  // If we aren't at the queue limit, try to pipeline another request
  if (response_queue_.size () < modules::mhttp::appl::consts::requests_queue_limit)
  {
    do_read ();
  }
}


void
http_session::queue_write (appl::syn::http::message_generator response)
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
http_session::do_write ()
{
  if (!response_queue_.empty ())
  {
    bool keep_alive = response_queue_.front ().keep_alive ();

    boost::beast::async_write (
      stream_,
      std::move (response_queue_.front ()),
      boost::beast::bind_front_handler (
        &http_session::on_write,
        shared_from_this (),
        keep_alive));
  }
}


void
http_session::on_write (
  bool                     keep_alive,
  boost::beast::error_code ec,
  std::size_t              bytes_transferred)
{
  U3_XLOG_DBG ("http_session::on_write" + VTOLOG (bytes_transferred));
  boost::ignore_unused (bytes_transferred);

  if (ec)
  {
    return u3beast_fail (ec, "http_session::write");
  }

  if (!keep_alive)
  {
    // This means we should close the connection, usually because
    // the response indicated the "Connection: close" semantic.
    return do_close ();
  }

  // Resume the read if it has been paused
  if (response_queue_.size () == modules::mhttp::appl::consts::requests_queue_limit)
  {
    do_read ();
  }

  response_queue_.pop ();

  do_write ();
}


void
http_session::do_close ()
{
  U3_XLOG_DEV ("http_session::http_session::do_close" + VTOLOG (::libs::utility::casts::reinterpret_cast_helper< std::uint64_t > (this)));
  // Send a TCP shutdown
  boost::beast::error_code ec;
  stream_.socket ().shutdown (boost::asio::ip::tcp::socket::shutdown_send, ec);
  // At this point the connection is closed gracefully
}
}   // namespace modules::mhttp::impl::beast::adv
