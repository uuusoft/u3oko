#pragma once
/**
\file       TCallParams.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "../helpers/quant/CQuant.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::backward
{
struct TThreadRetFromCall {
  TThreadRetFromCall () :
    byte_size_ (0),
    beg_dst_ (0)
  {
  }

  void
  reset ()
  {
    byte_size_ = 0;
    beg_dst_   = 0;
  }

  bool
  check () const
  {
    return byte_size_ > 0 && beg_dst_;
  }

  int                 byte_size_;   //<
  const std::int16_t* beg_dst_;     //<
};


struct TCallParams {
  TCallParams () :
    psrc_ (0),
    pdst_ (0),
    pquanter_ (0),
    prets_ (0)
  {
  }

  ~TCallParams ()
  {
  }

  void
  reset ()
  {
    psrc_     = 0;
    pdst_     = 0;
    pquanter_ = 0;
    prets_    = 0;
  }

  bool
  check () const
  {
    return psrc_ && pdst_ && pquanter_ && prets_;
  }

  const ::libs::optim::io::ProxyBuf*  psrc_;       //<
  ::libs::optim::io::ProxyBuf*        pdst_;       //<
  const b8x8::helpers::quant::CQuant* pquanter_;   //<
  std::vector< TThreadRetFromCall >*  prets_;      //< Размер сжатых данных для каждого потока
};
}   // namespace libs::optim::s16bit::freq::dct::b8x8::backward
