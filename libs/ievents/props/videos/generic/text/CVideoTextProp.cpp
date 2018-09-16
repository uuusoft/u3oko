//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file   CVideoTextProp.cpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date   01.01.2017
\copyright  www.uuusoft.com
\project  uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "CVideoTextProp.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace text {
#if 0
  CVideoTextProp::CVideoTextProp () : enable_ (false)
  {
    property_name_ = "libs/ievents/props/videos/generic/text/CVideoTextProp";
    type_id_ = index_type ({ 0x15, 0x11, 0x0d, 0xb5, 0xec, 0x00, 0x46, 0xf5, 0x9d, 0x4c, 0x33, 0x4c, 0x62, 0x3f, 0x5a, 0x4c });
  }


  ::libs::events::IEvent::ptr CVideoTextProp::clone_int( const ::libs::events::DeepEventCloneType& _deep ) const
  {
    if( ::libs::events::DeepEventCloneType::empty == _deep )
    {
      return std::m1ake_shared<CVideoTextProp>();
    }

    return std::m1ake_shared<CVideoTextProp>(*this);
  }


  void CVideoTextProp::load_int( const base_functs::xml::itn& _prop ) 
  {
    super::load_int( _prop );

    base_functs::xml::ritn  _params = _prop->children ("param");
    base_functs::xml::itn _param  = _params.begin ();

    while ( _param != _params.end () )
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<bool>( _param, "enable", enable_ );

      ++_param;
    }

    self_correct ();
    return;
  }


  template<class Archive>
  void CVideoTextProp::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );
    ar & BOOST_SERIALIZATION_NVP( enable_ );

    return;
  }
#endif
}}}}}}      // namespace libs::ievents::props::videos::generics::text

//BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::props::videos::generics::text::CVideoTextProp );
//SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::props::videos::generics::text::CVideoTextProp );
