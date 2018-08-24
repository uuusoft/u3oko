#pragma once
/**
\file       video-correct-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace correct {
//  syn
using ::libs::events::buff::BuffEventInfo;
/**
  \brief  empty brief
  */
class VideoCorrectProp : public ievents::Event
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
  //  ext consts
  static const int min = -1;
  static const int max = 1;
  static const int def = 0;
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoCorrectProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoCorrectProp);
  UUU_DISABLE_ACOPY_TYPE (VideoCorrectProp);

  explicit VideoCorrectProp (const Acessor& = Acessor (0));

  virtual ~VideoCorrectProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/correct/video-correct-prop";
    return _ret;
  }

  float       saturation_;         //< Значение насыщенности. [-1.0, +1.0].
  float       bright_;             //< Значение освещенности. [-1.0, +1.0].
  float       contrast_;           //< Значение контраста. [-1.0, +1.0].
  float       sharp_;              //< Значение резкости. [-1.0, +1.0].
  float       hue_;                //< Значение цветового тона. [-1.0, +1.0].
  float       gamma_;              //< Значение гаммы коррекции.  [-1.0, +1.0].
  float       white_balance_;      //< Значение баланса белого цвета.  [-1.0, +1.0].
  bool        adaptive_;           //< Флаг, включает адаптивную коррекцию освещенности на изображении.
  bool        short2byte_;         //< Флаг, принудительно контролировать диапазон значений пикселей в выходном изображении.
  std::string hint_impl_;            //< Опциональный идентифкатор реализации. Например "auto", "hard", "soft", etc.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
  virtual void                        self_correct_int () override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::correct

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::correct::VideoCorrectProp);
