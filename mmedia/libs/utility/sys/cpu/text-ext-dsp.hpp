#pragma once
/**
\file       text-ext-dsp.hpp
\author     Erashov Anton erashov2026@proton.me
\date       02.06.2022
\project    u3_helpers_lib
*/

namespace libs::utility::sys::cpu
{
class TextExtDsp final
{
  public:
  TextExtDsp ();

  std::string get_text (const DspExts& val) const;
  DspExts     get_val (const std::string& txt) const;

  private:
  //  internal typess
  using str2val_type = boost::unordered_flat_map< std::string, DspExts >;
  using val2str_type = boost::unordered_flat_map< DspExts, std::string >;

  str2val_type txt2val_;   //<
  val2str_type val2txt_;   //<
};
}   // namespace libs::utility::sys::cpu
