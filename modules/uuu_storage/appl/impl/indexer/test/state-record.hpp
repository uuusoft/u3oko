#pragma once
/**
\file       state-record.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       15.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {
/**
  \brief  Хранимое состояние для одной записи (блока бинарных данных, сохраненных в хранилище).
  */
class StateRecord
{
  public:
  // ext types
  using id_chunk_type    = IStorageImpl::id_chunk_type;
  using time_record_type = ::libs::istorage_events::TypeTimeStream;

  StateRecord ()
  {}

  virtual ~StateRecord ()
  {}

  id_chunk_type    id_;         //< Индентификатор записи в хранилище.
  time_record_type start_;      //< ???
  time_record_type stop_;       //< ???


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (id_);
    ar& BOOST_SERIALIZATION_NVP (start_);
    ar& BOOST_SERIALIZATION_NVP (stop_);
    return;
  }
};

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test
