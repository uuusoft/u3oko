#pragma once
/**
\file       libs-bufs-syn.hpp
\date       09.03.2026
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::bufs::syn
{
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
using off_buf_type            = ::utils::dbufs::video::consts::offs::off_buf_type;
using IVideoBuf               = ::utils::dbufs::video::IVideoBuf;

namespace offs = utils::dbufs::video::consts::offs;
}   // namespace libs::bufs::syn
