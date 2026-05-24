/**
\file       test-indexer-impl-int-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.08.2018
\project    u3_module_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../module-storage-includes_int.hpp"
#include "test-indexer-impl.hpp"

namespace modules::uuu_storage::appl::impl::indexer::test::details
{
inline std::string
get_name_state_file ()
{
  return "state_impl.bin";
}
}   // namespace modules::uuu_storage::appl::impl::indexer::test::details

namespace modules::uuu_storage::appl::impl::indexer::test
{
void
TestIndexerImpl::update_path ()
{
  if (!root_path_.empty ())
  {
    return;
  }

  auto iappl = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
  root_path_ = info_.path2data_;

  if (root_path_.empty ())
  {
    auto path  = iappl->get_path (::libs::iproperties::appl_paths::Paths::active_storage_module);
    root_path_ = ::libs::helpers::files::make_path (path, std::string ("test-indexer"));
  }
  ::libs::helpers::files::create_folder (root_path_);
}


void
TestIndexerImpl::load_state ()
{
  const auto    file_name = details::get_name_state_file ();
  const auto    full_path = ::libs::helpers::files::make_path (root_path_, file_name);
  std::ifstream file (full_path, std::ios::binary);

  state_saved_ = false;

  if (!file.is_open ())
  {
    return;
  }

  try
  {
    boost::archive::xml_iarchive xmla (file, boost::archive::no_header);
    xmla&                        BOOST_SERIALIZATION_NVP (state_);
  }
  catch (std::exception& e)
  {
    U3_LOG_STORAGE_EXCEPT (e.what ());
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
  const auto    full_path = ::libs::helpers::files::make_path (root_path_, file_name);
  std::ofstream file (full_path, std::ios::binary | std::ios::trunc);

  if (!file.is_open ())
  {
    U3_XLOG_ERROR ("open file for save state path=" + full_path);
    return;
  }

  try
  {
    boost::archive::xml_oarchive xmla (file, boost::archive::no_header);

    xmla& BOOST_SERIALIZATION_NVP (state_);
  }
  catch (std::exception& e)
  {
    U3_LOG_STORAGE_EXCEPT (e.what ());
    return;
  }

  state_saved_ = true;
}


void
TestIndexerImpl::open_stream (::libs::istorage_events::events::UpdateStream::raw_ptr info)
{
  U3_ASSERT (info->stream_id_ == ::libs::istorage_events::consts::empty_stream_id);
  U3_ASSERT (info->obj_id_.is_valid ());

  info->stream_id_ = boost::uuids::random_generator () ();
  U3_ASSERT (info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
  auto& obj_state = state_->objects_[info->obj_id_];

  obj_state.streams_.push_back (StateStream (info->stream_id_));
  state_saved_ = false;
}


void
TestIndexerImpl::close_stream (::libs::istorage_events::events::UpdateStream::raw_ptr info)
{
  U3_ASSERT (info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
}
}   // namespace modules::uuu_storage::appl::impl::indexer::test
