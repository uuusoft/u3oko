#pragma once
/**
\file       mem-block-event.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace events {
//  syn
typedef ::libs::link::mem::IBlockMem IBlockMem;
//  forward
class CBuffHelper_ResetVideo;
/**
  \brief  empty brief
  */
class MemBlockEvent : public BaseGUIEvent
{
  friend class CBuffHelper_ResetVideo;
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (MemBlockEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MemBlockEvent);
  UUU_DISABLE_ACOPY_TYPE (MemBlockEvent);

  explicit MemBlockEvent (const Acessor& = Acessor (0), const IBlockMem& _hmem = IBlockMem (), int _id = 0);

  virtual ~MemBlockEvent ();

  virtual TypeEvents get_type () const override;

  IBlockMem get_hmem ();

  void set_hmem (const IBlockMem&);

  bool reset_video (void* _pmem) const;

  int get_id () const;

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/igui_events/events/props/mem-block-event";
    return _ret;
  }


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseGUIEvent);

  IBlockMem hmem_;      /// ???
  int       id_;        /// ???

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  //virtual void load_int( const base_functs::xml::itn& _prop ) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};
/**
  \brief  empty brief
  */
class CBuffHelper_ResetVideo : public ::libs::link::mem::IHandlerMem
{
  public:
  CBuffHelper_ResetVideo (MemBlockEvent* _obj) :
    obj_ (_obj)
  {}

  virtual ~CBuffHelper_ResetVideo ()
  {}

  virtual bool
  update (void* _pmem) const override
  {
    obj_->reset_video (_pmem);
    return true;
  }

  private:
  mutable MemBlockEvent* obj_;      /// ???
};

}}}      // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_KEY (::libs::igui_events::events::MemBlockEvent);
