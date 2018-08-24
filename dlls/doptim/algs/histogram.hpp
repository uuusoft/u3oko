#pragma once
/**
\file       histogram.hpp
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
class CHistogramAlg : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.statistics.histogram";

  CHistogramAlg ()
  {
    update (::libs::optim::io::TInit ());
    sel_.set_text (val_key);
  }

  virtual ~CHistogramAlg ()
  {}


  protected:
  virtual void
  update_int (const ::libs::optim::io::TInit& _iinfo) override
  {
    switch (_iinfo.ext_)
      {
#if defined(UUU_CPU_X86)
      case ::libs::helpers::sys::cpu::TypeExtCpu::axv2:
      case ::libs::helpers::sys::cpu::TypeExtCpu::fma:
        sel_.set (::libs::optim::s16bit::statistics::histogram::avx2);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::avx1:
        sel_.set (::libs::optim::s16bit::statistics::histogram::avx1);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse4_2:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse4_1:
      //case ::libs::helpers::sys::cpu::TypeExtCpu::eecI64:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse3:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse2:
        sel_.set (::libs::optim::s16bit::statistics::histogram::sse2);
        sel_.set (::libs::optim::s16bit::statistics::histogram::alu);
        break;
#endif
      case ::libs::helpers::sys::cpu::TypeExtCpu::alu:
        sel_.set (::libs::optim::s16bit::statistics::histogram::alu);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::usual:
#if defined(UUU_CPU_X86)
        sel_.set (::libs::optim::s16bit::statistics::histogram::sse2);
#elif defined(UUU_CPU_ARM)
        sel_.set (::libs::optim::s16bit::statistics::histogram::alu);
#else
        sel_.set (::libs::optim::s16bit::statistics::histogram::alu);
#endif
        break;
#if defined(UUU_CPU_ARM)
      case ::libs::helpers::sys::cpu::TypeExtCpu::neon:
        sel_.set (::libs::optim::s16bit::statistics::histogram::alu);
        break;
#endif
      default:
        UASSERT_SIGNAL ("failed");
        sel_.set (::libs::optim::s16bit::statistics::histogram::alu);
        break;
      }
    return;
  }
};

}}}}      // namespace dlls::doptim::impl::algs
