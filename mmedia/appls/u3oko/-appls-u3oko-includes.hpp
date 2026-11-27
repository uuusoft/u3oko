#pragma once
/**
\file       -appls-u3oko-includes.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_appl_u3oko () -> ::libs::link::appl::IApplication*;
extern "C" BOOST_SYMBOL_EXPORT auto delete_impl_appl_u3oko (::libs::link::appl::IApplication*) -> void;
