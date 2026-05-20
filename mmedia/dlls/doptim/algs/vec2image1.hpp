#pragma once
/**
\file       vec2image1.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CVec2Image1Alg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.gen.vec2image1";

  CVec2Image1Alg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CVec2Image1Alg ()
  {
  }

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    sel_.set (::libs::optim::s16bit::gen::vec2image1::alu);
  }
};
}   // namespace dlls::doptim::impl::algs
