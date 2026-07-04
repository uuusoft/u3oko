/**
\file       state-process-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
*/
#include "libs-link-includes_int.hpp"
#include "state-process-event.hpp"

namespace libs::link
{
auto
StateProcessEvent::is_seq_exist () const -> bool
{
  return id_seq_.empty () ? false : true;
}


auto
StateProcessEvent::is_childs_exist () const -> bool
{
  return childs_.empty () ? false : true;
}


auto
StateProcessEvent::is_failed () const -> bool
{
  return failed_;
}


void
StateProcessEvent::reset ()
{
  sync_event_ = false;
  request_    = false;
  recv_seq_   = false;
  make_seq_   = false;
  answer_     = false;
  failed_     = false;

  msg_.reset ();
  id_seq_.reset ();
  childs_.clear ();
  error_text_.clear ();
}


void
StateProcessEvent::update (::libs::events::IEvent::ptr& msg)
{
  msg_ = msg;
}


auto
to_string (const StateProcessEvent& val) -> std::string
{
  return std::string ("StateProcessEvent[") +
         "sync_event:" + std::to_string (val.sync_event_) +
         "request:" + std::to_string (val.request_) +
         "answer:" + std::to_string (val.answer_) +
         "msg:" + (val.msg_ ? std::string { val.msg_->get_mid () } : "empty msg_") + "]";
}
}   // namespace libs::link
