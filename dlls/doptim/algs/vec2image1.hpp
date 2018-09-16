#pragma once
/**
\file       vec2image1.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_doptim_dll
\brief      empty brief
*/

namespace dlls { namespace doptim { namespace impl { namespace algs {
/**
\brief  empty brief
*/
class CVec2Image1Alg : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.gen.vec2image1";

  CVec2Image1Alg ()
  {
    update (::libs::optim::io::TInit ());
    sel_.set_text (val_key);
  }

  virtual ~CVec2Image1Alg ()
  {}


  protected:
  virtual void
  update_int (const ::libs::optim::io::TInit& _iinfo) override
  {
    sel_.set (::libs::optim::s16bit::gen::vec2image1::alu);
    return;
  }
};

}}}}      // namespace dlls::doptim::impl::algs
