#pragma once
/**
\file       id2buf-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       13.09.2018
\project    u3_http_module
*/

// old shit
namespace modules::uuu_http::appl
{
struct Id2BufInfo final {
  Id2BufInfo ()  = default;
  ~Id2BufInfo () = default;

  syn::ZipDataEvent::zip_buf_type buf_;                  //<
  std::int32_t                    off_data_ = 0;         //<
  std::string                     base64_buf_;           //< U3-REFACT
  std::int64_t                    number_frame_   = 0;   //<
  std::int64_t                    counter_frames_ = 0;   //<
};
}   // namespace modules::uuu_http::appl
