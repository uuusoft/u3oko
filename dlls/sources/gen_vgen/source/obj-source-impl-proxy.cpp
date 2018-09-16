//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       obj-source-impl-proxy.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.05.2017
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "obj-source-impl-proxy.hpp"

namespace dlls { namespace sources { namespace gen_vgen {

ObjSourceImplProxy::ObjSourceImplProxy () :
  funct_get_ (0),
  funct_free_ (0),
  impl_ (nullptr)
{}


ObjSourceImplProxy::~ObjSourceImplProxy ()
{
  clear ();
}


void
ObjSourceImplProxy::init (const std::string& _name_impl)
{
  clear ();
  CHECK_STATE (!_name_impl.empty (), "failed, empty impl name for capture");

  const std::string _path      = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  const std::string _full_path = ::libs::helpers::files::make_path (_path, ::utils::mem_functs::files::decorate_dll_name (_name_impl));

  XULOG_TRACE ("try load dll source from, " << _full_path);
  lib_.load (_full_path.c_str (), boost::dll::load_mode::rtld_now);

  XULOG_TRACE ("try get create funct from, " << _full_path);
  funct_get_ = boost::dll::import<gen_lib::get_source_funct_type> (lib_, gen_lib::consts::name_get_funct);

  XULOG_TRACE ("try get free funct from, " << _full_path);
  funct_free_ = boost::dll::import<gen_lib::free_source_funct_type> (lib_, gen_lib::consts::name_free_funct);
  CHECK_STATE (funct_get_ && funct_free_, "failed get funct");

  XULOG_TRACE ("try make source from, " << _full_path);
  CHECK_CALL (funct_get_ (&impl_), "failed create impl");
  CHECK_STATE (impl_, "failed, create empty impl");

  impl_->init ();
  XULOG_TRACE ("make source done from, " << _full_path);
  return;
}


void
ObjSourceImplProxy::clear ()
{
  if (funct_free_ && impl_)
    {
      impl_->stop ();
      funct_free_ (&impl_);
    }

  funct_get_  = 0;
  funct_free_ = 0;
  impl_       = nullptr;
  //  Ќикогда ничего не выгружаем, во избежании падени€ из-за возможных перекрестных ссылок (weak_ptr x shared_ptr).
  //if( lib_.is_loaded() ){lib_.unload();}
  return;
}


gen_lib::ISourceImpl::raw_ptr
ObjSourceImplProxy::get ()
{
  return impl_;
}


boost::dll::shared_library
ObjSourceImplProxy::get_lib ()
{
  return lib_;
}

}}}      // namespace dlls::sources::gen_vgen
