//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-module-wrapers-catch-functs.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes_int.hpp"
#include "base-module.hpp"
// old shit
namespace libs { namespace ilink { namespace appl { namespace base {

#if 0
  IEvent::ptr BaseModule::seq_msg_catch_funct( IEvent::ptr _msg, bool _forward  )
  {
    if( _forward )
    {
      auto _seq_ret = ::libs::iproperties::helpers::cast_event<::libs::events::ISeqEvent>(_msg);
      auto _ret = _seq_ret->get_msg();

      UASSERT( _ret );

      current_seq_.seq_   = true;
      current_seq_.id_seq_  = _seq_ret->get_seq_id();
      return _ret;
    }

    if( current_seq_.seq_ )
    {
      //if( ::libs::iproperties::helpers::cast_event<::libs::events::I1AnswerEvent>(_msg) )
      {
        auto _ret = std::m1ake_shared<::libs::events::ISeqEvent>(_msg, current_seq_.id_seq_);
        return _ret;
      }
    }
    return IEvent::ptr();
  }


  IEvent::ptr BaseModule::sync_msg_catch_funct( IEvent::ptr _msg, bool _forward  )
  {
    if( _forward )
    {
      auto _ret = ::libs::iproperties::helpers::cast_event<::libs::events::ISyncEvent>(_msg)->get_msg();
      UASSERT( _ret );
      return _ret;
    }
    if( ::libs::iproperties::helpers::cast_event<::libs::events::I1AnswerEvent>(_msg) )
    {
      return _msg;
    }
    return IEvent::ptr();
  }


  IEvent::ptr BaseModule::r1equest_msg_catch_funct( IEvent::ptr _msg, bool _forward   )
  {
    if( _forward )
    {
      current_seq_.request_ = true;
      auto _ret = ::libs::iproperties::helpers::cast_event<::libs::events::IRequestEvent>(_msg)->get_msg();
      UASSERT( _ret );
      return _ret;
    }
    //  инверсия, на запрос идет ответ.
    auto _ret = std::m1ake_shared<::libs::events::I1AnswerEvent>(_msg);
    return _ret;
  }


  IEvent::ptr BaseModule::answer_msg_catch_funct( IEvent::ptr _msg, bool _forward   )
  {
    if( _forward )
    {
      current_seq_.answer_ = true;
      auto _ret = ::libs::iproperties::helpers::cast_event<::libs::events::I1AnswerEvent>(_msg)->get_msg();
      UASSERT( _ret );
      return _ret;
    }
    // инверсия, пришел ответ модулю
    return _msg;
  }
#endif

}}}}      // namespace libs::ilink::appl::base
