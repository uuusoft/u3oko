/**
\file       test-indexer-impl-int-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       21.08.2018
*/
#include "../../../../module-storage-includes_int.hpp"
#include "test-indexer-impl.hpp"

namespace modules::mstorage::appl::impl::indexer::test::details
{
inline auto
get_name_state_file () -> std::string
{
  return "state_impl.bin";
}
}   // namespace modules::mstorage::appl::impl::indexer::test::details

namespace modules::mstorage::appl::impl::indexer::test
{
void
TestIndexerImpl::update_path ()
{
  if (!root_path_.empty ())
  {
    return;
  }

  auto* osprops = ::libs::iproperties::helpers::get_shared_prop_os ();
  auto  iappl   = osprops->get_paths_lockfree ();
  root_path_    = info_.path2data_;

  if (root_path_.empty ())
  {
    auto path  = iappl->get_path (::libs::iproperties::appl_paths::Paths::active_storage_module);
    root_path_ = ::libs::utility::files::make_path (path, std::string ("test-indexer"));
  }
  ::libs::utility::files::create_folder (root_path_);
}


void
TestIndexerImpl::load_state ()
{
  const auto    file_name = details::get_name_state_file ();
  const auto    full_path = ::libs::utility::files::make_path (root_path_, file_name);
  std::ifstream file (full_path, std::ios::binary);

  state_saved_ = false;

  if (!file.is_open ())
  {
    return;
  }

  try
  {
#if (U3_USE_BOOST_SERIALIZTION)
    boost::archive::xml_iarchive xmla (file, boost::archive::no_header);
    xmla&                        BOOST_SERIALIZATION_NVP (state_);
#else
    ::libs::utility::checks::throw_ifn (0);
#endif
  }
  catch (std::exception& excpt)
  {
    U3_LOG_STORAGE_EXCEPT (excpt.what ());
  }
}


void
TestIndexerImpl::save_state ()
{
  if (state_saved_)
  {
    return;
  }

  const auto    file_name = details::get_name_state_file ();
  const auto    full_path = ::libs::utility::files::make_path (root_path_, file_name);
  std::ofstream file (full_path, std::ios::binary | std::ios::trunc);

  if (!file.is_open ())
  {
    U3_XLOG_ERROR ("open file for save state path=" + full_path);
    return;
  }

  try
  {
#if (U3_USE_BOOST_SERIALIZTION)
    boost::archive::xml_oarchive xmla (file, boost::archive::no_header);
    xmla&                        BOOST_SERIALIZATION_NVP (state_);
#else
    ::libs::utility::checks::throw_ifn (0);
#endif
  }
  catch (std::exception& excpt)
  {
    U3_LOG_STORAGE_EXCEPT (excpt.what ());
    return;
  }

  state_saved_ = true;
}


void
TestIndexerImpl::open_stream (syn::UpdateStream::raw_ptr info)
{
  ::libs::utility::checks::throw_ifn (info->stream_id_ == ::libs::events_storage::consts::empty_stream_id);
  ::libs::utility::checks::throw_ifn (info->obj_id_.is_valid ());

  info->stream_id_ = boost::uuids::random_generator () ();
  ::libs::utility::checks::throw_ifn (info->stream_id_ != ::libs::events_storage::consts::empty_stream_id);
  auto& obj_state = state_->objects_[info->obj_id_];

  obj_state.streams_.emplace_back (info->stream_id_);
  state_saved_ = false;
}


void
TestIndexerImpl::close_stream (syn::UpdateStream::raw_ptr info)
{
  ::libs::utility::checks::throw_ifn (info->stream_id_ != ::libs::events_storage::consts::empty_stream_id);
}
}   // namespace modules::mstorage::appl::impl::indexer::test
