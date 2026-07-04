#pragma once
/**
\file       correct-image-impl.hpp
\date       01.01.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_vcorrect_vdd
*/

namespace dlls::uplifters::vcorrect::soft::consts
{
#if 1
inline constexpr std::uint32_t size_graduent      = 256;   // std::pow (2, 8);
inline constexpr std::uint16_t max_graduent_val   = 127;   // std::pow (2, 7);
inline constexpr float         bound_gradient_val = static_cast< float > (max_graduent_val);
#else
inline constexpr std::uint32_t size_graduent      = 65536;   // std::pow (2, 16);
inline constexpr std::uint16_t max_graduent_val   = 32768;   // std::pow (2, 15);
inline constexpr float         bound_gradient_val = static_cast< float > (max_graduent_val);
#endif
}   // namespace dlls::uplifters::vcorrect::soft::consts

namespace dlls::uplifters::vcorrect::soft
{
class CorrectImageImpl final : public ::libs::events_base::runtime::interf::interfaces::ICorrectImage
{
  public:
  CorrectImageImpl ();
  virtual ~CorrectImageImpl () = default;

  CorrectImageImpl (const CorrectImageImpl&)                = delete;
  CorrectImageImpl& operator= (const CorrectImageImpl&)     = delete;
  CorrectImageImpl (CorrectImageImpl&&) noexcept            = delete;
  CorrectImageImpl& operator= (CorrectImageImpl&&) noexcept = delete;

  private:
  using graduent_array_type = std::array< std::int16_t, consts::size_graduent >;

  U3_ADD_SUPER_CLASS (::libs::events_base::runtime::interf::interfaces::ICorrectImage)

  //  ::libs::events_base::runtime::interf::interfaces::ICorrectImage overrides
  virtual auto change_state_int (bool) -> void override;
  virtual auto update_correction_property_int (const syn::VideoCorrectProp::raw_ptr) -> void override;
  virtual auto process_int (syn::IVideoBuf::raw_ptr, syn::IVideoBuf::raw_ptr, syn::IVideoBuf::raw_ptr) -> bool override;

  auto graduent_correct (syn::IVideoBuf&, const graduent_array_type&) -> void;
  auto bright_correct (syn::IVideoBuf&) -> void;
  auto sat2byte_correct (syn::IVideoBuf&) -> void;

  syn::VideoCorrectProp::craw_ptr props_ = nullptr;   //<
  ::libs::optim::io::hioptim      mfunc_const_add_;   //<
  ::libs::optim::io::hioptim      mfunc_sat2byte_;    //<
  ::libs::optim::io::hioptim      mfunc_grad_func_;   //<
  graduent_array_type             contrasts_ {};      //<
  graduent_array_type             saturations_ {};    //<
  graduent_array_type             hues_ {};           //<
  syn::IMCaller::ptr              pthreads_;          //<
};
}   // namespace dlls::uplifters::vcorrect::soft
