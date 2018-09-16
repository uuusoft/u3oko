#pragma once
/**
\file       mfunct-params.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      emty brief
*/

namespace libs { namespace optim { namespace io {
/**
  \brief  
  */
struct MFunctParams
{
  //  ext types
  using any_type  = boost::any;
  using anys_type = std::vector<any_type>;

  MFunctParams () :
    dest_mask_ (0),
    source_mask_ (0)
  {
    arrayss_.reserve (8);
    parrayss_.reserve (8);
    uints_.reserve (4);
    ints_.reserve (4);
    pints_.reserve (4);
    floats_.reserve (4);
    bools_.reserve (4);
    consts_.reserve (4);
  }

  std::vector<short*>       arrayss_;          //< old shit REFACT
  std::vector<short**>      parrayss_;         //< old shit REFACT
  std::vector<unsigned int> uints_;            //< old shit REFACT
  std::vector<int>          ints_;             //< old shit REFACT
  std::vector<int*>         pints_;            //< old shit REFACT
  std::vector<float>        floats_;           //< old shit REFACT
  std::vector<bool>         bools_;            //< old shit REFACT
  std::vector<const short*> consts_;           //< old shit REFACT
  const unsigned short*     dest_mask_;        //< old shit REFACT
  const unsigned short*     source_mask_;      //< old shit REFACT
  anys_type                 evals_;            //< ???
};

}}}      // namespace libs::optim::io
