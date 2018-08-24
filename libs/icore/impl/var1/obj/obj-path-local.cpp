//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       obj-path-local.cpp    
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       22.12.2016.
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

::libs::helpers::dlls::ForeverLoadDlls ObjPath::freez_libs_;

ObjPath::ObjPath (const core::path::IPath* pparent, ::libs::link::ILink::weak_ptr _logger) :
  pparent_ (pparent),
  state_ (obj::RunStateFilter::stop),
  pf_create_ (0),
  logger_ (_logger)
{}


ObjPath::~ObjPath ()
{
  state_ = obj::RunStateFilter::stop;
  ObjPath::free_lib ();
  return;
}


void
ObjPath::load_lib (const std::string& _name_lib, const base_functs::xml::itn& _node)
{
  XULOG_TRACE ("uuu_core::Filter::load_lib::beg, " << _name_lib);
  lib_.load (_name_lib, boost::dll::load_mode::rtld_now);
  name_lib_ = lib_.location ().filename ().string ();

  XULOG_TRACE ("uuu_core::Filter::load_lib::try get create funct from, " << _name_lib << ", " << obj::consts::name_funct_create);
  pf_create_ = boost::dll::import<obj::dll::create_impl_funct_type> (lib_, obj::consts::name_funct_create);
  //  регистриуем свои данные в DLL
  dfilter_.reset (pf_create_ ());
  dfilter_->load (&info_, _node);
  info_.correct ();
  //  Пока отключено удаление.
  //  Удерживаем в памяти все загруженные единожды модули обработки данных. Их не много, а удалять их пока нельзя из-за нерешенной проблемы с событиями
  //  которые могут быть привязаны к ним.
  freez_libs_.add (_name_lib, lib_);
  XULOG_TRACE ("uuu_core::Filter::load_lib::end, " << _name_lib);
  return;
}


void
ObjPath::free_lib ()
{
  if (lib_)
    {
      dfilter_.reset ();
      pf_create_ = 0;
      lib_.unload ();
    }

  name_lib_.clear ();
  return;
}


void
ObjPath::set_src_connect (
  int      _indx_src,
  ObjPath* _filter,
  int      _indx_dst)
{
  CHECK_STATE (_indx_src < info_.pts_.count_ins_, "failed connect, _indx_src < info_.pts_.count_ins_");

  info_.pts_.ins_[_indx_src].filter_  = _filter;
  info_.pts_.ins_[_indx_src].indx_pt_ = _indx_dst;
  UASSERT (info_.pts_.ins_[_indx_src].self_test ());
  return;
}


void
ObjPath::set_dst_connect (
  int      _indx_src,
  ObjPath* _filter,
  int      _indx_dst)
{
  CHECK_STATE (_indx_src < info_.pts_.count_outs_, "failed connect, _indx_src < info_.pts_.count_outs_");

  info_.pts_.outs_[_indx_src].filter_  = _filter;
  info_.pts_.outs_[_indx_src].indx_pt_ = _indx_dst;

  UASSERT (info_.pts_.outs_[_indx_src].self_test ());
  return;
}


void
ObjPath::transform (obj::dll::TransformInfo& _info)
{
  UASSERT (dfilter_);
  _info.finfo_ = &info_;
  dfilter_->transform (_info);
  return;
}


const obj::FilterInfo&
ObjPath::get_info () const
{
  return info_;
}

}}}}}      // namespace libs::icore::impl::var1::obj
