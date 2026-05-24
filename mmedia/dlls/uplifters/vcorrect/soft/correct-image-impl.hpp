#pragma once
/**
\file       correct-image-impl.hpp
\date       01.01.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcorrect_vdd
*/

namespace dlls::uplifters::vcorrect::soft
{
class CorrectImageImpl final : public ::libs::ievents::runtime::interf::interfaces::ICorrectImage
{
  public:
  CorrectImageImpl ();
  virtual ~CorrectImageImpl ();

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::interf::interfaces::ICorrectImage)

  //  ::libs::ievents::runtime::interf::interfaces::ICorrectImage overrides
  virtual void change_state_int (bool enable) override;
  virtual void update_correction_property_int (const syn::VideoCorrectProp::raw_ptr info) override;
  virtual bool process_int (syn::IVideoBuf::raw_ptr h16, syn::IVideoBuf::raw_ptr s16, syn::IVideoBuf::raw_ptr l16) override;

  void graduent_correct (syn::IVideoBuf& buf, const std::array< std::int16_t, 256 >& vals2vals);
  void bright_correct (syn::IVideoBuf& y16_buf);
  void sat2byte_correct (syn::IVideoBuf& y16_buf);

  syn::VideoCorrectProp::craw_ptr props_;             //<
  ::libs::optim::io::hioptim      mfunc_const_add_;   //<
  ::libs::optim::io::hioptim      mfunc_sat2byte_;    //<
  ::libs::optim::io::hioptim      mfunc_grad_func_;   //<
  std::array< std::int16_t, 256 > contrasts_;         //<
  std::array< std::int16_t, 256 > saturations_;       //<
  std::array< std::int16_t, 256 > hues_;              //<
  syn::IMCaller::ptr              pthreads_;          //<
};
}   // namespace dlls::uplifters::vcorrect::soft
