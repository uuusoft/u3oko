#pragma once
/**
\file       beast-listener.hpp
\author     Erashov Anton erashov2026@proton.me
\date       13.03.2026
\project    u3_http_module
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/

namespace modules::uuu_http::impl::beast
{
using selected_session_ssl_type = adv::http_session_ssl;
using selected_session_type     = adv::http_session;

class listener : public std::enable_shared_from_this< listener >
{
  public:
  listener (
    boost::asio::io_context&       ioc,
    boost::asio::ssl::context&     ctx,
    boost::asio::ip::tcp::endpoint endpoint,
    handler_func_type              http_handler,
    const shared_state_ptr_type&   shared_state);

  // Start accepting incoming connections
  void run ();

  private:
  boost::asio::io_context&       ioc_;
  boost::asio::ssl::context&     ctx_;
  boost::asio::ip::tcp::acceptor acceptor_;
  const handler_func_type        http_handler_;
  shared_state_ptr_type          shared_state_;
  bool                           ssl_enable_ = true;

  void do_accept ();
  void on_accept (boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
};
}   // namespace modules::uuu_http::impl::beast
