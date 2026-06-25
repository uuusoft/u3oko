#pragma once
/**
\file       path-usings-enum.hpp
\date       22.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::modules::storage
{
enum class PathUsings : std::uint32_t
{
  disabled   = 0x00,   //<
  read_only  = 0x01,   //<
  write_only = 0x02,   //<
  read_write = 0x03,   //<
  unknown    = 0xFF    //<
};

PathUsings str2using_path (const std::string& str);
void       tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const PathUsings& src);
PathUsings tag_invoke (::boost::json::value_to_tag< PathUsings >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::modules::storage
