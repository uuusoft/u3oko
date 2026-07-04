#pragma once
/**
\file       dbufs-includes.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_dbufs
*/
#include "dbufs-video-syn.hpp"

#include "enum-buf-flags.hpp"
#include "enum-mem-vars.hpp"
#include "ibuf.hpp"
#include "imem-buf.hpp"

#include "video/consts/dbufs-video-const-vals.hpp"
#include "video/consts/offs/dbufs-video-const-offs.hpp"
#include "video/consts/offs/dbufs-is-valid-helpers-funcs.hpp"
#include "video/consts/offs/dbufs-str2eof-helper-funcs.hpp"

#include "video/dim-vars.hpp"
#include "video/enum-dim-checks.hpp"
#include "video/enum-subs.hpp"
#include "video/alloc-params.hpp"
#include "video/ivideo-buf.hpp"

#include "allocator/ibuf-allocator.hpp"
#include "allocator/buf-allocator.hpp"
#include "allocator/buf-allocator-proxy.hpp"

#include "video/helpers/replace-buf-params-funcs.hpp"
#include "video/helpers/buf-dimension-equal-funcs.hpp"
#include "video/helpers/get-data-buf-funcs.hpp"
#include "video/helpers/fill-buf-funcs.hpp"
#include "video/helpers/fill-buf-edges-funcs.hpp"
#include "video/helpers/reset-buf-edges-funcs.hpp"
#include "video/helpers/swap-buf-data-by-rows-funcs.hpp"
