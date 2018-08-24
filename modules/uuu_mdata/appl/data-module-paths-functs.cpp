//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       data-module-paths-functs.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_data
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "data-module.hpp"

namespace modules { namespace uuu_mdata { namespace appl {

DataModule::ptr_path_type
DataModule::get_path (const id_path_type& _id)
{
  UASSERT (!_id.empty ());
  auto _val = idatas_.find (_id);
  if (_val != idatas_.end ())
    {
      return _val->second;
    }
  return DataModule::ptr_path_type ();
}


void
DataModule::send_msg2path (const id_path_type& _id, ::libs::events::IEvent::ptr _msg)
{
  auto _wdata = get_path (_id);
  auto _idata = _wdata.lock ();

  if (!_idata)
    {
      UASSERT_SIGNAL ("try start empty data path");
      return;
    }

  const auto _id_objs = _idata->get_objs ();
  for (const auto& _id_obj : _id_objs)
    {
      _idata->send_event2obj (_id_obj, _msg);
    }
  return;
}


void
DataModule::update_cpu_path (const id_path_type& _id)
{
  auto                        _idemons = ::libs::iproperties::helpers::cast_prop_demons ();
  ISharedProperty::guard_type _guard (_idemons->get_sync ());
  auto                        _ioptim   = _idemons->get_optim_lockfree ()->impl ();
  auto                        _wdata    = get_path (_id);
  auto                        _idata    = _wdata.lock ();
  auto                        _info_cpu = ::libs::iproperties::helpers::cast_event<::libs::ievents::props::hardware::InfoCPUEvent> (event_props_.info_cpu_);
  TInit                       _upi;

  _upi.ext_ = _info_cpu->get_type ();
  _ioptim->update (_upi);

  if (!_idata)
    {
      XULOG_INFO ("try use empty data path, " << _id);
      return;
    }
  send_msg2path (_id, event_props_.info_cpu_);
  return;
}


void
DataModule::delete_path (const id_path_type& _id)
{
  auto _wdata = get_path (_id);
  if (_wdata.expired ())
    {
      return;
    }

  UASSERT (1 == _wdata.use_count ());
  icore_->delete_path (_wdata);
  idatas_.erase (_id);
  return;
}


void
DataModule::make_path (const std::string& _name_xml)
{
  DATA_LOG (std::string ("Create data path from: " + _name_xml));
  CHECK_STATE (!_name_xml.empty (), "failed, try make data path from empty xml file");

  delete_path (_name_xml);
  idatas_[_name_xml] = icore_->create_path ();

  auto _idata = idatas_[_name_xml].lock ();

  CHECK_STATE (_idata, "failed, return empty path");
  _idata->set_logger (logger_);

  //  При загрузке пути допустимы не критичные исключения, связанные с ошибками в xml пути.
  try
    {
      _idata->load (_name_xml);
    }
  catch (const std::exception& _e)
    {
      EXCEPT_LOG (logger_, _e.what (), text_id_module_.c_str ());
    }
  return;
}


void
DataModule::start_path (const id_path_type& _id)
{
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
  _dmsg->set_start (true);
  send_msg2path (_id, _rmsg);
  return;
}


void
DataModule::stop_path (const id_path_type& _id)
{
  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_rmsg);
  _dmsg->set_start (false);
  send_msg2path (_id, _rmsg);
  return;
}

}}}      // namespace modules::uuu_mdata::appl
