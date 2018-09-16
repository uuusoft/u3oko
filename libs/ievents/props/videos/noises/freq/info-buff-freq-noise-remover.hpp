//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       info-buff-freq-noise-remover.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace freq {
/**
  \brief  empty brief
  */
struct InfoBuffFreqNoiseRemover : public ::libs::events::buff::EventBuffsInfo
{
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (InfoBuffFreqNoiseRemover);

  InfoBuffFreqNoiseRemover ();

  off_buff_type bindx_diff_;          //< ???
  short         bound_x_plus_y_;      //< ???
  float         dwt_koeff2_;          //< ???

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}}}      // namespace libs::ievents::props::videos::noises::freq

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
