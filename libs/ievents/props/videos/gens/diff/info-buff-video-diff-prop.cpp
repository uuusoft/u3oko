//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-buff-video-diff-prop.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "info-buff-video-diff-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace gens { namespace diff {

InfoBuffVideoDiffProp::InfoBuffVideoDiffProp () :
  bindx_diff_ (utils::dbuffs::video::consts::offs::invalid)
{}


InfoBuffVideoDiffProp::~InfoBuffVideoDiffProp ()
{}


template <class Archive>
void
InfoBuffVideoDiffProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (bindx_diff_);
  ar& BOOST_SERIALIZATION_NVP (op_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::gens::diff::InfoBuffVideoDiffProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::gens::diff::InfoBuffVideoDiffProp);
