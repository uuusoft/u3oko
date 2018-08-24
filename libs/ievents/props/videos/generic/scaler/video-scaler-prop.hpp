#pragma once
/**
\file       video-scaler-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace scaler {
/**
  \brief  empty brief
  */
class VideoScalerProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoScalerProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoScalerProp);
  UUU_DISABLE_ACOPY_TYPE (VideoScalerProp);

  explicit VideoScalerProp (const Acessor& = Acessor (0));

  virtual ~VideoScalerProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/scaler/video-scaler-prop";
    return _ret;
  }

  const std::vector<BuffEventInfoVideoScaler>& get_buffs () const;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  std::vector<BuffEventInfoVideoScaler> buffs_;      //<Пары источник-назачение для масштабирования.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::scaler

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::scaler::VideoScalerProp);
