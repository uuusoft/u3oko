//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       CVideoMatrixProp.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "CVideoMatrixProp.hpp"
//old shit
namespace libs {
namespace ievents {
namespace props {
namespace videos {
namespace generics {
namespace matrix {
#if 0
  CVideoMatrixProp::CVideoMatrixProp () :
    enable_ (false),
    koeff_ (255),
    bound_ (80),
    change_color_ (true),
    replicate_images_ (true)
  {
    property_name_ = "libs/ievents/props/videos/generic/matrix/CVideoMatrixProp";

    type_id_ = index_type ({ 0xeb, 0xae, 0x6c, 0x56, 0x8f, 0x03, 0x4e, 0x6f, 0xab, 0x23, 0x55, 0x4e, 0x43, 0x9c, 0x18, 0x85 });
  }


  ::libs::events::IEvent::ptr CVideoMatrixProp::clone_int( const ::libs::events::DeepEventCloneType& _deep ) const
  {
    if( ::libs::events::DeepEventCloneType::empty == _deep )
    {
      return std::m1ake_shared<CVideoMatrixProp>();
    }

    return std::m1ake_shared<CVideoMatrixProp>(*this);
  }


  void CVideoMatrixProp::load_int( const base_functs::xml::itn& _prop ) 
  {
    super::load_int( _prop );

    base_functs::xml::ritn  _params = _prop->children ("param");
    base_functs::xml::itn _param  = _params.begin ();

    while ( _param != _params.end () )
    {

      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<bool>(        _param, "enable",     enable_ );
      ::libs::icore::xml::helpers::load<int>(         _param, "koeff",      koeff_ );
      ::libs::icore::xml::helpers::load<int>(         _param, "bound",      bound_ );
      ::libs::icore::xml::helpers::load<bool>(        _param, "change_color",   change_color_ );
      ::libs::icore::xml::helpers::load<bool>(        _param, "replicate_images", replicate_images_ );
      ::libs::icore::xml::helpers::load<std::string>( _param, "folder",     folder_ );

      ++_param;
    }

    self_correct ();
    return;
  }


  template<class Archive>
  void CVideoMatrixProp::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );
    ar & BOOST_SERIALIZATION_NVP( enable_ );
    ar & BOOST_SERIALIZATION_NVP( koeff_ );
    ar & BOOST_SERIALIZATION_NVP( bound_ );
    ar & BOOST_SERIALIZATION_NVP( change_color_ );
    ar & BOOST_SERIALIZATION_NVP( replicate_images_ );
    ar & BOOST_SERIALIZATION_NVP( folder_ );
    return;
  }
#endif
}
}}}}}      // namespace libs::ievents::props::videos::generics::matrix

//BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::props::videos::generics::matrix::CVideoMatrixProp );
//SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::props::videos::generics::matrix::CVideoMatrixProp );
