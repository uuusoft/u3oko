/**
\file       test-indexer-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       25.07.2018
*/
#include "../../../../module-storage-includes_int.hpp"
#include "test-indexer-impl.hpp"

namespace modules::mstorage::appl::impl::indexer::test
{
TestIndexerImpl::~TestIndexerImpl ()
{
  save_state ();
}


auto
TestIndexerImpl::change_state_int (const ImplRuns& state) -> bool
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
TestIndexerImpl::set_info_int (const syn::PathInfo::craw_ptr info)
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
TestIndexerImpl::update_stream_int (syn::UpdateStream::raw_ptr info)
{
  switch (info->action_)
  {
  case ::libs::events_storage::StreamUpdates::open:
    open_stream (info);
    break;
  case ::libs::events_storage::StreamUpdates::close:
    close_stream (info);
    break;
  case ::libs::events_storage::StreamUpdates::change:
    ::libs::utility::checks::throw_ifn (info->stream_id_ != ::libs::events_storage::consts::empty_stream_id);
    break;
  case ::libs::events_storage::StreamUpdates::check_and_get_info:
    ::libs::utility::checks::throw_ifn (info->stream_id_ != ::libs::events_storage::consts::empty_stream_id);
    break;
  default:
    ::libs::utility::checks::throw_exception ("find action " + to_string (info->action_));
    break;
  }

  state_saved_ = false;
}


void
TestIndexerImpl::get_objects_int (std::vector< syn::TypeObjectId >& objs)
{
  objs.clear ();
  objs.reserve (state_->objects_.size ());

  for (auto& obj : state_->objects_)
  {
    objs.push_back (obj.second.id_);
  }
}
}   // namespace modules::mstorage::appl::impl::indexer::test
