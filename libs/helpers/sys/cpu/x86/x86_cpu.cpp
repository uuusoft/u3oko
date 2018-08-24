//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       x86_cpu.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "x86_cpu.hpp"

namespace libs { namespace helpers { namespace sys { namespace cpu { namespace x86 {

#if defined(UUU_CPU_X86)

#if defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)

static inline unsigned long long
_xgetbv (unsigned int index)
{
  unsigned int eax;
  unsigned int edx;
  __asm__ __volatile__("xgetbv"
                       : "=a"(eax), "=d"(edx)
                       : "c"(index));
  return ((unsigned long long)edx << 32) | eax;
}

#endif

std::string
get_text_about_cpu ()
{
  static const unsigned int _regs_eax[] = {
    0x80000002,
    0x80000003,
    0x80000004
  };

  std::string  _ret;
  unsigned int _regs[4];
  char         _buff[1 * 1024];

  _buff[0] = '\0';

  for (std::size_t _indx = 0; _indx < COUNT_OF (_regs_eax); ++_indx)
    {
#if defined(UUU_COMPILER_MSC)
      __cpuid (UUU_MEM_CAST<int*> (_regs), _regs_eax[_indx]);
#else
      __get_cpuid (_regs_eax[_indx], &_regs[0], &_regs[1], &_regs[2], &_regs[3]);
#endif

      *UUU_MEM_CAST<unsigned int*> (_buff + 16 * _indx + 0)  = _regs[0];
      *UUU_MEM_CAST<unsigned int*> (_buff + 16 * _indx + 4)  = _regs[1];
      *UUU_MEM_CAST<unsigned int*> (_buff + 16 * _indx + 8)  = _regs[2];
      *UUU_MEM_CAST<unsigned int*> (_buff + 16 * _indx + 12) = _regs[3];
    }

  _buff[48] = '\0';
  _ret      = _buff;

  UASSERT (!_ret.empty ());
  return _ret;
}


bool
get_exts_cpu (SupportExtensionCPU& _ret)
{
  const unsigned long _def_max_eax = 7;
  unsigned int        _max_eax     = 1;
  unsigned int        _regs[4];

  _ret.reset ();

#if defined(UUU_COMPILER_MSC)
  __cpuid (UUU_MEM_CAST<int*> (_regs), 0);
#else
  __get_cpuid (0, &_regs[0], &_regs[1], &_regs[2], &_regs[3]);
#endif

  _max_eax = UUU_ICAST_UINT (_regs[0]);
  _max_eax = std::min<unsigned int> (_max_eax, _def_max_eax);

  for (unsigned int _check_eax = 1; _check_eax <= _max_eax; ++_check_eax)
    {
      std::vector<TypeExtCpu>   _offs;
      std::vector<int>          _reg_shifts;
      std::vector<unsigned int> _regs_source;
      unsigned long             _edx = 0;
      unsigned long             _ecx = 0;
      unsigned long             _ebx = 0;

#if defined(UUU_COMPILER_MSC)
      __cpuid (UUU_MEM_CAST<int*> (_regs), _check_eax);
#else
      __get_cpuid (_check_eax, &_regs[0], &_regs[1], &_regs[2], &_regs[3]);
#endif

      _ebx = _regs[1];
      _ecx = _regs[2];
      _edx = _regs[3];

      _offs.clear ();

      _reg_shifts.clear ();

      _regs_source.clear ();

      switch (_check_eax)
        {
        case 1:
          {
            _offs.push_back (TypeExtCpu::sse3);
            _reg_shifts.push_back (0);
            _regs_source.push_back (_ecx);

            _offs.push_back (TypeExtCpu::sse4_1);
            _reg_shifts.push_back (19);
            _regs_source.push_back (_ecx);

            _offs.push_back (TypeExtCpu::sse4_2);
            _reg_shifts.push_back (20);
            _regs_source.push_back (_ecx);

            _offs.push_back (TypeExtCpu::fma);
            _reg_shifts.push_back (12);
            _regs_source.push_back (_ecx);

            _offs.push_back (TypeExtCpu::f16c);
            _reg_shifts.push_back (29);
            _regs_source.push_back (_ecx);

            _offs.push_back (TypeExtCpu::avx1);
            _reg_shifts.push_back (28);
            _regs_source.push_back (_ecx);

            _offs.push_back (TypeExtCpu::rdrand);
            _reg_shifts.push_back (30);
            _regs_source.push_back (_ecx);

            _offs.push_back (TypeExtCpu::mmx);
            _reg_shifts.push_back (23);
            _regs_source.push_back (_edx);

            _offs.push_back (TypeExtCpu::sse1);
            _reg_shifts.push_back (25);
            _regs_source.push_back (_edx);

            _offs.push_back (TypeExtCpu::sse2);
            _reg_shifts.push_back (26);
            _regs_source.push_back (_edx);

            break;
          }
        case 7:
          {
            _offs.push_back (TypeExtCpu::axv2);
            _reg_shifts.push_back (5);
            _regs_source.push_back (_ebx);

            break;
          }
        default:
          break;
        }

      UASSERT (_offs.size () == _reg_shifts.size ());
      UASSERT (_offs.size () == _regs_source.size ());

      for (std::size_t _indx = 0; _indx < _offs.size (); ++_indx)
        {
          if (_reg_shifts[_indx] < 0)
            {
              continue;
            }

          if (_regs_source[_indx] & (1 << _reg_shifts[_indx]))
            {
              _ret.set (_offs[_indx]);
            }
        }
    }

  //https://habrahabr.ru/post/99367/
  if (_ret.check (TypeExtCpu::avx1))
    {
      //exended check
      unsigned long _ext_res = 0;

#if defined(UUU_COMPILER_MSC)
      __cpuid (UUU_MEM_CAST<int*> (_regs), 0);
#else
      __get_cpuid (0, &_regs[0], &_regs[1], &_regs[2], &_regs[3]);
#endif

      if (_regs[0] > 1)
        {
#if defined(UUU_COMPILER_MSC)
          __cpuid (UUU_MEM_CAST<int*> (_regs), 1);
#else
          __get_cpuid (1, &_regs[0], &_regs[1], &_regs[2], &_regs[3]);
#endif

          if ((_regs[2] & 0x18000000) == 0x18000000)
            {
              unsigned long long _val = _xgetbv (0);
              if ((_val & 0x6) == 0x6)
                {
                  _ext_res = 1;
                }
            }
        }

#if 0
      _asm
      {
        pushad;
        xor eax, eax;
        cpuid;
        cmp eax, 1      ; Поддерживает ли CPUID параметр eax = 1?
        jb not_supported;
        mov eax, 1;
        cpuid;
        and ecx, 018000000h ; Проверяем, что установлены биты 27 (ОС использует XSAVE/XRSTOR);
        cmp ecx, 018000000h ; и 28 (поддержка AVX процессором);
        jne not_supported;
        xor ecx, ecx    ; Номер регистра XFEATURE_ENABLED_MASK/XCR0 есть 0;
        xgetbv        ; Регистр XFEATURE_ENABLED_MASK теперь в edx:eax;
        and eax, 110b;
        cmp eax, 110b   ; Убеждаемся, что ОС сохраняет AVX регистры при переключении контекста;
        jne not_supported;
        mov eax, 1;
        jmp done;
        ret;
not_supported:
        xor eax, eax;
done:
        lea edx, _ext_res;
        mov [edx], eax;
        popad;
      }
#endif
      if (!_ext_res)
        {
          _ret.clear (TypeExtCpu::avx1);
        }
    }

  if (!_ret.check (TypeExtCpu::avx1))
    {
      //linked
      _ret.clear (TypeExtCpu::fma);
      _ret.clear (TypeExtCpu::axv2);
    }

  return true;
}


bool
get_all_info_cpu (SupportExtensionCPU& _ret)
{
  _ret.reset ();
  CHECK_CALL_NO_THROW (get_exts_cpu (_ret));

  _ret.id_cpu_ = get_text_about_cpu ();
  return true;
}
#endif
}}}}}      // namespace libs::helpers::sys::cpu::x86
