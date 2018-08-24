//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       cpu-info.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "x86/x86_cpu.hpp"
#include "arm/arm_cpu.hpp"

namespace libs { namespace helpers { namespace sys { namespace cpu {

CpuInfo::CpuInfo ()
{
  ext_cpu_ranged_.reserve (128);

  ext_cpu_ranged_.push_back (TypeExtCpu::hexagon6);
  ext_cpu_ranged_.push_back (TypeExtCpu::hexagon5);
  ext_cpu_ranged_.push_back (TypeExtCpu::hexagon4);
  ext_cpu_ranged_.push_back (TypeExtCpu::neon);
  ext_cpu_ranged_.push_back (TypeExtCpu::axv2);
  ext_cpu_ranged_.push_back (TypeExtCpu::fma);
  ext_cpu_ranged_.push_back (TypeExtCpu::avx1);
  ext_cpu_ranged_.push_back (TypeExtCpu::sse4_2);
  ext_cpu_ranged_.push_back (TypeExtCpu::sse4_1);
  ext_cpu_ranged_.push_back (TypeExtCpu::sse3);
  ext_cpu_ranged_.push_back (TypeExtCpu::sse2);

  //ext_cpu_ranged_.push_back(TypeExtCpu::sse1 );
  //ext_cpu_ranged_.push_back(TypeExtCpu::mmx);

  all_ext_.reserve (128);

  std::copy (ext_cpu_ranged_.rbegin (), ext_cpu_ranged_.rend (), back_inserter (all_ext_));

  all_ext_.push_back (TypeExtCpu::f16c);
  all_ext_.push_back (TypeExtCpu::rdrand);


#if defined(UUU_CPU_X86)
  CHECK_CALL (x86::get_all_info_cpu (exts_), "failed get info cpu");
#elif defined(UUU_CPU_ARM)
  CHECK_CALL (arm::get_all_info_cpu (exts_), "failde get info cpu");
#else
#error "unknow cpu"
#endif

  return;
}


TypeExtCpu
CpuInfo::get_max () const
{
  for (const TypeExtCpu& _ext : ext_cpu_ranged_)
    {
      if (exts_.check (_ext))
        {
          return _ext;
        }
    }
  return TypeExtCpu::usual;
}


TypeExtCpu
CpuInfo::get_min () const
{
  TypeExtCpu _ret = TypeExtCpu::usual;

  for (const TypeExtCpu& _ext : ext_cpu_ranged_)
    {
      if (exts_.check (_ext))
        {
          _ret = _ext;
        }
    }

  return _ret;
}


bool
CpuInfo::is_less (const TypeExtCpu& _op1, const TypeExtCpu& _op2) const
{
  for (const TypeExtCpu& _ext : ext_cpu_ranged_)
    {
      if (_ext == _op1)
        {
          return false;
        }
      if (_ext == _op2)
        {
          return true;
        }
    }

  UASSERT_SIGNAL ("failed");
  return false;
}


void
CpuInfo::full_text (std::string& _info)
{
  _info.reserve (512);

  _info = "cpu ";

#if defined(UUU_CPU_X86)

  _info += x86::get_text_about_cpu ();

#elif defined(UUU_CPU_ARM)

  _info += arm::get_text_about_cpu ();

#else
#error
#endif

  _info += "\n";
  _info += "ext: ";

  for (const TypeExtCpu& _ext : all_ext_)
    {
#if 1
      if (!exts_.check (_ext))
        {
          continue;
        }

      _info += texter_.get_text (_ext);
      _info += " ";
#else
      _info += texter_.get_text (_ext);
      _info += exts_.check (_ext) ? "+" : "-";
      _info += " ";
#endif
    }

  return;
}

}}}}      // namespace libs::helpers::sys::cpu
