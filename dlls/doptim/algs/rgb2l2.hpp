//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       rgb2l2.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_doptim_dll
\brief      empty brief
*/

namespace dlls { namespace doptim { namespace impl { namespace algs {
/**
\brief  empty brief
*/
class CRgb2LAlg2 : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.convert.l_vs_rgb2.rgb24_to_l";

  CRgb2LAlg2 ()
  {
    update (::libs::optim::io::TInit ());
    sel_.set_text (val_key);
  }

  virtual ~CRgb2LAlg2 ()
  {}


  protected:
  virtual void
  update_int (const ::libs::optim::io::TInit& _iinfo) override
  {
    switch (_iinfo.ext_)
      {
#if defined(UUU_CPU_X86)
      case ::libs::helpers::sys::cpu::TypeExtCpu::fma:
      case ::libs::helpers::sys::cpu::TypeExtCpu::axv2:
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_avx2);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::avx1:
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_avx1);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse4_2:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse4_1:
      //case ::libs::helpers::sys::cpu::TypeExtCpu::eecI64:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse3:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse2:
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_sse2);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse1:
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_sse1);
        break;
#endif
      case ::libs::helpers::sys::cpu::TypeExtCpu::alu:
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_alu);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::usual:
#if defined(UUU_CPU_X86)
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_sse2);
#elif defined(UUU_CPU_ARM)
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_neon);
#else
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_alu);
#endif
        break;
#if defined(UUU_CPU_ARM)
      case ::libs::helpers::sys::cpu::TypeExtCpu::neon:
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_neon);
        break;
#endif
      default:
        UASSERT_SIGNAL ("failed");
        sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_alu);
        break;
      }
    return;
  }
};

}}}}      // namespace dlls::doptim::impl::algs
