#pragma once
/**
\file       subs-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       30.07.2018
\project    u3_dbufs
*/

namespace utils::dbufs::video
{
enum class Subs : std::uint32_t
{
  sub_444 = 0x00,   //< YUV444
  sub_422 = 0x01,   //< YUV422
  sub_420 = 0x02,   //< YUV420
  sub_440 = 0x03,   //< YUV440
  sub_441 = 0x04,   //< YUV441
  unknown = 0xFF    //<
};
}   // namespace utils::dbufs::video
