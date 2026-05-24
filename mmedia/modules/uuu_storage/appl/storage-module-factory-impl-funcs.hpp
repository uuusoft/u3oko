#pragma once
/**
\file       storage-module-factory-impl-funcs.hpp
\date       11.08.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl
{
inline impl::IStorageImpl::ptr
get_storage_impl ()
{
  impl::IStorageImpl::ptr ret = std::make_shared< impl::storage::test::TestStorageImpl > ("test path2data");
  return ret;
}

inline impl::IIndexerImpl::ptr
get_indexer_impl ()
{
#ifndef U3_DBG_EXTERNAL_LIB_SKIP_SQLITE
  impl::IIndexerImpl::ptr ret = std::make_shared< impl::indexer::sqlite::SqliteIndexerImpl > ();
#else
  impl::IIndexerImpl::ptr ret = std::make_shared< impl::indexer::test::TestIndexerImpl > ();
#endif
  return ret;
}
}   // namespace modules::uuu_storage::appl
