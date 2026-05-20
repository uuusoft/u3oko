/**
\file       diff-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vgen_diff_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-diff-lib-includes_int.hpp"
#include "diff-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::gens::vgen_diff::lib
{
DiffImpl::DiffImpl () :
  props_ (nullptr),
  transinfo_ (nullptr)
{
}


DiffImpl::~DiffImpl ()
{
}


void
DiffImpl::set_props (syn::VideoDiffProp::craw_ptr props)
{
  props_ = props;
}


void
DiffImpl::init ()
{
  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  cmp_get_const_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCmpGTConstAlg::val_key));
  abs_diff_      = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CAbsDiffAlg::val_key));
  pthreads_      = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
}


void
DiffImpl::set_transform_info (syn::TransformInfo* tranform_info)
{
  transinfo_ = tranform_info;
}
}   // namespace dlls::gens::vgen_diff::lib
