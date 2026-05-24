/**
\file       leaf-module-catch-funcs.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "leaf-module.hpp"

namespace libs::ilink::appl::leaf
{
::libs::events::IEvent::ptr
LeafModule::default_catch_func (
  ::libs::events::IEvent::ptr&                     msg,
  bool                                             forward,
  const ::libs::ilink::appl::StateProcessEventExt& process_state)
{
  return ::libs::events::IEvent::ptr ();
}
}   // namespace libs::ilink::appl::leaf
