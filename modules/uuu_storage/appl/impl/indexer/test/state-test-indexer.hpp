#pragma once
/**
\file       state-test-indexer.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       15.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {
/**
  \brief  Сохраняемое состояние тестовой реализации подсистемы индексации хранимых данных.
  */
class StateTestIndexer : public ::libs::istorage_events::events::BaseStorageEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (StateTestIndexer);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (StateTestIndexer);
  UUU_DISABLE_ACOPY_TYPE (StateTestIndexer);
  using objects_type = std::unordered_map<StateObject::TypeObjectId, StateObject>;

  explicit StateTestIndexer (const Acessor& = Acessor (0));

  virtual ~StateTestIndexer ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "modules/uuu_storage/appl/impl/indexer/test/state-test-indexer";
    return _ret;
  }

  objects_type objects_;      //< Список объектов (источников данных) текущего состояния индексера.


  protected:
  virtual void copy_int (const IEvent::craw_ptr _src) override;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
};

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test

BOOST_CLASS_EXPORT_KEY (::modules::uuu_storage::appl::impl::indexer::test::StateTestIndexer);
