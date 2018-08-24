#pragma once
/**
\file       video-histogram-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace histogram {
/**
  \brief  empty brief
  */
struct BuffEventInfo : public ::libs::events::buff::BuffEventInfo
{
  public:
  BuffEventInfo () :
    norm_ (false), dindx_ (-1)
  {}

  bool norm_;       //< ???
  int  dindx_;      //< ???

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (norm_);
    ar& BOOST_SERIALIZATION_NVP (dindx_);
    return;
  }
};
/**
  \brief  empty brief
  */
class VideoHistogramProp : public ievents::Event
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
  using type2buff_type = std::vector<std::pair<off_buff_type, BuffEventInfo>>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoHistogramProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoHistogramProp);
  UUU_DISABLE_ACOPY_TYPE (VideoHistogramProp);

  explicit VideoHistogramProp (const Acessor& = Acessor (0));

  virtual ~VideoHistogramProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/histogram/video-histogram-prop";
    return _ret;
  }

  type2buff_type buffs2norm_;      //< ???


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::histogram

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::histogram::VideoHistogramProp);
