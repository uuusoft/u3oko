#pragma once
/**
\file       module-storage-impl-indexer-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       15.08.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::indexer::sqlite
{
constexpr std::uint64_t max_count_records_per_seance = 100 * 1024;   //<
constexpr std::uint64_t max_count_seances_per_object = 1 * 256;      //<
}   // namespace modules::uuu_storage::appl::impl::indexer::sqlite
