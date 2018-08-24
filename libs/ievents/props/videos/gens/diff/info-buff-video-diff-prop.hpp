//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       info-buff-video-diff-prop.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace gens { namespace diff {
/**
  \brief  empty brief
  */
struct InfoBuffVideoDiffProp
{
  InfoBuffVideoDiffProp ();

  virtual ~InfoBuffVideoDiffProp ();

  off_buff_type       bindx_diff_;      //<буфера источника и назначения для разности.
  ParamsVideoDiffProp op_;              //<Операция постобработки разности.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}}      // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::gens::diff::InfoBuffVideoDiffProp);
