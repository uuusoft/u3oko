/**
\file       morph-operator.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       16.07.2018
\project    u3_vgen_mops_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-mops-lib-includes_int.hpp"
#include "morph-operator.hpp"

#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::gens::vgen_mops::lib::helpers
{
MorphOperator::MorphOperator () :
  pthreads_ (nullptr),
  transinfo_ (nullptr)
{
}


MorphOperator::~MorphOperator ()
{
}


void
MorphOperator::init ()
{
  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  conv_mod_3x3_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod3x3Alg::val_key));
  conv_mod_5x5_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod5x5Alg::val_key));
  conv_mod_7x7_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod7x7Alg::val_key));
  conv_mod_9x9_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod9x9Alg::val_key));
  conv_mod_11x11_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod11x11Alg::val_key));
}


void
MorphOperator::applay_operation2buf (
  const syn::NodeID&                id_node,
  const syn::MorphOperationParams&  op,
  ::libs::bufs::Bufs*               pbuf,
  ::utils::dbufs::video::IVideoBuf* pdst)
{
  pthreads_ = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();

  switch (op.morph_type_)
  {
  case ::libs::ievents::props::videos::generic::morph::MorphOps::empty:
    break;
  case ::libs::ievents::props::videos::generic::morph::MorphOps::binary:
    break;
  case ::libs::ievents::props::videos::generic::morph::MorphOps::dilation:
    dilation_buf (id_node, op, pbuf, pdst);
    break;
  case ::libs::ievents::props::videos::generic::morph::MorphOps::erosion:
    erosion_buf (id_node, op, pbuf, pdst);
    break;
  default:
    U3_LOG_DATA_ERROR ("unknown type MorphOps" + VTOLOG (U3_CAST_UINT32_FORCE (op.morph_type_)));
    break;
  }
}


void
MorphOperator::set_transform_info (syn::TransformInfo* tranform_info)
{
  transinfo_ = tranform_info;
}
}   // namespace dlls::gens::vgen_mops::lib::helpers
