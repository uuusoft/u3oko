#pragma once
/**
\file       module-storage-impl-storage-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       05.09.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::storage::test::consts
{
using consts_val_type = std::uint64_t;

constexpr consts_val_type max_count_session_data_files          = 20 * 1024;           //<
constexpr consts_val_type min_size_session_data_file            = 10 * 1024 * 1024;    //<
constexpr consts_val_type max_size_session_data_file            = 256 * 1024 * 1024;   //<
constexpr consts_val_type max_count_fragments_session_data_file = 128 * 1024;          //<

static_assert (consts::max_size_session_data_file < consts::max_size_session_data_file * consts::max_count_session_data_files);
static_assert (consts::max_count_session_data_files < consts::max_count_session_data_files * consts::max_count_fragments_session_data_file);

const std::string name_seance_info_file    = "seance_state";   //<
const std::string name_ext_index_data_file = "isbd";           //< aka index storage binary data
const std::string name_ext_data_file       = "sbd";            //< aka storage binary data
}   // namespace modules::uuu_storage::appl::impl::storage::test::consts
