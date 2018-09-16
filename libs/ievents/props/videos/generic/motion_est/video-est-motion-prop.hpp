#pragma once
/**
\file       video-est-motion-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace motion_est { namespace consts {

const std::pair<char, char> inv_vec (static_cast<char> (127), static_cast<char> (127));

}}}}}}}      // namespace libs::ievents::props::videos::generics::motion_est::consts

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace motion_est {
/**
\brief  Свойства алгоритма оценки движения в кадре.
*/
class VideoEstMotionProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoEstMotionProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoEstMotionProp);
  UUU_DISABLE_ACOPY_TYPE (VideoEstMotionProp);

  explicit VideoEstMotionProp (const Acessor& = Acessor (0));

  virtual ~VideoEstMotionProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/motion_est/video-est-motion-prop";
    return _ret;
  }

  std::vector<EventBuffsInfo> buffs_;      //< ???


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::motion_est

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::motion_est::VideoEstMotionProp);
