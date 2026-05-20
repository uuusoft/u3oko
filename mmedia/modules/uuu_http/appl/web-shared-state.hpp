#pragma once
/**
\file       http-module.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_http_module
*/

namespace modules::uuu_http::impl::beast
{
class websocket_session_ssl;
class websocket_session;
}   // namespace modules::uuu_http::impl::beast

namespace modules::uuu_http::appl
{
class WebSharedState final
{
  public:
  // ext types
  using send_data_type           = std::vector< char >;
  using session_type             = modules::uuu_http::impl::beast::websocket_session;
  using sessions_holder_type     = std::unordered_set< session_type* >;
  using session_ssl_type         = modules::uuu_http::impl::beast::websocket_session_ssl;
  using ssl_sessions_holder_type = std::unordered_set< session_ssl_type* >;

  explicit WebSharedState ();

  void         join (session_ssl_type* session);
  void         leave (session_ssl_type* session);
  void         join (session_type* session);
  void         leave (session_type* session);
  void         broadcast_send (send_data_type&&);
  std::int64_t get_size_pending_send () const;

  private:
  mutable std::mutex       mutex_;          //<
  sessions_holder_type     sessions_;       //<
  ssl_sessions_holder_type ssl_sessions_;   //<
};

}   // namespace modules::uuu_http::appl
