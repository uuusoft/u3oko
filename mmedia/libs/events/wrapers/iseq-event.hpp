#pragma once
/**
\file       iseq-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/

namespace libs::events
{
/// Событие последовательности событий
/// спользуется как флаг индентификации последовательности
class ISeqEvent : public IWrapBaseEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using id_type = ::libs::helpers::utils::cuuid;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ISeqEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ISeqEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ISeqEvent)

  explicit ISeqEvent (const Acessor& = Acessor (0), IEvent::ptr = IEvent::ptr (), const id_type& id = id_type ());
  virtual ~ISeqEvent () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/events/iseq-event";
    return ret;
  }

  const id_type& get_seq_id () const;
  void           set_seq_id (const id_type&);
  bool           empty () const;

  protected:
  virtual IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void        copy_int (const IEvent::craw_ptr src) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (IWrapBaseEvent)

  id_type id_;   //< Уникальный идентификатор последовательности событий

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::ISeqEvent);
