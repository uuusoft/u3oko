//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       leaf-module.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes_int.hpp"
#include "leaf-module.hpp"

namespace libs { namespace ilink { namespace appl { namespace leaf {

LeafModule::LeafModule ()
{}


LeafModule::~LeafModule ()
{}


void
LeafModule::update_catch_functs_int ()
{
  super::update_catch_functs_int ();

  catch_functs_.insert (
    std::make_pair (
      ::libs::events::ISeqEvent::gen_get_mid (),
      std::bind (&LeafModule::seq_msg_catch_funct, this, std::placeholders::_1, std::placeholders::_2)));

  catch_functs_.insert (
    std::make_pair (
      ::libs::events::ISyncEvent::gen_get_mid (),
      std::bind (&LeafModule::sync_msg_catch_funct, this, std::placeholders::_1, std::placeholders::_2)));

  catch_functs_.insert (
    std::make_pair (
      ::libs::events::IRequestEvent::gen_get_mid (),
      std::bind (&LeafModule::request_msg_catch_funct, this, std::placeholders::_1, std::placeholders::_2)));

  catch_functs_.insert (
    std::make_pair (
      ::libs::events::IAnswerEvent::gen_get_mid (),
      std::bind (&LeafModule::answer_msg_catch_funct, this, std::placeholders::_1, std::placeholders::_2)));

  catch_functs_.insert (
    std::make_pair (
      revents::state::ChangStateProcessTypeEvent::gen_get_mid (),
      [this](IEvent::ptr _msg, bool _forward) {
        if (_forward)
          {
            auto _state_cmd = ::libs::iproperties::helpers::cast_event<revents::state::ChangStateProcessTypeEvent> (_msg);
            if (!_state_cmd->is_start ())
              {
                stop_module_ = true;
              }
            return IEvent::ptr ();
          }
        return _msg;
      }));

  return;
}

}}}}      // namespace libs::ilink::appl::leaf
