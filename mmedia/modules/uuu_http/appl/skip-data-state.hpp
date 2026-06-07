#pragma once
/**
\file       skip-data-state.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       13.09.2018
\project    u3_http_module
*/

namespace modules::uuu_http::appl
{
struct SkipDataState final {
  using time_point_type = std::chrono::time_point< std::chrono::high_resolution_clock >;

  SkipDataState ()  = default;
  ~SkipDataState () = default;

  void
  reset ()
  {
    SkipDataState temp;
    std::swap (skip_send_bytes_, temp.skip_send_bytes_);
    std::swap (skip_send_request_, temp.skip_send_request_);
    std::swap (last_send_time_, temp.last_send_time_);
  }

  std::uint64_t   skip_send_bytes_   = 0;                                            //<
  std::uint64_t   skip_send_request_ = 0;                                            //<
  time_point_type last_send_time_    = std::chrono::high_resolution_clock::now ();   //<
};
}   // namespace modules::uuu_http::appl
