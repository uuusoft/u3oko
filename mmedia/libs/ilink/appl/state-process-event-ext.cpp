/**
\file       state-process-event-ext.cpp
\date       02.03.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/
#include "../libs-ilink-includes_int.hpp"
#include "libs-ilink-appl-includes_int.hpp"
#include "state-process-event-ext.hpp"

namespace libs::ilink::appl
{
void
StateProcessEventExt::reset ()
{
  super::reset ();
  source_.reset ();
  dest_.reset ();
}


std::string
to_string (const StateProcessEventExt& obj)
{
  std::string ret = ::libs::link::to_string (obj);
  ret += ", msg " + (obj.msg_ ? std::string { obj.msg_->get_mid () } : "empty");
  return ret;
}
}   // namespace libs::ilink::appl
