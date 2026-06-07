/**
\file       vgen-conv3_11-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgen_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-conv3_11-includes_int.hpp"
#include "vgen-conv3_11-info-filter-dll.hpp"
#include "vgen-conv3_11-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::gens::vgen_conv3_11
{
void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  conv_mod_3x3_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod3x3Alg::val_key));
  conv_mod_5x5_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod5x5Alg::val_key));
  conv_mod_7x7_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod7x7Alg::val_key));
  conv_mod_9x9_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod9x9Alg::val_key));
  conv_mod_11x11_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod11x11Alg::val_key));
}


void
Filter::call_int (syn::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}
}   // namespace dlls::gens::vgen_conv3_11
