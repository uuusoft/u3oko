/**
\file       state-process-event-ext.cpp
\date       02.03.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../libs-ilink-includes_int.hpp"
#include "libs-ilink-appl-includes_int.hpp"
#include "state-process-event-ext.hpp"

namespace libs::ilink::appl
{
StateProcessEventExt::StateProcessEventExt ()
{
}


StateProcessEventExt::~StateProcessEventExt ()
{
}


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
  ret += ", msg " + (obj.msg_ ? obj.msg_->get_mid () : "empty");
  return ret;
}
}   // namespace libs::ilink::appl
