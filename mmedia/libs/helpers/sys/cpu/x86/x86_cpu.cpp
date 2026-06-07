/**
\file       x86_cpu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../helpers-lib-includes_int.hpp"
#include "x86_cpu.hpp"

// U3-REFACT

#ifdef U3_CPU_X86

namespace libs::helpers::sys::cpu::x86
{
#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
uint64_t
fxgetbv (uint32_t index)
{
  std::uint32_t eax;
  std::uint32_t edx;

  __asm__ __volatile__ ("xgetbv"
                        : "=a"(eax), "=d"(edx)
                        : "c"(index));
  return ((uint64_t) edx << 32) | eax;
}
#  endif


std::string
get_text_about_cpu ()
{
  static const std::uint32_t regs_eax[] = {
    0x80000002,
    0x80000003,
    0x80000004
  };

  std::string   ret;
  std::uint32_t regs[4];
  char          buf[1 * 1024];

  buf[0] = '\0';

  for (std::size_t indx = 0; indx < std::size (regs_eax); ++indx)
  {
#  if defined(U3_COMPILER_MSC)
    __cpuid (::libs::helpers::casts::reinterpret_cast_helper< std::int32_t* > (regs), regs_eax[indx]);
#  else
    __get_cpuid (regs_eax[indx], &regs[0], &regs[1], &regs[2], &regs[3]);
#  endif

    *::libs::helpers::casts::reinterpret_cast_helper< std::uint32_t* > (buf + 16 * indx + 0)  = regs[0];
    *::libs::helpers::casts::reinterpret_cast_helper< std::uint32_t* > (buf + 16 * indx + 4)  = regs[1];
    *::libs::helpers::casts::reinterpret_cast_helper< std::uint32_t* > (buf + 16 * indx + 8)  = regs[2];
    *::libs::helpers::casts::reinterpret_cast_helper< std::uint32_t* > (buf + 16 * indx + 12) = regs[3];
  }

  buf[48] = '\0';
  ret     = buf;

  U3_ASSERT (!ret.empty ());
  return ret;
}


bool
get_exts_cpu (SupportExtensionCPU& ret)
{
  const unsigned long def_max_eax = 7;
  std::uint32_t       max_eax     = 1;
  std::uint32_t       regs[4];

  ret.reset ();

#  if defined(U3_COMPILER_MSC)
  __cpuid (::libs::helpers::casts::reinterpret_cast_helper< std::int32_t* > (regs), 0);
#  else
  __get_cpuid (0, &regs[0], &regs[1], &regs[2], &regs[3]);
#  endif

  max_eax = U3_CAST_UINT32 (regs[0]);
  max_eax = std::min< std::uint32_t > (max_eax, def_max_eax);

  for (uint32_t check_eax = 1; check_eax <= max_eax; ++check_eax)
  {
    std::vector< CpuExts >       offs;
    std::vector< std::int32_t >  reg_shifts;
    std::vector< std::uint32_t > regs_source;
    std::vector< CpuMinorExts >  minor_offs;
    std::vector< std::int32_t >  minor_reg_shifts;
    std::vector< std::uint32_t > minor_regs_source;
    unsigned long                edx = 0;
    unsigned long                ecx = 0;
    unsigned long                ebx = 0;

#  if defined(U3_COMPILER_MSC)
    __cpuid (::libs::helpers::casts::reinterpret_cast_helper< std::int32_t* > (regs), check_eax);
#  else
    __get_cpuid (check_eax, &regs[0], &regs[1], &regs[2], &regs[3]);
#  endif

    ebx = regs[1];
    ecx = regs[2];
    edx = regs[3];

    switch (check_eax)
    {
    case 1: {
      offs.push_back (CpuExts::sse3);
      reg_shifts.push_back (0);
      regs_source.push_back (ecx);

      offs.push_back (CpuExts::sse4_1);
      reg_shifts.push_back (19);
      regs_source.push_back (ecx);

      offs.push_back (CpuExts::sse4_2);
      reg_shifts.push_back (20);
      regs_source.push_back (ecx);

      minor_offs.push_back (CpuMinorExts::fma);
      minor_reg_shifts.push_back (12);
      minor_regs_source.push_back (ecx);

      minor_offs.push_back (CpuMinorExts::f16c);
      minor_reg_shifts.push_back (29);
      minor_regs_source.push_back (ecx);

      offs.push_back (CpuExts::avx1);
      reg_shifts.push_back (28);
      regs_source.push_back (ecx);

      minor_offs.push_back (CpuMinorExts::rdrand);
      minor_reg_shifts.push_back (30);
      minor_regs_source.push_back (ecx);

      offs.push_back (CpuExts::mmx);
      reg_shifts.push_back (23);
      regs_source.push_back (edx);

      offs.push_back (CpuExts::sse1);
      reg_shifts.push_back (25);
      regs_source.push_back (edx);

      offs.push_back (CpuExts::sse2);
      reg_shifts.push_back (26);
      regs_source.push_back (edx);
      break;
    }
    case 7: {
      offs.push_back (CpuExts::avx2);
      reg_shifts.push_back (5);
      regs_source.push_back (ebx);
      break;
    }
    default:
      break;
    }

    U3_ASSERT (offs.size () == reg_shifts.size ());
    U3_ASSERT (offs.size () == regs_source.size ());

    for (std::size_t indx = 0; indx < offs.size (); ++indx)
    {
      if (reg_shifts[indx] < 0)
      {
        continue;
      }
      if (regs_source[indx] & (1 << reg_shifts[indx]))
      {
        ret.set (offs[indx]);
      }
    }

    U3_ASSERT (minor_offs.size () == minor_reg_shifts.size ());
    U3_ASSERT (minor_offs.size () == minor_regs_source.size ());

    for (std::size_t indx = 0; indx < minor_offs.size (); ++indx)
    {
      if (minor_reg_shifts[indx] < 0)
      {
        continue;
      }
      if (minor_regs_source[indx] & (1 << minor_reg_shifts[indx]))
      {
        ret.set (minor_offs[indx]);
      }
    }
  }

  // https://habrahabr.ru/post/99367/
  if (ret.check (CpuExts::avx1))
  {
    // exended check
    unsigned long ext_res = 0;

#  if defined(U3_COMPILER_MSC)
    __cpuid (::libs::helpers::casts::reinterpret_cast_helper< std::int32_t* > (regs), 0);
#  else
    __get_cpuid (0, &regs[0], &regs[1], &regs[2], &regs[3]);
#  endif

    if (regs[0] > 1)
    {
#  if defined(U3_COMPILER_MSC)
      __cpuid (::libs::helpers::casts::reinterpret_cast_helper< std::int32_t* > (regs), 1);
#  else
      __get_cpuid (1, &regs[0], &regs[1], &regs[2], &regs[3]);
#  endif

      if ((regs[2] & 0x18000000) == 0x18000000)
      {
#  if defined(U3_COMPILER_MSC)
        std::uint64_t val = _xgetbv (0);
#  else
        std::uint64_t val = fxgetbv (0);
#  endif
        if ((val & 0x6) == 0x6)
        {
          ext_res = 1;
        }
      }
    }

    if (!ext_res)
    {
      ret.clear (CpuExts::avx1);
    }
  }

  if (!ret.check (CpuExts::avx1))
  {
    // linked
    ret.clear (CpuMinorExts::fma);
    ret.clear (CpuExts::avx2);
  }
  return true;
}


bool
get_all_info_cpu (SupportExtensionCPU& ret)
{
  ret.reset ();
  U3_CHECK_NT (get_exts_cpu (ret), "get_all_info_cpu");

  ret.id_cpu_ = get_text_about_cpu ();
  return true;
}
}   // namespace libs::helpers::sys::cpu::x86

#endif
