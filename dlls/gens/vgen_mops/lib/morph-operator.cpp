//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       morph-operator.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_vgen_mops_lib
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "morph-operator.hpp"

#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls { namespace gens { namespace vgen_mops { namespace lib { namespace helpers {

MorphOperator::MorphOperator () :
  pthreads_ (nullptr)
{}


MorphOperator::~MorphOperator ()
{}


void
MorphOperator::init ()
{
  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  conv_mod_3x3_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod3x3Alg::val_key));
  conv_mod_5x5_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod5x5Alg::val_key));
  conv_mod_7x7_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod7x7Alg::val_key));
  conv_mod_9x9_   = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod9x9Alg::val_key));
  conv_mod_11x11_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod11x11Alg::val_key));
  return;
}


void
MorphOperator::applay_operation2buff (
  const ParamsOperation& _op,
  ::libs::buffs::Buffs*  _pbuff,
  IVideoBuff*            _pdst)
{
  pthreads_ = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();

  switch (_op.type_)
    {
    case ::libs::ievents::props::videos::generic::morph::TypeOperation::empty:
      break;
    case ::libs::ievents::props::videos::generic::morph::TypeOperation::dilation:
      dilation_buff (_op, _pbuff, _pdst);
      break;
    case ::libs::ievents::props::videos::generic::morph::TypeOperation::erosion:
      erosion_buff (_op, _pbuff, _pdst);
      break;
    default:
      UASSERT_SIGNAL ("failed");
      break;
    }
  return;
}

}}}}}      // namespace dlls::gens::vgen_mops::lib::helpers
