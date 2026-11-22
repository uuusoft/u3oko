#pragma once
/**
\file       beast-http-session.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.03.2026
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/

namespace modules::mhttp::impl::beast::adv
{
class http_session_ssl : public std::enable_shared_from_this< http_session_ssl >
{
  public:
  using parser_type         = boost::optional< appl::syn::http::request_parser< appl::syn::http::string_body > >;
  using response_queue_type = std::queue< appl::syn::http::message_generator >;
  using stream_type         = boost::beast::ssl_stream< boost::beast::tcp_stream >;

  // Take ownership of the socket
  http_session_ssl (
    boost::asio::ip::tcp::socket&& socket,
    boost::asio::ssl::context&     ctx,
    const handler_func_type&       http_handler,
    shared_state_ptr_type          shared_state);

  auto run () -> void;

  private:
  auto on_run () -> void;
  auto do_read () -> void;
  auto on_read (boost::beast::error_code, std::size_t) -> void;
  auto on_handshake (boost::beast::error_code) -> void;
  auto queue_write (appl::syn::http::message_generator) -> void;
  // Called to start/continue the write-loop. Should not be called when
  // write_loop is already active.
  auto do_write () -> void;
  auto on_write (bool, boost::beast::error_code, std::size_t) -> void;
  auto do_close () -> void;
  auto on_shutdown (boost::beast::error_code) -> void;

  private:
  stream_type                stream_;           //<
  boost::beast::flat_buffer  buf_;              //<
  const handler_func_type&   http_handler_;     //<
  response_queue_type        response_queue_;   //<
  parser_type                parser_;           //<
  shared_state_ptr_type      shared_state_;     //<
  boost::asio::ssl::context& ctx_;              //<
};
}   // namespace modules::mhttp::impl::beast::adv
