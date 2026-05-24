#pragma once
/**
\file       transform-value-helper.hpp
\date       11.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
*/

namespace libs::helpers::utils
{
template< typename TTValue >
class TransformValueHelper final
{
  public:
  //  ext types
  using beg_func_type = std::function< void (TTValue&) >;
  using end_func_type = std::function< void (TTValue&) >;

  explicit TransformValueHelper (
    TTValue&             value,
    const beg_func_type& beg_func,
    const beg_func_type& end_funct) :
    value_ (value),
    beg_func_ (beg_func),
    end_func_ (end_funct)
  {
    beg_func_ (value_);
  }

  ~TransformValueHelper ()
  {
    end_func_ (value_);
  }

  private:
  TTValue&            value_;      //<
  const beg_func_type beg_func_;   //<
  const end_func_type end_func_;   //<
};
}   // namespace libs::helpers::utils
