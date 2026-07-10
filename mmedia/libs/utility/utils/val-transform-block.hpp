#pragma once
/**
\file       val-transform-block.hpp
\date       11.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/

namespace libs::utility::utils
{
template< typename TType >
class ValTransformBlock final
{
  public:
  //  ext types
  using begfunc_type = std::function< void (TType&) >;
  using endfunc_type = std::function< void (TType&) >;

  explicit ValTransformBlock (
    TType&              value,
    const begfunc_type& beg_func,
    const endfunc_type& end_funct) :
    value_ (value),
    beg_func_ (beg_func),
    end_func_ (end_funct)
  {
    beg_func_ (value_);
  }

  ~ValTransformBlock ()
  {
    end_func_ (value_);
  }

  private:
  TType&             value_;      //<
  const begfunc_type beg_func_;   //<
  const endfunc_type end_func_;   //<
};
}   // namespace libs::utility::utils
