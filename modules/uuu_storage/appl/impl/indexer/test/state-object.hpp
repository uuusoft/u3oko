#pragma once
/**
\file       state-object.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       15.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {
/**
\brief  Хранимое состояние для одного объекта записи (камера, микрофон и т.п.).
*/
class StateObject
{
  public:
  // ext types
  using streams_type = std::list<StateStream>;
  using TypeObjectId = ::libs::istorage_events::TypeObjectId;

  StateObject ()
  {}

  virtual ~StateObject ()
  {}

  bool
  operator== (const StateObject& _lv) const
  {
    return id_.val_ == _lv.id_.val_;
  }

  TypeObjectId id_;           //< Идентификатор объекта.
  streams_type streams_;      //< Список сеансов к данного объекту.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (id_);
    ar& BOOST_SERIALIZATION_NVP (streams_);
    return;
  }
};

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test

namespace std {

template <>
struct hash<::modules::uuu_storage::appl::impl::indexer::test::StateObject>
{
  size_t
  operator() (const ::modules::uuu_storage::appl::impl::indexer::test::StateObject& _val) const noexcept
  {
    return hash<typename ::modules::uuu_storage::appl::impl::indexer::test::StateObject::TypeObjectId> () (_val.id_);
  }
};

}      // namespace std
