#pragma once
/**
\file       video-driver-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace driver {
//  syn
using videos::generics::convert::TypeSrc2Dst;
using ::libs::helpers::utils::cuuid;
/**
  \brief  empty brief
  */
class VideoDriverProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoDriverProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoDriverProp);
  UUU_DISABLE_ACOPY_TYPE (VideoDriverProp);

  explicit VideoDriverProp (const Acessor& = Acessor (0));

  virtual ~VideoDriverProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/driver/video-driver-prop";
    return _ret;
  }

  std::string name_impl_dll_;      //< Имя dll реализации захвата данных из источника.
  cuuid       cat_dshow_;          //< Идентификатор каталога dshow. DEPRECATED.
  std::string text_;               //< ???
  std::string name_;               //< ???
  int         indx_device_;        //< Индекс устройства в каталоге dshow. DEPRECATED.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;

  void sync_data ();
};

}}}}}}      // namespace libs::ievents::props::videos::generics::driver

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::driver::VideoDriverProp);
