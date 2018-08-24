//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       path-local-ipath-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "../includes.hpp"
#include "../../../xml/includes.hpp"
#include "path.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 { namespace path {

void
Path::load_int (const std::string& _xml_file)
{
  UASSERT (!_xml_file.empty ());
  guard_type _grd (ctrl_mtx_);
  auto       _iappl = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_appl_paths_lockfree ();

  xml_path_.reset ();

  CHECK_STATE (_iappl, "failed, empty application");

  ::libs::icore::xml::TInitInfo _helper_info (_iappl);
  ::libs::icore::xml::Loader    _helper_xml (_helper_info);

  ::libs::icore::xml::helpers::load_xml (&_helper_xml, _xml_file, TypePath::data_xml, xml_path_);

  base_functs::xml::ritn _range_nodes = xml_path_.root ().children ("path");

  load_impl (_range_nodes.begin ());
  return;
}


const Path::array_id_objs_type&
Path::get_objs_int () const
{
  guard_type _grd (ctrl_mtx_);
  return id_objs_;
}


void
Path::send_event2obj_int (const PathObjID& _id_obj, events::IEvent::ptr& _evnt)
{
  UASSERT (_evnt);
  guard_type _grd (ctrl_mtx_);

  recv_special_event_impl (_evnt);

  if (!_id_obj.check ())
    {
      // такое бывает, когда используется сообщение для всего потока обработки данных. Надо бы скорректировать.
      return;
    }

  auto _find_obj = id2obj_.find (_id_obj);
  if (id2obj_.end () == _find_obj)
    {
      UASSERT_SIGNAL ("failed find obj path by id");
      return;
    }

  _find_obj->second->send_event2me (_evnt);
  return;
}


void
Path::set_logger_int (::libs::link::ILink::weak_ptr _ptr)
{
  logger_ = _ptr;
  return;
}

}}}}}      // namespace libs::icore::impl::var1::path
