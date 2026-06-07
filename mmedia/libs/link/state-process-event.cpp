/**
\file       state-process-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_link
*/
#include "libs-link-includes_int.hpp"
#include "state-process-event.hpp"

namespace libs::link
{
bool
StateProcessEvent::is_seq_exist () const
{
  return id_seq_.empty () ? false : true;
}


bool
StateProcessEvent::is_childs_exist () const
{
  return childs_.empty () ? false : true;
}


bool
StateProcessEvent::is_failed () const
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


std::string
to_string (const StateProcessEvent& val)
{
  return std::string ("StateProcessEvent[") +
         "sync_event:" + std::to_string (val.sync_event_) +
         "request:" + std::to_string (val.request_) +
         "answer:" + std::to_string (val.answer_) +
         "msg:" + val.msg_->get_mid () + "]";
}
}   // namespace libs::link
