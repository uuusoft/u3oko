/**
\file       state-test-indexer.cpp
\author     Erashov Anton erashov2026@proton.me
\date       15.08.2018
*/
#include "../../../../-module-storage-includes-int.hpp"
#include "state-test-indexer.hpp"

namespace modules::mstorage::appl::impl::indexer::test
{
StateTestIndexer::StateTestIndexer (const Acessor& pha)
{
}


auto
StateTestIndexer::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return StateTestIndexer::gen_get_mid ();
}


auto
StateTestIndexer::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< StateTestIndexer > (this, deep);
}


void
StateTestIndexer::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< StateTestIndexer > (src);
  super::copy_int (src);

  objects_ = dsrc->objects_;
}

#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
StateTestIndexer::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_storageoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (objects_);

  self_correct ();
}
#endif
}   // namespace modules::mstorage::appl::impl::indexer::test

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::modules::mstorage::appl::impl::indexer::test::StateTestIndexer);
U3_BOOST_ADD_SERIALIZE_ARCH (::modules::mstorage::appl::impl::indexer::test::StateTestIndexer);
