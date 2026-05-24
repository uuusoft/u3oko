#pragma once
/**
\file       call-params.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_scale
*/

namespace libs::optim::s16bit::scale::fixed
{
struct CallParams final {
  CallParams () :
    psrc_ (nullptr),
    pdst_ (nullptr)
  {
  }

  ~CallParams ()
  {
  }


  void
  reset ()
  {
    psrc_ = nullptr;
    pdst_ = nullptr;
  }


  void
  check () const
  {
    U3_CHECK (psrc_, "empty src");
    U3_CHECK (pdst_, "empty dst");
  }

  const ::libs::optim::io::ProxyBuf* psrc_;   //<
  ::libs::optim::io::ProxyBuf*       pdst_;   //<
};
}   // namespace libs::optim::s16bit::scale::fixed
