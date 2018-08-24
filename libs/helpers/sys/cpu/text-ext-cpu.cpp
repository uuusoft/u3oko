//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       text-ext-cpu.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "text-ext-cpu.hpp"

namespace libs { namespace helpers { namespace sys { namespace cpu {

TextExtCpu::TextExtCpu ()
{
  static const std::string _txts[] =
    {
      "default", "max", "min", "alu", "sse2", "sse3", "sse4.1", "sse4.2", "avx1", "avx2", "fma", "neon", "f16c", "rdrand", "hex4", "hex5", "hex6"
    };

  static const TypeExtCpu _exts[] =
    {
      TypeExtCpu::usual, TypeExtCpu::max, TypeExtCpu::min, TypeExtCpu::alu, TypeExtCpu::sse2, TypeExtCpu::sse3, TypeExtCpu::sse4_1, TypeExtCpu::sse4_2, TypeExtCpu::avx1, TypeExtCpu::axv2, TypeExtCpu::fma, TypeExtCpu::neon, TypeExtCpu::f16c, TypeExtCpu::rdrand, TypeExtCpu::hexagon4, TypeExtCpu::hexagon5, TypeExtCpu::hexagon6
    };


  for (std::size_t _indx = 0; _indx < COUNT_OF (_txts); ++_indx)
    {
      txt2val_.insert (std::pair<std::string, TypeExtCpu> (_txts[_indx], _exts[_indx]));
      val2txt_.insert (std::pair<TypeExtCpu, std::string> (_exts[_indx], _txts[_indx]));
    }
  return;
}


std::string
TextExtCpu::get_text (const TypeExtCpu& _val) const
{
  auto _it = val2txt_.find (_val);

  if (_it == val2txt_.end ())
    {
      UASSERT_SIGNAL ("failed");
      return std::string ("???");
    }

  UASSERT (!_it->second.empty ());
  return _it->second;
}


TypeExtCpu
TextExtCpu::get_val (const std::string& _txt) const
{
  UASSERT (!_txt.empty ());
  auto _it = txt2val_.find (_txt);

  if (_it == txt2val_.end ())
    {
      UASSERT_SIGNAL ("failed");
      return TypeExtCpu::usual;
    }
  return _it->second;
}

}}}}      // namespace libs::helpers::sys::cpu
