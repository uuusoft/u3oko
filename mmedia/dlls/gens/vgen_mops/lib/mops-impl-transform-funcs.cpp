/**
\file       mops-impl-transform-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       16.07.2018
\project    u3_vgen_mops_lib
\brief      Реализация основной функции преобразования фильтра МО
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-mops-lib-includes_int.hpp"
#include "morph-operator.hpp"
#include "mops-impl.hpp"

namespace dlls::gens::vgen_mops::lib
{
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
      pdst->clone (psrc, 100.0f);
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
}   // namespace dlls::gens::vgen_mops::lib
