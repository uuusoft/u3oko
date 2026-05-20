/**
\file       dbufs-str2eof-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       09.03.2022
\project    u3_dbufs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../dbufs-includes_int.hpp"
#include "dbufs-str2eof-helper-funcs.hpp"

namespace utils::dbufs::video::consts::offs
{
const off_buf_type&
str2eoffbuf (const std::string& key)
{
  static const std::unordered_map< std::string, const off_buf_type > valmap = {
    { "", invalid },
    { "-", invalid },
    { "?", invalid },
    { "??", invalid },
    { "???", invalid },
    { invalid, invalid }
  };

  auto finger = valmap.find (key);
  if (valmap.end () == finger)
  {
    finger = valmap.find (invalid);
  }
  return finger->second;
}
}   // namespace utils::dbufs::video::consts::offs
