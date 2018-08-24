#pragma once
/**
\file       nv212y16.hpp
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
class CNV212Y16Alg : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.convert.nv21_y16";

  CNV212Y16Alg ()
  {
    update (::libs::optim::io::TInit ());
    sel_.set_text (val_key);
  }

  virtual ~CNV212Y16Alg ()
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
        sel_.set (::libs::optim::convert::nv21_y16::avx2);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::avx1:
        sel_.set (::libs::optim::convert::nv21_y16::sse2);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse4_2:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse4_1:
      //case ::libs::helpers::sys::cpu::TypeExtCpu::eecI64:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse3:
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse2:
        sel_.set (::libs::optim::convert::nv21_y16::sse2);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::sse1:
        sel_.set (::libs::optim::convert::nv21_y16::alu);
        break;
#endif
      case ::libs::helpers::sys::cpu::TypeExtCpu::alu:
        sel_.set (::libs::optim::convert::nv21_y16::alu);
        break;
      case ::libs::helpers::sys::cpu::TypeExtCpu::usual:
#if defined(UUU_CPU_X86)
        sel_.set (::libs::optim::convert::nv21_y16::sse2);
#elif defined(UUU_CPU_ARM)
        sel_.set (::libs::optim::convert::nv21_y16::neon);
#else
        sel_.set (::libs::optim::convert::nv21_y16::alu);
#endif
        break;
#if defined(UUU_CPU_ARM)
      case ::libs::helpers::sys::cpu::TypeExtCpu::neon:
        sel_.set (::libs::optim::convert::nv21_y16::neon);
        break;
#endif
      default:
        UASSERT_SIGNAL ("failed");
        sel_.set (::libs::optim::convert::nv21_y16::alu);
        break;
      }
    return;
  }
};

}}}}      // namespace dlls::doptim::impl::algs
