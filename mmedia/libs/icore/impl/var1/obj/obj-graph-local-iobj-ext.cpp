/**
\file       obj-graph-local-iobj-ext.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\project    u3_icore_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../libs-icore-includes_int.hpp"
#include "../libs-icore-impl-var1-includes.hpp"
#include "obj-graph-local.hpp"

namespace libs::icore::impl::var1::obj
{
void
ObjGraph::stop_int ()
{
  state_ = obj::FilterRuns::stop;
  if (dfilter_)
  {
    dfilter_->stop ();
  }
}


void
ObjGraph::run_int ()
{
  state_ = obj::FilterRuns::run;
  if (dfilter_)
  {
    dfilter_->run ();
  }
}


void
ObjGraph::load_int (const ::pugi::xml_named_node_iterator& root)
{
  auto iappl = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
  U3_CHECK (iappl, "failed, empty appl");
  U3_CHECK (std::string ("node") == std::string (root->name ()), "failed, ivalide name arg");

  const pugi::xml_attribute name_attr = root->attribute ("name");
  U3_CHECK (!name_attr.empty (), "failed - empty name");

  const std::string file_path = ::libs::helpers::files::make_path (
    iappl->get_path (::libs::iproperties::appl_paths::Paths::bins),
    ::libs::helpers::dlls::decorate_dll_name (std::string (name_attr.as_string ())));

  iinfo_.lib_name_ = file_path;

  ObjGraph::load_lib (iinfo_.lib_name_, root);
}


void
ObjGraph::connect_int (int id_pt1, IGraphNodeExt::ptr& filter, int id_pt2)
{
  U3_ASSERT (filter.get ());
  auto rfilter = std::dynamic_pointer_cast< ObjGraph > (filter);
  U3_CHECK (rfilter, "failed, null filter");

  set_dst_connect (id_pt1, rfilter.get (), id_pt2);
  rfilter->set_src_connect (id_pt2, this, id_pt1);
}


void
ObjGraph::send_event2me_int (::libs::events::IEvent::ptr& info)
{
  U3_ASSERT (dfilter_);
  obj::dll::CallInterfInfo cinfo;

  cinfo.finfo_ = &info_;
  cinfo.event_ = info;

  if (dfilter_)
  {
    dfilter_->call (cinfo);
  }
}
}   // namespace libs::icore::impl::var1::obj
