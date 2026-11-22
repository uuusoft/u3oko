#pragma once
/**
\file       beast-websocket-session.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.03.2026
\original   https://github.com/boostorg/beast/blob/develop/example/http/server/async/http_server_async.cpp
*/

namespace modules::mhttp::impl::beast
{
class websocket_session final : public std::enable_shared_from_this< websocket_session >
{
  public:
  using ws_stream_type         = appl::syn::websocket::stream< boost::beast::tcp_stream >;
  using send_data_type         = shared_state_type::send_data_type;
  using storage_send_data_type = std::vector< std::shared_ptr< const send_data_type > >;

  // Take ownership of the socket
  explicit websocket_session (boost::asio::ip::tcp::socket&&, shared_state_ptr_type);
  ~websocket_session ();

  // Start the asynchronous accept operation
  template< class Body, class Allocator >
  void do_accept (appl::syn::http::request< Body, appl::syn::http::basic_fields< Allocator > >);

  auto send (const std::shared_ptr< const send_data_type >&) -> void;
  auto get_size_pending_send () const -> std::int64_t;

  private:
  ws_stream_type              ws_;                        //<
  boost::beast::flat_buffer   buf_;                       //<
  shared_state_ptr_type       shared_state_;              //<
  storage_send_data_type      send_queue_;                //<
  std::atomic< std::int64_t > size_pending_send_ { 0 };   //<

  auto on_accept (boost::beast::error_code) -> void;
  auto do_read () -> void;
  auto on_read (boost::beast::error_code, std::size_t) -> void;
  auto on_write (boost::beast::error_code, std::size_t) -> void;
  auto on_send (const std::shared_ptr< const send_data_type >&) -> void;
};


// Start the asynchronous accept operation
template< class Body, class Allocator >
void
websocket_session::do_accept (appl::syn::http::request< Body, appl::syn::http::basic_fields< Allocator > > req)
{
  ws_.set_option (
    appl::syn::websocket::stream_base::timeout::suggested (
      boost::beast::role_type::server));

  // Set a decorator to change the Server of the handshake
  ws_.set_option (appl::syn::websocket::stream_base::decorator (
    [] (appl::syn::websocket::response_type& res) {
      res.set (appl::syn::http::field::server,
               std::string (BOOST_BEAST_VERSION_STRING) +
                 " advanced-server");
    }));

  // Accept the websocket handshake
  ws_.async_accept (
    req,
    boost::beast::bind_front_handler (
      &websocket_session::on_accept,
      shared_from_this ()));
}
}   // namespace modules::mhttp::impl::beast
