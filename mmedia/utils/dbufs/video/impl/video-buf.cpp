/**
\file         video-buf.cpp
\date         26.07.2016
\author       Erashov Anton erashov2026@proton.me
\project      u3_dbufs
\brief        Реализация буфера под видео.
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../dbufs-includes_int.hpp"
#include "video-buf.hpp"

namespace utils::dbufs::video::impl
{
VideoBuf::VideoBuf ()
{
  flush ();
}


VideoBuf::~VideoBuf ()
{
}
}   // namespace utils::dbufs::video::impl
