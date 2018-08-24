//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       diff-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vgen_diff_lib
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "diff-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace gens { namespace vgen_diff { namespace lib {

DiffImpl::DiffImpl () :
  props_ (nullptr)
{}


DiffImpl::~DiffImpl ()
{}


void
DiffImpl::set_props (VideoDiffProp::craw_ptr _props)
{
  props_ = _props;
  return;
}


void
DiffImpl::init ()
{
  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  cmp_get_const_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCmpGTConstAlg::val_key));
  abs_diff_      = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CAbsDiffAlg::val_key));
  pthreads_      = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();
  return;
}

}}}}      // namespace dlls::gens::vgen_diff::lib
