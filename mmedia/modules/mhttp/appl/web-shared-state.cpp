/**
\file       web-shared-state-module.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "-http-module-includes-int.hpp"
#include "-http-module-syn.hpp"
#include "web-shared-state.hpp"

namespace modules::mhttp::appl
{
auto
WebSharedState::join (session_type* session) -> void
{
  std::scoped_lock lock (mutex_);
  sessions_.insert (session);
}


auto
WebSharedState::leave (session_type* session) -> void
{
  std::scoped_lock lock (mutex_);
  sessions_.erase (session);
}


auto
WebSharedState::join (session_ssl_type* session) -> void
{
  std::scoped_lock lock (mutex_);
  ssl_sessions_.insert (session);
}


auto
WebSharedState::leave (session_ssl_type* session) -> void
{
  std::scoped_lock lock (mutex_);
  ssl_sessions_.erase (session);
}

// Broadcast a message to all websocket client sessions
auto
WebSharedState::broadcast_send (send_data_type&& message) -> void
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
}


auto
WebSharedState::get_size_pending_send () const -> std::int64_t
{
  std::int64_t                                     ret = 0;
  std::vector< std::weak_ptr< session_ssl_type > > weakss;

  std::scoped_lock lock (mutex_);
  for (auto& p : ssl_sessions_)
  {
    ret += p->get_size_pending_send ();
  }
  return ret;
}
}   // namespace modules::mhttp::appl
