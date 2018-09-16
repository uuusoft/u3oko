#pragma once
/**
\file       size-changed-event.hpp
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace events {
/**
\brief  empty brief
*/
class SizeChangedEvent : public BaseGUIEvent
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
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (SizeChangedEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (SizeChangedEvent);
  UUU_DISABLE_ACOPY_TYPE (SizeChangedEvent);

  explicit SizeChangedEvent (const Acessor& = Acessor (0), const ::libs::igui_events::utils::ISize::ptr& _size = ::libs::igui_events::utils::ISize::ptr ());

  virtual ~SizeChangedEvent ();

  virtual TypeEvents get_type () const override;

  ::libs::igui_events::utils::ISize::ptr get_size () const;

  void set_size (const ::libs::igui_events::utils::ISize::ptr&);

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/igui_events/events/props/size-changed-event";
    return _ret;
  }


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseGUIEvent);

  ::libs::igui_events::utils::ISize::ptr size_;      //< ???

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::SizeChangedEvent);
