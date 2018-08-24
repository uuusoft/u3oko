//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       buff-event-info-vec2image1.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace vec2image {
/**
  \brief  empty brief
  */
struct BuffEventInfoVec2Image1 : public ::libs::events::buff::BuffEventInfo
{
  friend class boost::serialization::access;

  public:
  explicit BuffEventInfoVec2Image1 () :
    size_block_ (16),
    mul_koeff_vec_ (1)
  {}


  void check () const;

  short size_block_;         //< Размер блока в пикселях, в который конвертируется вектор.
  short mul_koeff_vec_;      //< Опциональный коэффициент для масштабирования векторов.


  protected:
  virtual void load_int (const base_functs::xml::itn& _node) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buff::BuffEventInfo);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}}      // namespace libs::ievents::props::videos::generics::vec2image

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::vec2image::BuffEventInfoVec2Image1);
