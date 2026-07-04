/**
\file         video-buf.cpp
\date         26.07.2016
\author       Erashov Anton erashov2026@proton.me
\project      u3_dbufs
\brief        Реализация буфера под видео
*/
#include "../../dbufs-includes_int.hpp"
#include "video-buf.hpp"

namespace utils::dbufs::video::impl
{
VideoBuf::VideoBuf ()
{
  flush ();
}
}   // namespace utils::dbufs::video::impl
