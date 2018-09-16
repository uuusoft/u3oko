//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       video-morphology-prop.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generic { namespace morph {
/**
\brief  Свойства фильтра для реализации морфологических операций над изображением.
*/
class VideoMorphologyProp : public ievents::Event
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
  using type2buff_type = std::list<std::pair<off_buff_type, MorphBuffInfo>>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoMorphologyProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoMorphologyProp);
  UUU_DISABLE_ACOPY_TYPE (VideoMorphologyProp);

  explicit VideoMorphologyProp (const Acessor& = Acessor (0));

  virtual ~VideoMorphologyProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/morph/video-morphology-prop";
    return _ret;
  }

  type2buff_type diffs_;      //< Список буферов над которыми требуется провести морфологические операции.


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generic::morph

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
