/**
\file       obj-graph-local.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       22.12.2016
\project    u3_icore_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../libs-icore-includes_int.hpp"
#include "../libs-icore-impl-var1-includes.hpp"
#include "mmedia/libs/proxy/proxy/icore-proxy.hpp"
#include "obj-graph-local.hpp"

namespace libs::icore::impl::var1::obj
{
::libs::helpers::dlls::ForeverLoadDlls ObjGraph::frozen_dlls_;

ObjGraph::ObjGraph (
  const ::libs::core::graph::IGraph*         pparent,
  const ::libs::core::graph::NodeID&         id_obj,
  ::libs::link::ILink::weak_ptr              logger,
  ::libs::helpers::statistic::ExpandedTimes& expand_objs_algoritm_time) :

  pparent_ (pparent),
  state_ (obj::FilterRuns::stop),
  pf_create_ (0),
  logger_ (logger),
  exptimes_ (expand_objs_algoritm_time)
{
  info_.id_obj_ = id_obj;
}


ObjGraph::~ObjGraph ()
{
  state_ = obj::FilterRuns::stop;
  ObjGraph::free_lib ();
}


std::string
make_name_function_for_data_path_library (
  const std::string& lib_name,
  const std::string& prefix_funct)
{
  return prefix_funct + "_" + libs::helpers::dlls::undecorate_dll_name (lib_name);
}


void
ObjGraph::load_lib (
  const std::string&                     name_lib,
  const ::pugi::xml_named_node_iterator& node)
{
  try
  {
#ifdef U3_BUILD_MODULES_AS_LIBS
    pf_create_ = ::libs::proxy::get_create_data_path_module_funct (::libs::helpers::files::get_name_from_path (name_lib));
#else
    lib_.load (name_lib, boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);

#  if defined(U3_OS_ANDROID)
    lib_name_ = name_lib;
#  else
    lib_name_ = lib_.location ().filename ().string ();
#  endif

#  if defined(U3_OS_ANDROID)
    pf_create_ = reinterpret_cast< obj::dll::create_impl_func_type* > (dlsym (lib_.native (), make_name_function_for_data_path_library (lib_name_, obj::consts::name_func_create).c_str ()));
#  else
    pf_create_ = boost::dll::import_symbol< obj::dll::create_impl_func_type > (
      lib_,
      make_name_function_for_data_path_library (lib_name_, obj::consts::name_func_create));
#  endif
#endif

    U3_CHECK (pf_create_, "empty create function data path object");
    //  регистриуем свои данные в DLL
    dfilter_.reset (pf_create_ ());
    dfilter_->load (&info_, node);
    info_.correct ();

#ifndef U3_BUILD_MODULES_AS_LIBS
    // Пока отключено удаление.
    // Удерживаем в памяти все загруженные единожды модули обработки данных. Их не много, а удалять их пока нельзя из-за нерешенной проблемы с событиями
    // которые могут быть привязаны к ним.
    frozen_dlls_.add (name_lib, lib_);
#endif
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (TOLOG (name_lib) + TOLOG (lib_name_) + TOLOG (e.what ()));
  }
}


void
ObjGraph::free_lib ()
{
  if (lib_)
  {
    dfilter_.reset ();
    pf_create_ = 0;
    lib_.unload ();
  }
  lib_name_.clear ();
}


void
ObjGraph::set_src_connect (
  int       indx_src,
  ObjGraph* filter,
  int       indx_dst)
{
  U3_CHECK (indx_src < info_.pts_.count_ins_, "failed connect, indx_src < info_.pts_.count_ins_" + VTOLOG (indx_src) + VTOLOG (info_.pts_.count_ins_) + VTOLOG (indx_dst) + TOLOG (filter->lib_name_));

  info_.pts_.ins_[indx_src].filter_  = filter;
  info_.pts_.ins_[indx_src].indx_pt_ = indx_dst;
  U3_ASSERT (info_.pts_.ins_[indx_src].self_test ());
}


void
ObjGraph::set_dst_connect (
  int       indx_src,
  ObjGraph* filter,
  int       indx_dst)
{
  U3_CHECK (indx_src < info_.pts_.count_outs_, "failed connect, indx_src < info_.pts_.count_outs_" + VTOLOG (indx_src) + VTOLOG (info_.pts_.count_outs_) + VTOLOG (indx_dst) + TOLOG (filter->lib_name_));

  info_.pts_.outs_[indx_src].filter_  = filter;
  info_.pts_.outs_[indx_src].indx_pt_ = indx_dst;
  U3_ASSERT (info_.pts_.outs_[indx_src].self_test ());
}


void
ObjGraph::transform (obj::dll::TransformInfo& info)
{
  U3_ASSERT (dfilter_);
  try
  {
    info.finfo_ = &info_;
    dfilter_->transform (info);
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


const obj::FilterInfo&
ObjGraph::get_info () const
{
  return info_;
}
}   // namespace libs::icore::impl::var1::obj
