//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ioptim-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_doptim_dll
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "ioptim-alg.hpp"
#include "ioptim-impl.hpp"

namespace dlls { namespace doptim { namespace impl {

IOptimImpl::IOptimImpl ()
{
  guard_type _grd (mtx_);
  construct ();
  return;
}


IOptimImpl::~IOptimImpl ()
{}


::libs::optim::io::hioptim
IOptimImpl::get (const ::libs::optim::io::qoptim& _query)
{
  guard_type _grd (mtx_);
  auto       _find = algs_.find (_query.id_);

  if (algs_.end () == _find)
    {
      UASSERT (_query.id_.c_str () && 0);
      return ::libs::optim::io::hioptim (nullptr);
    }

  UASSERT (_find->second);
  ::libs::optim::io::hioptim _ret = _find->second->get ();
  UASSERT (_ret.self_test ());
  return _ret;
}


void
IOptimImpl::update (const ::libs::optim::io::TInit& _iinfo)
{
  guard_type _grd (mtx_);

  for (str2functs_type::value_type& _val : algs_)
    {
      UASSERT (_val.second);
      _val.second->update (_iinfo);
    }
  return;
}

}}}      // namespace dlls::doptim::impl
