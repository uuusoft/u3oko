#pragma once
/**
\file       iindexer-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       09.08.2018
*/

namespace modules::mstorage::appl::impl
{
class IIndexerImpl
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (IIndexerImpl)
  U3_ADD_DELETE_MOVE_COPY (IIndexerImpl)

  virtual ~IIndexerImpl () = default;

  void
  set_info (const syn::PathInfo::craw_ptr info)
  {
    // ::libs::utility::checks::throw_ifn (info);
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
  update_stream (syn::UpdateStream::raw_ptr info)
  {
    ::libs::utility::checks::throw_ifn (info);
    update_stream_int (info);
  }

  void
  get_objects (std::vector< syn::TypeObjectId >& objs)
  {
    get_objects_int (objs);
  }

  protected:
  IIndexerImpl () = default;

  private:
  // IIndexerImpl
  virtual void get_objects_int (std::vector< syn::TypeObjectId >&) = 0;
  virtual bool change_state_int (const ImplRuns&)                  = 0;
  virtual void set_info_int (const syn::PathInfo::craw_ptr)        = 0;
  virtual void update_stream_int (syn::UpdateStream::raw_ptr)      = 0;

  ImplRuns status_ { ImplRuns::stop };   //<
};
}   // namespace modules::mstorage::appl::impl
