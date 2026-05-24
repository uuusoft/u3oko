#pragma once
/**
\file       state-test-indexer.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       15.08.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::indexer::test
{
class StateTestIndexer : public ::libs::istorage_events::events::BaseStorageEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using objects_type = std::unordered_map< StateObject::TypeObjectId, StateObject >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (StateTestIndexer)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (StateTestIndexer)
  U3_HELPER_DISABLE_ACOPY_TYPE (StateTestIndexer)

  explicit StateTestIndexer (const Acessor& = Acessor (0));

  virtual ~StateTestIndexer ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "modules/uuu_storage/appl/impl/indexer/test/state-test-indexer";
    return ret;
  }

  objects_type objects_;   //<

  protected:
  virtual void copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::istorage_events::events::BaseStorageEvent)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
};
}   // namespace modules::uuu_storage::appl::impl::indexer::test

BOOST_CLASS_EXPORT_KEY (::modules::uuu_storage::appl::impl::indexer::test::StateTestIndexer);
