#pragma once
/**
\file       -module-log-includes.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/
// EAI-REFACT
#include "mmedia/libs/proxy/proxy/ievents-proxy.hpp"

#include "to-log.hpp"

#include "defines/defines-helper-http-log-calls.hpp"
#include "defines/defines-helper-events-log-calls.hpp"
#include "defines/defines-helper-gui-log-calls.hpp"
#include "defines/defines-helper-data-log-calls.hpp"
#include "defines/defines-helper-storage-log-calls.hpp"
#include "defines/defines-helper-appl-log-calls.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_mpl_mlog () -> ::libs::link::appl::IApplication*;
extern "C" BOOST_SYMBOL_EXPORT auto delete_impl_mpl_mlog (::libs::link::appl::IApplication*) -> void;
