#pragma once
/**
\file       defines-check-state-turbojpeg-lib.hpp
\author     Erashov Anton erashov2026@proton.me
\date       02.10.2024
*/

namespace dlls::codecs::vcodec_mjpg
{
inline std::string
get_error_text ()
{
  const char* jerr = tjGetErrorStr ();
  return std::string ("jpeg coder ") + std::string (jerr ? jerr : "unknown null turbojpeg error");
}
}   // namespace dlls::codecs::vcodec_mjpg
