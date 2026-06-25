/*
\file       text-ext-dsp.cpp
\date       02.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../helpers-lib-includes_int.hpp"
#include "text-ext-dsp.hpp"

namespace libs::helpers::sys::cpu
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


std::string
TextExtDsp::get_text (const DspExts& val) const
{
  auto it = val2txt_.find (val);

  if (it == val2txt_.end ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return std::string ("???");
  }

  U3_ASSERT (!it->second.empty ());
  return it->second;
}


DspExts
TextExtDsp::get_val (const std::string& txt) const
{
  U3_ASSERT (!txt.empty ());
  auto it = txt2val_.find (txt);

  if (it == txt2val_.end ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return DspExts::usual;
  }
  return it->second;
}
}   // namespace libs::helpers::sys::cpu
