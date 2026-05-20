#pragma once
/**
\file       ioptim-alg.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_doptim_dll
*/

// EAI-REFACT
namespace dlls::doptim::impl::syn
{
using hioptim = ::libs::optim::io::hioptim;
}

namespace dlls::doptim::impl
{
class IOptimAlg
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IOptimAlg)

  IOptimAlg () :
    sel_ (&func_)
  {
  }

  virtual ~IOptimAlg ()
  {
  }

  syn::hioptim
  get ()
  {
    U3_ASSERT (sel_.self_test ());
    return sel_;
  }

  void
  sync_impl (const ::libs::optim::io::TInit& iinfo)
  {
    try
    {
      sync_impl_int (iinfo);
    }
    catch (const std::exception& e)
    {
      U3_LOG_DATA_EXCEPT (e.what ());
    }
  }

  protected:
  //  IOptimAlg interface
  virtual void sync_impl_int (const ::libs::optim::io::TInit& iinfo) = 0;

  syn::hioptim::store_func_type func_;   //<
  syn::hioptim                  sel_;    //<
};
}   // namespace dlls::doptim::impl
