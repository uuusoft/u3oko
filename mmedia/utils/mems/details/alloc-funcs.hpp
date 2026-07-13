#pragma once
/**
\file       alloc-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_mems
*/

namespace utils::mems::details
{
extern "C" BOOST_SYMBOL_EXPORT auto afree (void**) -> void;
extern "C" BOOST_SYMBOL_EXPORT auto aalloc (void**, const std::size_t) -> void;
extern "C" BOOST_SYMBOL_EXPORT auto arealloc (void**, const std::size_t) -> void;
}   // namespace utils::mems::details
