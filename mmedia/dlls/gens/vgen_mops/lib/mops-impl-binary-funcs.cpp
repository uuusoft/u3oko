/**
\file       mops-impl-binary-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       16.07.2018
\project    u3_vgen_mops_lib
\brief      Реализация впомогательной функции бинаризации изображения
            Не является МО, но требуется для реализации МО через свертку
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-mops-lib-includes_int.hpp"
#include "morph-operator.hpp"
#include "mops-impl.hpp"

namespace dlls::gens::vgen_mops::lib
{
void
MopsImpl::bin_buf (
  const syn::NodeID&                id_node,
  const syn::MorphBuffInfo&         b2b,
  const std::int16_t                bound,
  const std::int16_t                val,
  ::utils::dbufs::video::IVideoBuf* pdst)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (pdst, "dst dlls::gens::vgen_mops::lib"));

  cinfo.params_.evals_.push_back (boost::any (::libs::optim::s16bit::consts::us_all_xffff));
  cinfo.params_.evals_.push_back (boost::any (bound));
  cinfo.params_.evals_.push_back (boost::any (val));

  ::libs::optim::mcalls::InfoMFunct tfunct (&cmp_get_const_);

  pthreads_->mthreads_call (
    id_node,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::gens::vgen_mops::lib
