#pragma once
/**
\file       mfunc-params.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::io
{
struct MTFuncParams final {
  //  ext types
  using any_param_type  = boost::any;                      //< EAI-REFACT std::any
  using any_params_type = std::vector< any_param_type >;   //<

  MTFuncParams () :
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

  std::vector< std::int16_t* >       arrayss_;       //< old shit U3-REFACT
  std::vector< std::int16_t** >      parrayss_;      //< old shit U3-REFACT
  std::vector< std::uint32_t >       uints_;         //< old shit U3-REFACT
  std::vector< std::int32_t >        ints_;          //< old shit U3-REFACT
  std::vector< std::int32_t* >       pints_;         //< old shit U3-REFACT
  std::vector< float >               floats_;        //< old shit U3-REFACT
  std::vector< bool >                bools_;         //< old shit U3-REFACT
  std::vector< const std::int16_t* > consts_;        //< old shit U3-REFACT
  const std::uint16_t*               dest_mask_;     //< old shit U3-REFACT
  const std::uint16_t*               source_mask_;   //< old shit U3-REFACT
  any_params_type                    evals_;         //<
};
}   // namespace libs::optim::io
