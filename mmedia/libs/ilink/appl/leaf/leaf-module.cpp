/**
\file       leaf-module.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "leaf-module.hpp"

namespace libs::ilink::appl::leaf
{
LeafModule::LeafModule ()
{
}


LeafModule::~LeafModule ()
{
}


void
LeafModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_.insert (
    std::make_pair (
      ::libs::events::ISeqEvent::gen_get_mid (),
      std::bind (&LeafModule::seq_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));

  catch_funcs_.insert (
    std::make_pair (
      ::libs::events::ISyncEvent::gen_get_mid (),
      std::bind (&LeafModule::sync_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));

  catch_funcs_.insert (
    std::make_pair (
      ::libs::events::IRequestEvent::gen_get_mid (),
      std::bind (&LeafModule::request_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));

  catch_funcs_.insert (
    std::make_pair (
      ::libs::events::IAnswerEvent::gen_get_mid (),
      std::bind (&LeafModule::answer_msg_catch_func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));

  catch_funcs_.insert (
    std::make_pair (
      syn::ChangeStateProcessEvent::gen_get_mid (),
      [this] (::libs::events::IEvent::ptr& msg, bool forward, const StateProcessEventExt& process_state) {
        try
        {
          if (forward)
          {
            auto state_cmd = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
            if (!state_cmd->is_start ())
            {
              stop_module_ = true;
            }
            return ::libs::events::IEvent::ptr ();
          }
          return msg;
        }
        catch (const std::exception& e)
        {
          U3_LOG_APPL_EXCEPT (e.what ());
        }
        return ::libs::events::IEvent::ptr ();
      }));
}
}   // namespace libs::ilink::appl::leaf
