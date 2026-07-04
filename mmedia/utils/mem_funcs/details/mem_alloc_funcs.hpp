#pragma once
/**
\file       mem_alloc_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_mem_funcs
*/

namespace utils::mem_funcs::details
{
extern "C" BOOST_SYMBOL_EXPORT auto afree (void**) -> void;
extern "C" BOOST_SYMBOL_EXPORT auto aalloc (void**, const std::size_t) -> void;
extern "C" BOOST_SYMBOL_EXPORT auto arealloc (void**, const std::size_t) -> void;
}   // namespace utils::mem_funcs::details
