/**
\file       dbufs-str2eof-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       09.03.2022
*/
#include "../../../dbufs-includes_int.hpp"
#include "dbufs-str2eof-helper-funcs.hpp"

namespace utils::dbufs::video::consts::offs
{
auto
str2eoffbuf (const std::string& key) -> const off_buf_type
{
  static const boost::unordered_flat_map< std::string, const off_buf_type, ::libs::utility::utils::TransparentStringHash, std::equal_to<> > valmap = {
    { "", invalid },
    { "-", invalid },
    { "?", invalid },
    { "??", invalid },
    { "???", invalid },
    { std::string (invalid), invalid }
  };

  auto finger = valmap.find (key);
  if (valmap.end () == finger)
  {
    finger = valmap.find (std::string (invalid));
  }
  return finger->second;
}
}   // namespace utils::dbufs::video::consts::offs
