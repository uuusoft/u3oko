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
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::gens::vgen_mops::lib
{
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


void
MopsImpl::itransform (const syn::NodeID& id_node, ::libs::bufs::Bufs& bufs)
{
  morph_helper_.set_transform_info (transinfo_);

  for (const auto& b2b : props_->diffs_)
  {
    const auto&                               sindx = b2b.sindx_diff_;
    const auto&                               dindx = b2b.bindx_diff_;
    ::utils::dbufs::video::IVideoBuf::raw_ptr psrc  = bufs[sindx];

    if (!psrc || psrc->get_flag (::utils::dbufs::BufFlags::empty))
    {
      continue;
    }

    ::libs::bufs::alloc_buf_by_indx (&bufs, dindx, psrc);

    ::utils::dbufs::video::IVideoBuf::raw_ptr pdst = bufs[dindx];
    if (dindx != sindx)
    {
      pdst->clone (psrc, 100.0F);
    }

    for (const auto& op : b2b.morph_operations_)
    {
      if (::libs::ievents::props::videos::generic::morph::MorphOps::empty == op.morph_type_ ||
          ::libs::ievents::props::videos::generic::morph::MorphOps::unknown == op.morph_type_)
      {
        continue;
      }

      U3_LOG_DATA_DBG (FTOLOG (b2b.sindx_diff_) + TOLOG (b2b.bindx_diff_) + to_string (op.morph_type_) + VTOLOG (op.bound_filling_) + VTOLOG (op.val_filling_));
      //  бинаризация в 0..1 как подготовка буфера для выполнения морфологической операции.
      bin_buf (id_node, b2b, op.bound_filling_, 1, pdst);
      //  собственно производим МО над подготовленным буфером.
      morph_helper_.applay_operation2buf (id_node, op, &bufs, pdst);
      //  Вспомогательная бинаризация для дальнейшей обработки буфера в последующих узлах графа обработки данных
      bin_buf (id_node, b2b, 0, op.val_filling_, pdst);
    }
  }

  morph_helper_.set_transform_info (nullptr);
}


void
MopsImpl::bin_buf (
  const syn::NodeID&                id_node,
  const syn::MorphBuffInfo&         b2b,
  const std::int16_t                bound,
  const std::int16_t                val,
  ::utils::dbufs::video::IVideoBuf* pdst)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.emplace_back (pdst, "dst dlls::gens::vgen_mops::lib");

  cinfo.params_.evals_.emplace_back (boost::any (::libs::optim::s16bit::consts::us_all_xffff));
  cinfo.params_.evals_.emplace_back (boost::any (bound));
  cinfo.params_.evals_.emplace_back (boost::any (val));

  ::libs::optim::mcalls::MTFuncInfo tfunc (&cmp_get_const_);

  pthreads_->mthreads_call (
    id_node,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::gens::vgen_mops::lib
