//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       ioptim-alg.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_doptim_dll
\brief      empty brief
*/

namespace dlls { namespace doptim { namespace impl {
//  syn
using ::libs::optim::io::hioptim;
/**
\brief  empty brief
*/
class IOptimAlg
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IOptimAlg);

  IOptimAlg () :
    sel_ (&funct_)
  {}

  virtual ~IOptimAlg ()
  {}

  ::libs::optim::io::hioptim
  get ()
  {
    UASSERT (sel_.self_test ());
    return sel_;
  }

  void
  update (const ::libs::optim::io::TInit& _iinfo)
  {
    return update_int (_iinfo);
  }


  protected:
  //  IOptimAlg interface
  virtual void update_int (const ::libs::optim::io::TInit& _iinfo) = 0;

  hioptim::store_funct_type funct_;      //< Функция алгоритма.
  hioptim                   sel_;        //< ???
};

}}}      // namespace dlls::doptim::impl
