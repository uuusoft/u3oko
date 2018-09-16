//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       buff-event-info-video-scaler.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace scaler {
//  syn
using ::libs::events::props::details::Rect;
/**
  \brief  empty brief
  */
enum struct TypeScaler
{
  nearest    = 0,      //< Признак функции мастабирования "ближайщий сосед".
  bilinear   = 1,      //< Билинейное масштабирование.
  fixed_pow2 = 2       //< Признак функции масштабирования в четное число раз по каждой оси.
};
/**
  \brief  empty brief
  */
struct EventBuffsInfoVideoScaler : public ::libs::events::buff::EventBuffsInfo
{
  friend class boost::serialization::access;

  public:
  explicit EventBuffsInfoVideoScaler () :
    type_ (TypeScaler::nearest),
    koeff_pow2_ (0)
  {}

  void
  check () const
  {
    super::check ();
    return;
  }

  TypeScaler type_;            //< тип масштабирования.
  int        koeff_pow2_;      //< Степень двойки для режима TypeScaler::fixed_pow2
  Rect       src_rect_;        //< Прямоугльник источника.
  Rect       dst_rect_;        //< Прямогульник назначения.


  protected:
  virtual void load_int (const base_functs::xml::itn& _node) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buff::EventBuffsInfo);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}}      // namespace libs::ievents::props::videos::generics::scaler

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::scaler::EventBuffsInfoVideoScaler);
