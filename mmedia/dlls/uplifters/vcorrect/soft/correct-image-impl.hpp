#pragma once
/**
\file       correct-image-impl.hpp
\date       01.01.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcorrect_vdd
*/

namespace dlls::uplifters::vcorrect::soft::consts
{
#if 1
constexpr std::uint32_t size_graduent      = 256;   // std::pow (2, 8);
constexpr std::uint16_t max_graduent_val   = 127;   // std::pow (2, 7);
constexpr float         bound_gradient_val = static_cast< float > (max_graduent_val);
#else
constexpr std::uint32_t size_graduent      = 65536;   // std::pow (2, 16);
constexpr std::uint16_t max_graduent_val   = 32768;   // std::pow (2, 15);
constexpr float         bound_gradient_val = static_cast< float > (max_graduent_val);
#endif
}   // namespace dlls::uplifters::vcorrect::soft::consts

namespace dlls::uplifters::vcorrect::soft
{
class CorrectImageImpl final : public ::libs::ievents::runtime::interf::interfaces::ICorrectImage
{
  public:
  CorrectImageImpl ();
  virtual ~CorrectImageImpl () = default;

  private:
  using graduent_array_type = std::array< std::int16_t, consts::size_graduent >;

  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::interf::interfaces::ICorrectImage)

  //  ::libs::ievents::runtime::interf::interfaces::ICorrectImage overrides
  virtual void change_state_int (bool enable) override;
  virtual void update_correction_property_int (const syn::VideoCorrectProp::raw_ptr info) override;
  virtual bool process_int (syn::IVideoBuf::raw_ptr h16, syn::IVideoBuf::raw_ptr s16, syn::IVideoBuf::raw_ptr l16) override;

  void graduent_correct (syn::IVideoBuf& buf, const graduent_array_type& vals2vals);
  void bright_correct (syn::IVideoBuf& y16_buf);
  void sat2byte_correct (syn::IVideoBuf& y16_buf);

  syn::VideoCorrectProp::craw_ptr props_ = nullptr;   //<
  ::libs::optim::io::hioptim      mfunc_const_add_;   //<
  ::libs::optim::io::hioptim      mfunc_sat2byte_;    //<
  ::libs::optim::io::hioptim      mfunc_grad_func_;   //<
  graduent_array_type             contrasts_;         //<
  graduent_array_type             saturations_;       //<
  graduent_array_type             hues_;              //<
  syn::IMCaller::ptr              pthreads_;          //<
};
}   // namespace dlls::uplifters::vcorrect::soft
