//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       buff-video-convolution-prop.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace convolution {
/**
  \brief  empty brief
  */
struct BuffVideoConvolutionProp : public ::libs::events::buff::BuffEventInfo
{
  public:
  BuffVideoConvolutionProp ();

  void check () const;

  std::string        name_;       //< ???
  short              size_;       //< ???
  std::vector<short> vals_;       //< ???
  int                koeff_;      //< ???
  bool               mod_;        //< ???


  protected:
  virtual void load_int (const base_functs::xml::itn& _node) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buff::BuffEventInfo);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}}      // namespace libs::ievents::props::videos::generics::convolution

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::convolution::BuffVideoConvolutionProp);
