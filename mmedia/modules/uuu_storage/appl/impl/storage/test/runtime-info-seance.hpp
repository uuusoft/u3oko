#pragma once
/**
\file       runtime-info-seance.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       05.09.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::storage::test
{
struct RuntimeInfoSeance final {
  U3_HELPER_DISABLE_ACOPY_TYPE (RuntimeInfoSeance)

  RuntimeInfoSeance ()
  {
  }

  ~RuntimeInfoSeance ()
  {
    reset ();
  }

  void
  reset ()
  {
    state_.reset ();
    cursor_.reset ();
    index_state_.reset ();
    data_file_.close ();
    size_data_file_ = 0;
  }

  StoredInfoSeance            state_;                //<
  IStorageImpl::id_chunk_type cursor_;               //<
  IndexDataFileState          index_state_;          //<
  std::ofstream               data_file_;            //<
  std::uint64_t               size_data_file_ = 0;   //<
};
}   // namespace modules::uuu_storage::appl::impl::storage::test
