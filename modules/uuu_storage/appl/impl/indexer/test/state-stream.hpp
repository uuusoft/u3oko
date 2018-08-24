#pragma once
/**
\file       state-stream.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       15.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {
/**
\brief  Хранимое состояние одного сеанса записи.
*/
class StateStream
{
  public:
  // ext types
  using records_type     = std::list<StateRecord>;
  using stream_id_type   = ::libs::istorage_events::stream_id_type;
  using time_stream_type = ::libs::istorage_events::TypeTimeStream;

  explicit StateStream (const stream_id_type& _id = ::libs::istorage_events::consts::empty_stream_id) :
    id_ (_id)
  {}

  virtual ~StateStream ()
  {}

  stream_id_type id_;           //< Уникальный идентификатор сеанса.
  records_type   records_;      //< Записи данного сеанса работы. Упорядоченны по времени.
  //time_stream_type start_;        //< ???
  //time_stream_type stop_;         //< ???

  const time_stream_type*
  get_start () const
  {
    if (records_.empty ())
      {
        return nullptr;
      }

    return &records_.front ().start_;
  }

  const time_stream_type*
  get_stop () const
  {
    if (records_.empty ())
      {
        return nullptr;
      }

    return &records_.back ().stop_;
  }


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (records_);
    ar& BOOST_SERIALIZATION_NVP (id_);
    //ar& BOOST_SERIALIZATION_NVP (start_);
    //ar& BOOST_SERIALIZATION_NVP (stop_);
    return;
  }
};

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test
