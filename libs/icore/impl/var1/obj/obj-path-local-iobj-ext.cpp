//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       obj-path-local-iobj-ext.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "../includes.hpp"
#include "obj-path-local.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {

void
ObjPath::stop_int ()
{
  state_ = obj::RunStateFilter::stop;
  return;
}


void
ObjPath::run_int ()
{
  state_ = obj::RunStateFilter::run;
  return;
}


void
ObjPath::load_int (const base_functs::xml::itn& _root)
{
  auto _iappl = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_appl_paths_lockfree ();

  CHECK_STATE (_iappl, "failed, empty _appl");
  CHECK_STATE (std::string ("node") == std::string (_root->name ()), "failed, ivalide name arg");

  const pugi::xml_attribute _name_attr = _root->attribute ("name");

  CHECK_STATE (!_name_attr.empty (), "failed - empty name");

  const std::string file_path = ::libs::helpers::files::make_path (
    _iappl->get_path (::libs::iproperties::appl_paths::TypePath::bins),
    ::utils::mem_functs::files::decorate_dll_name (std::string (_name_attr.as_string ())));

  iinfo_.lib_name_ = file_path;

  ObjPath::load_lib (iinfo_.lib_name_, _root);
  return;
}


void
ObjPath::connect_int (int id_pt1, IPathObjExt::ptr& filter, int id_pt2)
{
  UASSERT (filter.get ());
  auto _rfilter = std::dynamic_pointer_cast<ObjPath> (filter);
  CHECK_STATE (_rfilter, "failed, null filter");

  set_dst_connect (id_pt1, _rfilter.get (), id_pt2);
  _rfilter->set_src_connect (id_pt2, this, id_pt1);
  return;
}


void
ObjPath::send_event2me_int (::libs::events::IEvent::ptr& _info)
{
  UASSERT (dfilter_);

  obj::dll::CallInterfInfo _cinfo;

  _cinfo.finfo_ = &info_;
  _cinfo.event_ = _info;

  dfilter_->call (_cinfo);
  return;
}

}}}}}      // namespace libs::icore::impl::var1::obj
