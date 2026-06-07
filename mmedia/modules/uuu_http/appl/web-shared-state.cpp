/**
\file       web-shared-state-module.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_http_module
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../module-http-includes_int.hpp"
#include "http-module-syn.hpp"
#include "web-shared-state.hpp"

namespace modules::uuu_http::appl
{
void
WebSharedState::join (session_type* session)
{
  std::scoped_lock lock (mutex_);
  sessions_.insert (session);
}

void
WebSharedState::leave (session_type* session)
{
  std::scoped_lock lock (mutex_);
  sessions_.erase (session);
}

void
WebSharedState::join (session_ssl_type* session)
{
  std::scoped_lock lock (mutex_);
  ssl_sessions_.insert (session);
}

void
WebSharedState::leave (session_ssl_type* session)
{
  std::scoped_lock lock (mutex_);
  ssl_sessions_.erase (session);
}

// Broadcast a message to all websocket client sessions
void
WebSharedState::broadcast_send (send_data_type&& message)
{
  // Put the message in a shared pointer so we can re-use it for each client
  const auto holdmessage = std::make_shared< send_data_type > (std::move (message));

  std::vector< std::weak_ptr< session_type > >     weakss;
  std::vector< std::weak_ptr< session_ssl_type > > ssl_weakss;

  {
    std::scoped_lock lock (mutex_);
    weakss.reserve (sessions_.size ());
    ssl_weakss.reserve (ssl_sessions_.size ());
    for (auto& p : sessions_)
    {
      weakss.emplace_back (p->weak_from_this ());
    }
    for (auto& p : ssl_sessions_)
    {
      ssl_weakss.emplace_back (p->weak_from_this ());
    }
  }

  // For each session in our local list, try to acquire a strong
  // pointer. If successful, then send the message on that session.
  U3_XLOG_DBG ("WebSharedState::send:begin" + VTOLOG (ssl_weakss.size ()) + VTOLOG (weakss.size ()) + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)))
  for (auto const& weaks : ssl_weakss)
  {
    if (auto wsk = weaks.lock ())
    {
      wsk->send (holdmessage);
    }
  }
  for (auto const& weaks : weakss)
  {
    if (auto wsk = weaks.lock ())
    {
      wsk->send (holdmessage);
    }
  }
  U3_XLOG_DBG ("WebSharedState::send:end" + VTOLOG (weakss.size ()) + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (this)))
}


std::int64_t
WebSharedState::get_size_pending_send () const
{
  std::int64_t                                     ret = 0;
  std::vector< std::weak_ptr< session_ssl_type > > weakss;
  std::scoped_lock                                 lock (mutex_);
  for (auto& p : ssl_sessions_)
  {
    ret += p->get_size_pending_send ();
  }
  return ret;
}
}   // namespace modules::uuu_http::appl
