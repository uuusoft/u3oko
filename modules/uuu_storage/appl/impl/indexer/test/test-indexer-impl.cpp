/**
\file       test-indexer-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       25.07.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "test-indexer-impl.hpp"

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {

TestIndexerImpl::TestIndexerImpl () :
  state_ (std::make_shared<StateTestIndexer> ()),
  state_saved_ (true)
{}


TestIndexerImpl::~TestIndexerImpl ()
{
  save_state ();
}


bool
TestIndexerImpl::change_state_int (const StateImplsType& _state)
{
  switch (_state)
    {
    case StateImplsType::run:
      load_state ();
      break;
    case StateImplsType::stop:
      save_state ();
      break;
    default:
      XULOG_WARNING ("unknown change state, " << UUU_ICAST_INT (_state));
      return false;
    }
  return true;
}


void
TestIndexerImpl::set_info_int (const PathInfo::craw_ptr _info)
{
  if (_info)
    {
      info_ = *_info;
    }
  update_path ();
  save_state ();      //  save probably previous state
  load_state ();
  state_saved_ = false;
  return;
}


void
TestIndexerImpl::update_stream_int (UpdateStream::raw_ptr _info)
{
  XULOG_TRACE ("TestIndexerImpl::update_stream_int, beg");

  switch (_info->action_)
    {
    case TypeUpdateStream::open:
      open_stream (_info);
      break;
    case TypeUpdateStream::close:
      close_stream (_info);
      break;
    case TypeUpdateStream::change:
      UASSERT (_info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
      break;
    case TypeUpdateStream::check_and_get_info:
      UASSERT (_info->stream_id_ != ::libs::istorage_events::consts::empty_stream_id);
      break;
    default:
      UASSERT_SIGNAL ("failed find action " << to_str (_info->action_));
      break;
    }

  state_saved_ = false;
  XULOG_TRACE ("TestIndexerImpl::update_stream_int, end");
  return;
}


void
TestIndexerImpl::get_objects_int (std::vector<TypeObjectId>& _objs)
{
  _objs.clear ();
  _objs.reserve (state_->objects_.size ());

  for (auto& _obj : state_->objects_)
    {
      _objs.push_back (_obj.second.id_);
    }
  return;
}

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test
