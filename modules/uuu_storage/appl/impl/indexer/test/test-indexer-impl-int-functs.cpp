/**
\file       test-indexer-impl-int-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "test-indexer-impl.hpp"

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test { namespace details {

inline std::string
get_name_state_file ()
{
  return "state_impl.bin";
}

}}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test::details

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {

void
TestIndexerImpl::update_path ()
{
  XULOG_TRACE ("TestIndexerImpl::update_path, beg, root_path_=" << root_path_);
  if (!root_path_.empty ())
    {
      XULOG_TRACE ("TestIndexerImpl::update_path, ready, skip");
      return;
    }

  auto _iappl = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_appl_paths_lockfree ();
  root_path_  = info_.path2data_;

  if (root_path_.empty ())
    {
      // »наче генерируем значение по умолчанию, использу€ идентификатор и путь по умолчанию.
      auto _path = _iappl->get_path (::libs::iproperties::appl_paths::TypePath::default_storage);
      root_path_ = ::libs::helpers::files::make_path (_path, std::string ("test-indexer"));
    }
  ::libs::helpers::files::create_folder (root_path_);
  XULOG_TRACE ("TestIndexerImpl::update_path, end, root_path_=" << root_path_);
  return;
}


void
TestIndexerImpl::load_state ()
{
  const auto    _file_name = details::get_name_state_file ();
  const auto    _full_path = ::libs::helpers::files::make_path (root_path_, _file_name);
  std::ifstream _file (_full_path, std::ios::binary);

  state_saved_ = false;

  if (!_file.is_open ())
    {
      return;
    }

  try
    {
      boost::archive::xml_iarchive _xmla (_file, boost::archive::no_header);
      _xmla&                       BOOST_SERIALIZATION_NVP (state_);
    }
  catch (std::exception& _e)
    {
      XULOG_FATAL ("failed load state, " << _e.what ());
    }
  return;
}


void
TestIndexerImpl::save_state ()
{
  if (state_saved_)
    {
      return;
    }

  const auto    _file_name = details::get_name_state_file ();
  const auto    _full_path = ::libs::helpers::files::make_path (root_path_, _file_name);
  std::ofstream _file (_full_path, std::ios::binary | std::ios::trunc);

  if (!_file.is_open ())
    {
      XULOG_ERROR ("failed open file for save state, " << _full_path);
      return;
    }

  try
    {
      boost::archive::xml_oarchive _xmla (_file, boost::archive::no_header);
      _xmla&                       BOOST_SERIALIZATION_NVP (state_);
    }
  catch (std::exception& _e)
    {
      XULOG_FATAL ("failed save state, " << _e.what ());
      return;
    }
  state_saved_ = true;
  return;
}


void
TestIndexerImpl::open_stream (UpdateStream::raw_ptr _info)
{
  UASSERT (_info->stream_id_ == ::libs::istorage_events::consts::empty_stream_id);
  UASSERT (_info->obj_id_.is_valid ());
  _info->stream_id_ = boost::uuids::random_generator () ();
  UASSERT (_info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
  auto& _obj_state = state_->objects_[_info->obj_id_];
  _obj_state.streams_.push_back (StateStream (_info->stream_id_));
  state_saved_ = false;
  return;
}


void
TestIndexerImpl::close_stream (UpdateStream::raw_ptr _info)
{
  UASSERT (_info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
  return;
}

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test
