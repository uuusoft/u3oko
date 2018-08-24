//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       state-test-indexer.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       15.08.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "state-test-indexer.hpp"

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {

StateTestIndexer::StateTestIndexer (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


StateTestIndexer::~StateTestIndexer ()
{}


::libs::events::IEvent::ptr
StateTestIndexer::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<StateTestIndexer> (this, _deep);
}


void
StateTestIndexer::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (StateTestIndexer);
  super::copy_int (_src);
  objects_ = _dsrc->objects_;
  return;
}


template <class Archive>
void
StateTestIndexer::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (objects_);
  return;
}

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test

BOOST_CLASS_EXPORT_IMPLEMENT (::modules::uuu_storage::appl::impl::indexer::test::StateTestIndexer);
SERIALIZE_TYPE_TO_ARCHIVES (::modules::uuu_storage::appl::impl::indexer::test::StateTestIndexer);
