#pragma once
/**
\file       -module-storage-includes.hpp
\date       23.07.2018
\author     Erashov Anton erashov2026@proton.me
*/

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_mpl_mstorage () -> ::libs::link::appl::IApplication*;
extern "C" BOOST_SYMBOL_EXPORT auto delete_impl_mpl_mstorage (::libs::link::appl::IApplication*) -> void;
