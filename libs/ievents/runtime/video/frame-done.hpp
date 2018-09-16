#pragma once
/**
\file       frame-done.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/

namespace libs { namespace ievents { namespace runtime { namespace video {
/**
\brief  Событие-уведомление об завершении обработки одного кадра с данными.
*/
class FrameDone : public RuntimeEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (FrameDone);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (FrameDone);
  UUU_DISABLE_ACOPY_TYPE (FrameDone);

  explicit FrameDone (const Acessor& = Acessor (0));

  virtual ~FrameDone ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/runtime/video/frame-done";
    return _ret;
  }


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;
};

}}}}      // namespace libs::ievents::runtime::video

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::video::FrameDone);
