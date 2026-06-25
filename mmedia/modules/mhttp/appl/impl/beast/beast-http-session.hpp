#pragma once
/**
\file       beast-http-session.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.03.2026
\project    mhttp
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/

namespace modules::mhttp::impl::beast::adv
{
class http_session : public std::enable_shared_from_this< http_session >
{
  public:
  using parser_type         = boost::optional< appl::syn::http::request_parser< appl::syn::http::string_body > >;
  using response_queue_type = std::queue< appl::syn::http::message_generator >;

  // Take ownership of the socket
  http_session (
    boost::asio::ip::tcp::socket&& socket,
    const handler_func_type&       http_handler,
    const shared_state_ptr_type&   shared_state);

  void run ();

  private:
  void do_read ();
  void on_read (boost::beast::error_code ec, std::size_t bytes_transferred);
  void queue_write (appl::syn::http::message_generator response);
  // Called to start/continue the write-loop. Should not be called when
  // write_loop is already active.
  void do_write ();
  void on_write (bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred);
  void do_close ();

  private:
  boost::beast::tcp_stream  stream_;           //<
  boost::beast::flat_buffer buf_;              //<
  const handler_func_type&  http_handler_;     //<
  response_queue_type       response_queue_;   //<
  parser_type               parser_;           //<
  shared_state_ptr_type     shared_state_;     //<
};
}   // namespace modules::mhttp::impl::beast::adv
