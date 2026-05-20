#pragma once
/**
\file       beast-websocket-session.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.03.2026
\project    u3_http_module
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/

namespace modules::uuu_http::impl::beast
{
class websocket_session_ssl final : public std::enable_shared_from_this< websocket_session_ssl >
{
  public:
  // using ws_stream_type = boost::beast::websocket::stream< boost::beast::tcp_stream >;
  using ws_stream_type = boost::beast::websocket::stream< boost::beast::ssl_stream< boost::beast::tcp_stream > >;
  using stream_type    = boost::beast::ssl_stream< boost::beast::tcp_stream >;
  // using stream_type = boost::asio::ip::tcp::socket;
  //  using stream_type    = boost::asio::ssl::stream< boost::beast::tcp_stream >;
  using send_data_type = shared_state_type::send_data_type;

  // Take ownership of the socket
  explicit websocket_session_ssl (
    stream_type&&                socket,
    boost::asio::ssl::context&   ctx,
    const shared_state_ptr_type& shared_state);

  ~websocket_session_ssl ();

  // Start the asynchronous accept operation
  template< class Body, class Allocator >
  void do_accept (boost::beast::http::request< Body, boost::beast::http::basic_fields< Allocator > > req);

  template< class Body, class Allocator >
  void run (boost::beast::http::request< Body, boost::beast::http::basic_fields< Allocator > > req);

  void on_run ();
  void on_handshake (boost::beast::error_code ec);

  void         send (const std::shared_ptr< const send_data_type >& ss);
  std::int64_t get_size_pending_send () const;

  private:
  ws_stream_type                                         ws_;                  //<
  boost::beast::flat_buffer                              buf_;                 //<
  shared_state_ptr_type                                  shared_state_;        //<
  std::vector< std::shared_ptr< const send_data_type > > send_queue_;          //<
  std::atomic< std::int64_t >                            size_pending_send_;   //<
  boost::asio::ssl::context&                             ctx_;                 //<

  void on_accept (boost::beast::error_code ec);
  void do_read ();
  void on_read (boost::beast::error_code ec, std::size_t bytes_transferred);
  void on_write (boost::beast::error_code ec, std::size_t bytes_transferred);
  void on_send (const std::shared_ptr< const send_data_type >& ss);
};


template< class Body, class Allocator >
void
websocket_session_ssl::run (boost::beast::http::request< Body, boost::beast::http::basic_fields< Allocator > > req)
{
  // U3_XLOG_DEV ("websocket_session_ssl::do_accept");
  //  Set suggested timeout settings for the websocket
  ws_.set_option (
    boost::beast::websocket::stream_base::timeout::suggested (
      boost::beast::role_type::server));

  // Set a decorator to change the Server of the handshake
  ws_.set_option (boost::beast::websocket::stream_base::decorator (
    [] (boost::beast::websocket::response_type& res) {
      res.set (boost::beast::http::field::server,
               std::string (BOOST_BEAST_VERSION_STRING) +
                 " advanced-server");
    }));

  // Accept the websocket handshake
#if 0  
  ws_.async_accept (
    req,
    boost::beast::bind_front_handler (
      &websocket_session_ssl::on_accept,
      shared_from_this ()));
#endif
  // We need to be executing within a strand to perform async operations
  // on the I/O objects in this session. Although not strictly necessary
  // for single-threaded contexts, this example code is written to be
  // thread-safe by default.
  boost::asio::dispatch (ws_.get_executor (),
                         boost::beast::bind_front_handler (
                           &websocket_session_ssl::on_run,
                           shared_from_this ()));
}


// Start the asynchronous accept operation
template< class Body, class Allocator >
void
websocket_session_ssl::do_accept (boost::beast::http::request< Body, boost::beast::http::basic_fields< Allocator > > req)
{
  // U3_XLOG_DEV ("websocket_session_ssl::do_accept");
  //  Set suggested timeout settings for the websocket
  ws_.set_option (
    boost::beast::websocket::stream_base::timeout::suggested (
      boost::beast::role_type::server));

  // Set a decorator to change the Server of the handshake
  ws_.set_option (boost::beast::websocket::stream_base::decorator (
    [] (boost::beast::websocket::response_type& res) {
      res.set (boost::beast::http::field::server,
               std::string (BOOST_BEAST_VERSION_STRING) +
                 " advanced-server");
    }));

  // Accept the websocket handshake
  ws_.async_accept (
    req,
    boost::beast::bind_front_handler (
      &websocket_session_ssl::on_accept,
      shared_from_this ()));
}
}   // namespace modules::uuu_http::impl::beast
