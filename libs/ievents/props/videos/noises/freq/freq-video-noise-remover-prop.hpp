#pragma once
/**
\file       freq-video-noise-remover-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace freq {
/**
  \brief  empty brief
  */
class FreqVideoNoiseRemoverProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (FreqVideoNoiseRemoverProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (FreqVideoNoiseRemoverProp);
  UUU_DISABLE_ACOPY_TYPE (FreqVideoNoiseRemoverProp);

  explicit FreqVideoNoiseRemoverProp (const Acessor& = Acessor (0));

  virtual ~FreqVideoNoiseRemoverProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/noises/freq/freq-video-noise-remover-prop";
    return _ret;
  }

  std::list<std::pair<off_buff_type, InfoBuffFreqNoiseRemover>> buffs_;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::noises::freq

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
