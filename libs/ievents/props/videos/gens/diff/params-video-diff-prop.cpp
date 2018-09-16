//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       params-video-diff-prop.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "params-video-diff-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace gens { namespace diff {

ParamsVideoDiffProp::ParamsVideoDiffProp (bool _enable, short _bound_filling, short _val_filling) :
  enable_ (_enable),
  bound_filling_ (_bound_filling),
  val_filling_ (_val_filling)
{}


ParamsVideoDiffProp::~ParamsVideoDiffProp ()
{}


bool
ParamsVideoDiffProp::self_test () const
{
  if (val_filling_ <= 0)
    {
      return false;
    }
  return true;
}


template <class Archive>
void
ParamsVideoDiffProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (enable_);
  ar& BOOST_SERIALIZATION_NVP (bound_filling_);
  ar& BOOST_SERIALIZATION_NVP (val_filling_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::gens::diff::ParamsVideoDiffProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::gens::diff::ParamsVideoDiffProp);
