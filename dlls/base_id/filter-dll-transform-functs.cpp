//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-transform-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_base_id_dll
\brief      empty brief.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace base_id {

void
Filter::transform_int (TransformInfo& _info)
{
  prepare_transform (_info);

  auto _events = _info.pframe_events_;
  UASSERT (_events);

  if (!send_base_interf_)
    {
      XULOG_TRACE ("Filter::transform_int: send base inteface");
      IEvent::ptr _rmsg;
      auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::interf::InterfBaseIdEvent> (_rmsg);
      _dmsg->set_interface (base_interf_);
      _dmsg->set_active (true);
      _events->push_back (_rmsg);
      send_base_interf_ = true;
    }

  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      return;
    }
  ++counter_frames_;
  return;
}

}}      // namespace dlls::base_id
