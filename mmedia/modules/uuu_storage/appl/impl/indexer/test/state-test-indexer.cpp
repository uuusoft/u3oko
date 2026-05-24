/**
\file       state-test-indexer.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       15.08.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../module-storage-includes_int.hpp"
#include "state-test-indexer.hpp"

namespace modules::uuu_storage::appl::impl::indexer::test
{
StateTestIndexer::StateTestIndexer (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


StateTestIndexer::~StateTestIndexer ()
{
}


::libs::events::IEvent::ptr
StateTestIndexer::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< StateTestIndexer > (this, deep);
}


void
StateTestIndexer::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (StateTestIndexer);
  super::copy_int (src);
  objects_ = dsrc->objects_;
}


template< class Archive >
void
StateTestIndexer::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  ar& BOOST_SERIALIZATION_NVP (objects_);

  self_correct ();
}
}   // namespace modules::uuu_storage::appl::impl::indexer::test

BOOST_CLASS_EXPORT_IMPLEMENT (::modules::uuu_storage::appl::impl::indexer::test::StateTestIndexer);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::modules::uuu_storage::appl::impl::indexer::test::StateTestIndexer);
