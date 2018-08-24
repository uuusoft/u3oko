#pragma once
/**
\file       gradient-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace gradient {
/**
  \brief  empty brief
  */
enum struct TypeGradient
{
  skip           = 0,      //< пропустить преобразование.
  usual          = 1,      //< Преобразование по умолчанию, фактически изображение не изменяется, используется для проверки работы и полноты операций. Аналог TypeGradient::skip.
  set2min        = 2,      //< Сброс всех значений в 0.
  set2max        = 3,      //< Сброс всех значений в 255.
  load_from_file = 4,      //< Загрузить преобразование из xml файла.
  rnd            = 5,      //< Случайным образом отобразить значения.
  increment      = 6       //< Линейно с течением времени увеличивать значение на 1. Используется для подбора.
};
/**
  \brief  empty brief
  */
struct ChannelGradient
{
  ChannelGradient () :
    type_ (TypeGradient::skip),
    animation_ (false),
    blure_ (false)
  {
    std::fill (vals_.begin (), vals_.end (), static_cast<short> (0));
  }

  TypeGradient           type_;            //< Тип преобразования.
  bool                   animation_;       //< Флаг анимации. depreceted.
  bool                   blure_;           //< Флаг размытия. deprected.
  std::array<short, 256> vals_;            //< Собственно вычисленные новые значения. По умолчанию они совпадают с их индексами.
  std::string            future_ext_;      //< Дополнительное поле для расширения функционала с целью проверки его на внесения в постоянную часть.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (type_);
    ar& BOOST_SERIALIZATION_NVP (animation_);
    ar& BOOST_SERIALIZATION_NVP (blure_);
    ar& BOOST_SERIALIZATION_NVP (vals_);
    ar& BOOST_SERIALIZATION_NVP (future_ext_);
    return;
  }
};
/**
  \brief  empty brief
  */
class GradientProp : public ievents::Event
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
  using channels_type = std::list<std::pair<off_buff_type, ChannelGradient>>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (GradientProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (GradientProp);
  UUU_DISABLE_ACOPY_TYPE (GradientProp);

  explicit GradientProp (const Acessor& = Acessor (0));

  virtual ~GradientProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/gradient/gradient-prop";
    return _ret;
  }

  channels_type chls_;      //< Список каналов преобразования.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  void load_layer (const base_functs::xml::itn& _node, ChannelGradient* _prop);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::gradient

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::gradient::GradientProp);
