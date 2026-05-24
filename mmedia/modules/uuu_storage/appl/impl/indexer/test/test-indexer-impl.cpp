/**
\file       test-indexer-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       25.07.2018
\project    u3_module_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../module-storage-includes_int.hpp"
#include "test-indexer-impl.hpp"

namespace modules::uuu_storage::appl::impl::indexer::test
{
TestIndexerImpl::TestIndexerImpl () :
  state_ (std::make_shared< StateTestIndexer > ()),
  state_saved_ (true)
{
}


TestIndexerImpl::~TestIndexerImpl ()
{
  save_state ();
}


bool
TestIndexerImpl::change_state_int (const ImplRuns& state)
{
  switch (state)
  {
  case ImplRuns::run:
    load_state ();
    break;
  case ImplRuns::stop:
    save_state ();
    break;
  default:
    U3_XLOG_WARN ("unknown change state" + VTOLOG (U3_CAST_UINT32_FORCE (state)));
    return false;
  }
  return true;
}


void
TestIndexerImpl::set_info_int (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info)
{
  if (info)
  {
    info_ = *info;
  }
  update_path ();
  save_state ();   //  save probably previous state
  load_state ();
  state_saved_ = false;
}


void
TestIndexerImpl::update_stream_int (::libs::istorage_events::events::UpdateStream::raw_ptr info)
{
  switch (info->action_)
  {
  case ::libs::istorage_events::StreamUpdates::open:
    open_stream (info);
    break;
  case ::libs::istorage_events::StreamUpdates::close:
    close_stream (info);
    break;
  case ::libs::istorage_events::StreamUpdates::change:
    U3_ASSERT (info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
    break;
  case ::libs::istorage_events::StreamUpdates::check_and_get_info:
    U3_ASSERT (info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
    break;
  default:
    U3_ASSERT_SIGNAL ("find action " + to_string (info->action_));
    break;
  }

  state_saved_ = false;
}


void
TestIndexerImpl::get_objects_int (std::vector< ::libs::istorage_events::TypeObjectId >& objs)
{
  objs.clear ();
  objs.reserve (state_->objects_.size ());

  for (auto& obj : state_->objects_)
  {
    objs.push_back (obj.second.id_);
  }
}
}   // namespace modules::uuu_storage::appl::impl::indexer::test
