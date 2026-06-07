#pragma once
/**
\file       beast-http-session.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.03.2026
\project    mhttp
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/

namespace modules::mhttp::impl::beast::adv
{
class http_session_ssl : public std::enable_shared_from_this< http_session_ssl >
{
  public:
  using parser_type         = boost::optional< boost::beast::http::request_parser< boost::beast::http::string_body > >;
  using response_queue_type = std::queue< boost::beast::http::message_generator >;
  // using stream_type         = boost::asio::ssl::stream< boost::beast::tcp_stream >;
  using stream_type = boost::beast::ssl_stream< boost::beast::tcp_stream >;
  //  using request_type        = boost::beast::http::request< boost::beast::http::string_body >;
  // using stream_type = boost::beast::tcp_stream;

  // Take ownership of the socket
  http_session_ssl (
    boost::asio::ip::tcp::socket&& socket,
    boost::asio::ssl::context&     ctx,
    const handler_func_type&       http_handler,
    const shared_state_ptr_type&   shared_state);

  void run ();

  private:
  void on_run ();
  void do_read ();
  void on_read (boost::beast::error_code ec, std::size_t bytes_transferred);
  void on_handshake (boost::beast::error_code ec);
  void queue_write (boost::beast::http::message_generator response);
  // Called to start/continue the write-loop. Should not be called when
  // write_loop is already active.
  void do_write ();
  void on_write (bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred);
  void do_close ();
  void on_shutdown (boost::beast::error_code ec);

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
