#pragma once
/**
\file       text-ext-cpu.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::sys::cpu
{
class TextExtCpu final
{
  public:
  TextExtCpu ();

  std::string get_text (const CpuExts& val) const;
  CpuExts     get_val (const std::string& txt) const;

  private:
  //  internal typess
  using str2val_type = boost::unordered_flat_map< std::string, CpuExts >;
  using val2str_type = boost::unordered_flat_map< CpuExts, std::string >;

  str2val_type txt2val_;   //<
  val2str_type val2txt_;   //<
};
}   // namespace libs::utility::sys::cpu
