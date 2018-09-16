//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vgen_conv
\brief      Фильтр для вывода изрбражения
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls { namespace gens { namespace vgen_conv3_11 {

Filter::Filter () :
  icore_3x3_ (&core_3x3_),
  icore_5x5_ (&core_5x5_),
  icore_7x7_ (&core_7x7_),
  icore_9x9_ (&core_9x9_),
  icore_11x11_ (&core_11x11_)
{}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);
  finfo_.load (_node);

  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  conv_mod_3x3_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod3x3Alg::val_key));
  conv_mod_5x5_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod5x5Alg::val_key));
  conv_mod_7x7_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod7x7Alg::val_key));
  conv_mod_9x9_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod9x9Alg::val_key));
  conv_mod_11x11_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod11x11Alg::val_key));
  return;
}


void
Filter::call_int (CallInterfInfo& _info)
{
  super::prepare_call (_info);
  super::call_gen (_info);
  return;
}


void
Filter::init_pts (ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::PointFilter::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);

  return;
}

}}}      // namespace dlls::gens::vgen_conv3_11
