/**
\file       mops-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       16.07.2018
\project    u3_vgen_mops_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-mops-lib-includes_int.hpp"
#include "morph-operator.hpp"
#include "mops-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::gens::vgen_mops::lib
{
MopsImpl::MopsImpl () :
  props_ (nullptr),
  transinfo_ (nullptr)
{
}


MopsImpl::~MopsImpl ()
{
}


void
MopsImpl::init ()
{
  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  cmp_get_const_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCmpGTConstAlg::val_key));
  pthreads_      = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();

  morph_helper_.init ();
}


void
MopsImpl::set_props (syn::VideoMorphologyProp::craw_ptr props)
{
  U3_ASSERT (props);
  props_ = props;
}


void
MopsImpl::set_transform_info (syn::TransformInfo* tranform_info)
{
  transinfo_ = tranform_info;
}
}   // namespace dlls::gens::vgen_mops::lib
