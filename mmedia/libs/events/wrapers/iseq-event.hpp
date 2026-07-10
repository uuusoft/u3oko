#pragma once
/**
\file       iseq-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/

namespace libs::events
{
/// Событие последовательности событий
/// спользуется как флаг индентификации последовательности
class ISeqEvent : public IWrapBaseEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using id_type = ::libs::utility::utils::cuuid;

  U3_ADD_POINTERS_TO_SELF (ISeqEvent)
  U3_ADD_MAKE_SHARED_THIS (ISeqEvent)
  U3_ADD_DELETE_MOVE_COPY (ISeqEvent)

  explicit ISeqEvent (const Acessor& = Acessor (0), IEvent::ptr = IEvent::ptr (), const id_type& id = id_type ());
  virtual ~ISeqEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events/iseq-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const id_type& get_seq_id () const;
  void           set_seq_id (const id_type&);
  bool           empty () const;

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps& deep) const -> IEvent::ptr override;
  virtual void copy_int (const IEvent::craw_ptr) override;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (IWrapBaseEvent)

  id_type id_;   //< Уникальный идентификатор последовательности событий

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::ISeqEvent);
