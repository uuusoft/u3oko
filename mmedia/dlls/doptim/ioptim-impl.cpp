/**
\file       ioptim-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_doptim_dll
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "doptim-includes_int.hpp"
#include "ioptim-alg.hpp"
#include "ioptim-impl.hpp"

namespace dlls::doptim::impl
{
IOptimImpl::IOptimImpl ()
{
  lock_type lock (mtx_);
  construct ();
}


IOptimImpl::~IOptimImpl ()
{
}


syn::hioptim
IOptimImpl::get (const ::libs::optim::io::qoptim& query)
{
  lock_type lock (mtx_);
  auto      find = algs_.find (query.id_);

  if (algs_.end () == find)
  {
    U3_ASSERT (query.id_.c_str () && 0);
    return syn::hioptim (nullptr);
  }

  U3_ASSERT (find->second);
  syn::hioptim ret = find->second->get ();
  U3_ASSERT (ret.self_test ());
  return ret;
}


void
IOptimImpl::sync_impl (const ::libs::optim::io::TInit& iinfo)
{
  ::libs::helpers::sys::cpu::TextExtCpu cpu_helper;
  lock_type                             lock (mtx_);
  for (str2funcs_type::value_type& val : algs_)
  {
    U3_ASSERT (val.second);
    val.second->sync_impl (iinfo);
  }
}
}   // namespace dlls::doptim::impl
