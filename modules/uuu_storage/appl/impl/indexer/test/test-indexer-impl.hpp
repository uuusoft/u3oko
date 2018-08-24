#pragma once
/**
\file       test-indexer-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       25.07.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {
// syn
using ::libs::iproperties::appl_paths::TypePath;
using ::libs::iproperties::appl_paths::IAppPaths;
/**
  \brief  Тестовая реализация подсистемы хранения данных.
  */
class TestIndexerImpl final : public IIndexerImpl
{
  public:
  TestIndexerImpl ();

  virtual ~TestIndexerImpl ();


  private:
  //  IIndexerImpl overrides
  virtual void get_objects_int (std::vector<TypeObjectId>& _objs) override;
  virtual void set_info_int (const PathInfo::craw_ptr _info) override;
  virtual bool change_state_int (const StateImplsType& _state) override;
  virtual void update_stream_int (UpdateStream::raw_ptr) override;

  void update_path ();

  void load_state ();

  void save_state ();

  void open_stream (UpdateStream::raw_ptr);

  void close_stream (UpdateStream::raw_ptr);

  StateTestIndexer::ptr state_;            //< Хранимое состояние индексера.
  bool                  state_saved_;      //< Флаг фиксации хранимого состояния на жестком диске.
  PathInfo              info_;             //< Внешняя информация с параметрами.
  std::string           root_path_;        //< Сформированный путь к данным индексера.
};

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test
