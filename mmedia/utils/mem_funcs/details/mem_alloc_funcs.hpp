#pragma once
/**
\file       mem_alloc_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_mem_funcs
*/

namespace utils::mem_funcs::details
{
extern "C" BOOST_SYMBOL_EXPORT void afree (void** pptr);
extern "C" BOOST_SYMBOL_EXPORT void aalloc (void** pptr, const std::size_t size);
extern "C" BOOST_SYMBOL_EXPORT void arealloc (void** pptr, const std::size_t size);
}   // namespace utils::mem_funcs::details
