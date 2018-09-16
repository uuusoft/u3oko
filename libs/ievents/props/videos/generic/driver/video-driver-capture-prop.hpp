//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       video-driver-capture-prop.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace driver {
//  syn
using videos::generics::convert::TypeSrc2Dst;
using ::libs::helpers::utils::cuuid;
/**
\brief    Параметры фокуса для устройства захвата.
*/
enum struct FocusType
{
  auto_generic     = 0,       //< Автофокус.
  auto_near        = 1,       //< ????.
  auto_macro       = 2,       //< ????.
  caf              = 3,       //< ????.
  caf_near         = 4,       //< ????.
  fixed_infinity   = 5,       //< ????.
  fixed_hyperfocal = 6,       //< ????.
  fixed_near       = 7,       //< ????.
  fixed_macro      = 8,       //< ????.
  fixed_cirrent    = 9,       //< ????.
  fixed_max        = 10,      //< ????.
  edof             = 11,      //< ????.
  caf_macro        = 12,      //< ????.
  caf_fast         = 13,      //< ????.
  caf_near_fast    = 14,      //< ????.
  caf_macro_fast   = 15       //< ????.
};
/**
\brief  
*/
inline FocusType
str2focus (const std::string& _str)
{
  const std::unordered_map<std::string, FocusType> _vals = {
    { "auto_generic", FocusType::auto_generic },
    { "auto_near", FocusType::auto_near },
    { "auto_macro", FocusType::auto_macro },
    { "caf", FocusType::caf },
    { "caf_near", FocusType::caf_near },
    { "fixed_infinity", FocusType::fixed_infinity },
    { "fixed_hyperfocal", FocusType::fixed_hyperfocal },
    { "fixed_near", FocusType::fixed_near },
    { "fixed_macro", FocusType::fixed_macro },
    { "fixed_cirrent", FocusType::fixed_cirrent },
    { "fixed_max", FocusType::fixed_max },
    { "edof", FocusType::edof },
    { "caf_macro", FocusType::caf_macro },
    { "caf_fast", FocusType::caf_fast },
    { "caf_near_fast", FocusType::caf_near_fast },
    { "caf_macro_fast", FocusType::caf_macro_fast }
  };

  auto _pval = _vals.find (_str);
  if (_vals.end () == _pval)
    {
      XULOG_WARNING ("unknown FocusType str, " << _str);
      return FocusType::auto_generic;
    }
  return _pval->second;
}
/**
  \brief  Свойства для устройства захвата видео.
  */
class VideoDriverCaptureProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoDriverCaptureProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoDriverCaptureProp);
  UUU_DISABLE_ACOPY_TYPE (VideoDriverCaptureProp);

  explicit VideoDriverCaptureProp (const Acessor& = Acessor (0));

  virtual ~VideoDriverCaptureProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/driver/video-driver-capture-prop";
    return _ret;
  }

  TypeSrc2Dst  type_resize_;              //< Типа масштабирования кадра.
  TypeCatchRgn type_capture_;             //< Тип захвата.
  unsigned int capture_fps_;              //< Количество кадров в секунду, снимаемых с устройства.
  int          width_;                    //< Ширина кадра.
  int          height_;                   //< Высота кадра.
  cuuid        px_format_;                //< Формат пикселей.
  unsigned int count_preload_frame_;      //< Количество буферов в реализации захвата данных с устройства.
  unsigned int mem_frames_cycle_;         //< ???
  int          delay_load_image_;         //< ???
  bool         mirror_x_;                 //<  Отразить по горизонтали изображение.
  bool         mirror_y_;                 //<  Отразить по вертикали изображение.
  int          rotation_;                 //< Вращение изображения, в градусах.
  FocusType    focus_;                    //< Фокус камеры.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::driver

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::driver::VideoDriverCaptureProp);
