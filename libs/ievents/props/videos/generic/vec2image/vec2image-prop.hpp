#pragma once
/**
\file       vec2image-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace vec2image {
/**
  \brief  empty brief
  */
class Vec2ImageProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (Vec2ImageProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (Vec2ImageProp);
  UUU_DISABLE_ACOPY_TYPE (Vec2ImageProp);

  explicit Vec2ImageProp (const Acessor& = Acessor (0));

  virtual ~Vec2ImageProp ()
  {}

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/vec2image/vec2image-prop";
    return _ret;
  }

  std::vector<BuffEventInfoVec2Image1> buffs_;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::vec2image

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::vec2image::Vec2ImageProp);
