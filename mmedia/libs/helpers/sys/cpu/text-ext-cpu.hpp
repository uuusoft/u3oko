#pragma once
/**
\file       text-ext-cpu.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::sys::cpu
{
class TextExtCpu final
{
  public:
  TextExtCpu ();

  std::string get_text (const CpuExts& val) const;
  CpuExts     get_val (const std::string& txt) const;

  private:
  //  internal typess
  using str2val_type = std::unordered_map< std::string, CpuExts >;
  using val2str_type = std::unordered_map< CpuExts, std::string >;

  str2val_type txt2val_;   //<
  val2str_type val2txt_;   //<
};
}   // namespace libs::helpers::sys::cpu
