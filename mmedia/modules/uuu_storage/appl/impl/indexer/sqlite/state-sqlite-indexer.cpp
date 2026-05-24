/**
\file       state-sqlite-indexer.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       15.08.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../module-storage-includes_int.hpp"
#include "state-sqlite-indexer.hpp"

namespace modules::uuu_storage::appl::impl::indexer::sqlite
{
StateSqliteIndexer::StateSqliteIndexer (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


StateSqliteIndexer::~StateSqliteIndexer ()
{
}


::libs::events::IEvent::ptr
StateSqliteIndexer::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< StateSqliteIndexer > (this, deep);
}


void
StateSqliteIndexer::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (StateSqliteIndexer);
  super::copy_int (src);
  objects_ = dsrc->objects_;
}


template< class Archive >
void
StateSqliteIndexer::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  ar& BOOST_SERIALIZATION_NVP (objects_);

  self_correct ();
}
}   // namespace modules::uuu_storage::appl::impl::indexer::sqlite

BOOST_CLASS_EXPORT_IMPLEMENT (::modules::uuu_storage::appl::impl::indexer::sqlite::StateSqliteIndexer);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::modules::uuu_storage::appl::impl::indexer::sqlite::StateSqliteIndexer);
