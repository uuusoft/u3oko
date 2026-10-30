/*
\file       text-ext-dsp.cpp
\date       02.06.2022
\author     Erashov Anton erashov2026@proton.me
*/
#include "../../utility-lib-includes_int.hpp"
#include "text-ext-dsp.hpp"

namespace libs::utility::sys::cpu
{
TextExtDsp::TextExtDsp ()
{
  static const std::string txts[] = {
    "default", "hex4", "hex5", "hex6"
  };

  static const DspExts exts[] = {
    DspExts::usual, DspExts::hexagon4, DspExts::hexagon5, DspExts::hexagon6
  };

  for (std::size_t indx = 0; indx < std::size (txts); ++indx)
  {
    txt2val_.insert (std::pair< std::string, DspExts > (txts[indx], exts[indx]));
    val2txt_.insert (std::pair< DspExts, std::string > (exts[indx], txts[indx]));
  }
}


auto
TextExtDsp::get_text (const DspExts& val) const -> std::string
{
  auto it = val2txt_.find (val);

  if (it == val2txt_.end ())
  {
    ::libs::utility::checks::mark ("failed");
    return std::string ("???");
  }

  ::libs::utility::checks::throw_ifn (!it->second.empty ());
  return it->second;
}


auto
TextExtDsp::get_val (const std::string& txt) const -> DspExts
{
  ::libs::utility::checks::throw_ifn (!txt.empty ());
  auto it = txt2val_.find (txt);

  if (it == txt2val_.end ())
  {
    ::libs::utility::checks::throw_exception ("failed");
    return DspExts::usual;
  }
  return it->second;
}
}   // namespace libs::utility::sys::cpu
