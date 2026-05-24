#pragma once
/**
\file       sqlite-indexer-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       25.07.2018
\project    u3_module_storage
*/
#ifndef U3_DBG_EXTERNAL_LIB_SKIP_SQLITE

namespace modules::uuu_storage::appl::impl::indexer::sqlite
{
class SqliteIndexerImpl final : public IIndexerImpl
{
  public:
  SqliteIndexerImpl ();
  virtual ~SqliteIndexerImpl ();

  private:
  //  IIndexerImpl overrides
  virtual void get_objects_int (std::vector< ::libs::istorage_events::TypeObjectId >& objs) override;
  virtual void set_info_int (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info) override;
  virtual bool change_state_int (const ImplRuns& state) override;
  virtual void update_stream_int (::libs::istorage_events::events::UpdateStream::raw_ptr) override;

  void update_path ();
  void load_state ();
  void save_state ();
  void open_stream (::libs::istorage_events::events::UpdateStream::raw_ptr);
  void close_stream (::libs::istorage_events::events::UpdateStream::raw_ptr);
  void prepare_base ();
  void shutdown_base ();

  StateSqliteIndexer::ptr                            state_;         //<
  bool                                               state_saved_;   //<
  ::libs::ievents::props::modules::storage::PathInfo info_;          //<
  std::string                                        root_path_;     //<
  sqlite3*                                           pbase_;         //<
};
}   // namespace modules::uuu_storage::appl::impl::indexer::sqlite

#endif
