#pragma once
/**
\file       -module-events-includes.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_mpl_mevents () -> ::libs::link::appl::IApplication*;
extern "C" BOOST_SYMBOL_EXPORT auto delete_impl_mpl_mevents (::libs::link::appl::IApplication*) -> void;
