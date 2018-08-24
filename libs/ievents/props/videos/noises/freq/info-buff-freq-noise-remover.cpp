//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-buff-freq-noise-remover.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "info-buff-freq-noise-remover.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace freq {

InfoBuffFreqNoiseRemover::InfoBuffFreqNoiseRemover () :
  bindx_diff_ (utils::dbuffs::video::consts::offs::invalid),
  bound_x_plus_y_ (1),
  dwt_koeff2_ (1.0f)
{}


template <class Archive>
void
InfoBuffFreqNoiseRemover::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (bindx_diff_);
  ar& BOOST_SERIALIZATION_NVP (bound_x_plus_y_);
  ar& BOOST_SERIALIZATION_NVP (dwt_koeff2_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::noises::freq

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
