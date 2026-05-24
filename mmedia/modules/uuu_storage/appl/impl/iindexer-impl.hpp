#pragma once
/**
\file       iindexer-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       09.08.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl
{
class IIndexerImpl
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IIndexerImpl)

  virtual ~IIndexerImpl ()
  {
  }

  void
  set_info (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info)
  {
    // U3_ASSERT (info);
    set_info_int (info);
  }

  void
  change_state (const ImplRuns& state)
  {
    if (!change_state_int (state))
    {
      U3_XLOG_ERROR ("change state storage impl " + to_string (state));
      return;
    }
    status_ = state;
  }

  void
  update_stream (::libs::istorage_events::events::UpdateStream::raw_ptr info)
  {
    U3_ASSERT (info);
    update_stream_int (info);
  }

  void
  get_objects (std::vector< ::libs::istorage_events::TypeObjectId >& objs)
  {
    get_objects_int (objs);
  }

  protected:
  IIndexerImpl () :
    status_ (ImplRuns::stop)
  {
  }

  private:
  // IIndexerImpl
  virtual void get_objects_int (std::vector< ::libs::istorage_events::TypeObjectId >& objs)           = 0;
  virtual bool change_state_int (const ImplRuns& state)                                               = 0;
  virtual void set_info_int (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info) = 0;
  virtual void update_stream_int (::libs::istorage_events::events::UpdateStream::raw_ptr)             = 0;

  ImplRuns status_;   //<
};
}   // namespace modules::uuu_storage::appl::impl
