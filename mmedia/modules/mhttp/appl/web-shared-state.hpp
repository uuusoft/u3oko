#pragma once
/**
\file       http-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  using sessions_holder_type     = std::unordered_set< session_type* >;
  using session_ssl_type         = modules::mhttp::impl::beast::websocket_session_ssl;
  using ssl_sessions_holder_type = std::unordered_set< session_ssl_type* >;

  explicit WebSharedState () = default;
  ~WebSharedState ()         = default;

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

}   // namespace modules::mhttp::appl
