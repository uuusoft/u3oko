#pragma once
/**
\file       http-module.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mhttp
*/

namespace modules::mhttp::impl::beast
{
class websocket_session_ssl;
class websocket_session;
}   // namespace modules::mhttp::impl::beast

namespace modules::mhttp::appl
{
class WebSharedState final
{
  public:
  // ext types
  using send_data_type           = std::vector< char >;
  using session_type             = modules::mhttp::impl::beast::websocket_session;
  using sessions_holder_type     = boost::unordered_flat_set< session_type* >;
  using session_ssl_type         = modules::mhttp::impl::beast::websocket_session_ssl;
  using ssl_sessions_holder_type = boost::unordered_flat_set< session_ssl_type* >;

  explicit WebSharedState () = default;
  ~WebSharedState ()         = default;

  auto join (session_ssl_type* session) -> void;
  auto leave (session_ssl_type* session) -> void;
  auto join (session_type* session) -> void;
  auto leave (session_type* session) -> void;
  auto broadcast_send (send_data_type&&) -> void;
  auto get_size_pending_send () const -> std::int64_t;

  private:
  mutable std::mutex       mutex_;          //<
  sessions_holder_type     sessions_;       //<
  ssl_sessions_holder_type ssl_sessions_;   //<
};

}   // namespace modules::mhttp::appl
