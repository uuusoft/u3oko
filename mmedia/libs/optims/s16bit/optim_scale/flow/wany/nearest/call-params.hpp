#pragma once
/**
\file       call-params.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_scale
*/

namespace libs::optim::s16bit::scale::flow::wany::nearest
{
struct CallParams {
  CallParams () :
    psrc_ (nullptr),
    pdst_ (nullptr),
    stride_output_ (nullptr),
    max_out_size_ (nullptr),
    indxer_ (nullptr)
  {
  }

  ~CallParams ()
  {
  }

  void
  reset ()
  {
    psrc_          = nullptr;
    pdst_          = nullptr;
    stride_output_ = nullptr;
    max_out_size_  = nullptr;
    indxer_        = nullptr;
  }

  void
  check () const
  {
    U3_CHECK (psrc_, "failed, empty src");
    U3_CHECK (pdst_, "failed, empty dst");
    U3_CHECK (stride_output_, "failed, empty out stride");
    U3_CHECK (max_out_size_, "failed, empty max size out");
    U3_CHECK (indxer_, "failed, empty endixer");
  }

  const ::libs::optim::io::ProxyBuf* psrc_;            //<
  ::libs::optim::io::ProxyBuf*       pdst_;            //<
  std::uint32_t*                     stride_output_;   //<
  std::uint32_t*                     max_out_size_;    //<
  const IndexerColRow*               indxer_;          //<
};
}   // namespace libs::optim::s16bit::scale::flow::wany::nearest
