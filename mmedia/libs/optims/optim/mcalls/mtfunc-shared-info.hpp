#pragma once
/**
\file       mtfunc-shared-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::mcalls
{
/// Данные, которые разделяются между всеми рабочими потоками при вызове
class MTFuncSharedInfo final
{
  public:
  //  ext types
  using barier_type     = std::barrier<>;
  using barier_ptr_type = std::unique_ptr< barier_type >;

  MTFuncSharedInfo ()  = default;
  ~MTFuncSharedInfo () = default;

  MTFuncSharedInfo (const MTFuncSharedInfo&)            = delete;
  MTFuncSharedInfo& operator= (const MTFuncSharedInfo&) = delete;

  std::atomic_bool exit_request_ = false;   //< Флаг запроса на выход
  barier_ptr_type  bstart_;                 //< Барьер старта
};
}   // namespace libs::optim::mcalls
