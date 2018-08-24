//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mops-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_vgen_mops_lib
\brief      Реализация фильтра МО.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "morph-operator.hpp"
#include "mops-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace gens { namespace vgen_mops { namespace lib {

MopsImpl::MopsImpl () :
  props_ (nullptr)
{}


MopsImpl::~MopsImpl ()
{}


void
MopsImpl::init ()
{
  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  cmp_get_const_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCmpGTConstAlg::val_key));
  pthreads_      = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();

  morph_helper_.init ();
  return;
}


void
MopsImpl::set_props (VideoMorphologyProp::craw_ptr _props)
{
  UASSERT (_props);
  props_ = _props;
  return;
}

}}}}      // namespace dlls::gens::vgen_mops::lib
