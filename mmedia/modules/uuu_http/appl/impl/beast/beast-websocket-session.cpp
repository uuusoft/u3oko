/**
\file       beast-websocket-session.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       31.03.2026
\project    u3_http_module
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/
#include "../../../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "../../http-module-syn.hpp"

namespace modules::uuu_http::impl::beast
{
websocket_session::websocket_session (
  boost::asio::ip::tcp::socket&& socket,
  // const handler_func_type&       ws_handler,
  const shared_state_ptr_type& shared_state) :

  ws_ (std::move (socket)),
  // ws_handler_ (ws_handler),
  shared_state_ (shared_state),
  size_pending_send_ (0)
{
  U3_XLOG_DEV ("websocket_session::on_create" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)));
}


websocket_session::~websocket_session ()
{
  U3_XLOG_DEV ("websocket_session::o_destroy" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)));
  // Remove this session from the list of active sessions
  shared_state_->leave (this);
}


void
websocket_session::on_accept (boost::beast::error_code ec)
{
  U3_XLOG_DEV ("websocket_session::on_accept" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)));
  if (ec)
  {
    return fail (ec, "accept");
  }

  shared_state_->join (this);
  // Read a message
  do_read ();
}


void
websocket_session::do_read ()
{
  // Read a message into our buf
  ws_.async_read (
    buf_,
    boost::beast::bind_front_handler (
      &websocket_session::on_read,
      shared_from_this ()));
}


void
websocket_session::on_read (boost::beast::error_code ec, std::size_t bytes_transferred)
{
  // U3_XLOG_DEV ("websocket_session::on_read" + VTOLOG (bytes_transferred));
  boost::ignore_unused (bytes_transferred);
  // This indicates that the websocket_session was closed
  if (ec == boost::beast::websocket::error::closed)
  {
    return;
  }
  if (ec)
  {
    return fail (ec, "read");
  }
  // Send to all connections
  // shared_state_->send(beast::bufs_to_string(buf_.data()));

  // Clear the buf
  buf_.consume (buf_.size ());

  // Read another message
  ws_.async_read (
    buf_,
    boost::beast::bind_front_handler (
      &websocket_session::on_read,
      shared_from_this ()));
}


void
websocket_session::send (const std::shared_ptr< const send_data_type >& ss)
{
  // Post our work to the strand, this ensures
  // that the members of `this` will not be
  // accessed concurrently.
  size_pending_send_ += U3_CAST_INT64 (ss->size ());

  boost::asio::post (
    ws_.get_executor (),
    boost::beast::bind_front_handler (
      &websocket_session::on_send,
      shared_from_this (),
      ss));
}


void
websocket_session::on_send (const std::shared_ptr< const send_data_type >& ss)
{
  // Always add to queue
  send_queue_.push_back (ss);

  // Are we already writing?
  if (send_queue_.size () > 1)
  {
    return;
  }

  ws_.binary (true);
  // We are not currently writing, so send this immediately
  ws_.async_write (
    boost::asio::buffer (*send_queue_.front ()),
    boost::beast::bind_front_handler (
      &websocket_session::on_write,
      shared_from_this ()));
}


void
websocket_session::on_write (
  boost::beast::error_code ec,
  std::size_t              bytes_transferred)
{
  // U3_XLOG_DEV ("websocket_session::on_write" + VTOLOG (bytes_transferred));
  //  boost::ignore_unused (bytes_transferred);
  if (ec)
  {
    return fail (ec, "write");
  }

  // Remove from the queue
  if (!send_queue_.empty ())
  {
    size_pending_send_ -= U3_CAST_INT64 (send_queue_.front ()->size ());
    U3_CHECK (size_pending_send_ >= 0, "invalid pending data size" + VTOLOG (size_pending_send_) + VTOLOG (bytes_transferred));
    send_queue_.erase (send_queue_.begin ());
  }

  // Send the next message if any
  if (!send_queue_.empty ())
  {
    // ws_.binary (true);
    ws_.async_write (
      boost::asio::buffer (*send_queue_.front ()),
      boost::beast::bind_front_handler (
        &websocket_session::on_write,
        shared_from_this ()));
  }
}


std::int64_t
websocket_session::get_size_pending_send () const
{
  return size_pending_send_;
}
}   // namespace modules::uuu_http::impl::beast
