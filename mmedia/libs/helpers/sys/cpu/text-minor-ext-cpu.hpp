#pragma once
/**
\file       text-minor-ext-cpu.hpp
\author     Erashov Anton erashov2026@proton.me
\date       02.06.2022
\project    u3_helpers_lib
*/

namespace libs::helpers::sys::cpu
{
class TextMinorExtCpu final
{
  public:
  TextMinorExtCpu ();

  std::string  get_text (const CpuMinorExts& val) const;
  CpuMinorExts get_val (const std::string& txt) const;

  private:
  //  internal typess
  using str2val_type = std::unordered_map< std::string, CpuMinorExts >;
  using val2str_type = std::unordered_map< CpuMinorExts, std::string >;

  str2val_type txt2val_;   //<
  val2str_type val2txt_;   //<
};
}   // namespace libs::helpers::sys::cpu
