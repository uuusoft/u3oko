//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file   COldSpaceNoiseRemoverProp.cpp
\date   01.08.2017
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project  uuu_ievents
\brief    empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../../includes_int.hpp"
#include "COldSpaceNoiseRemoverProp.hpp"
//old shit
namespace libs {
namespace ievents {
namespace props {
namespace videos {
namespace noises {
namespace space {
namespace ext {
#if 0
  COldSpaceNoiseRemoverProp::COldSpaceNoiseRemoverProp () :
    koeff2_ (5.0f),
    update_color_ (true),
    use_counter_as_cond_ (true),
    count_cycles_ (2)
  {
    property_name_ = gen_get_mid();
    
  }


  COldSpaceNoiseRemoverProp::~COldSpaceNoiseRemoverProp ()
  {}


  ::libs::events::IEvent::ptr COldSpaceNoiseRemoverProp::clone_int( const ::libs::events::DeepEventCloneType& _deep ) const
  {
    if( ::libs::events::DeepEventCloneType::empty == _deep )
    {
      return std::m1ake_shared<COldSpaceNoiseRemoverProp>();
    }

    return std::m1ake_shared<COldSpaceNoiseRemoverProp>(*this);
  }


  void COldSpaceNoiseRemoverProp::load_int( const base_functs::xml::itn& _prop ) 
  {
    super::load_int( _prop );

    base_functs::xml::ritn  _params = _prop->children ("param");
    base_functs::xml::itn _param  = _params.begin ();

    while ( _param != _params.end () )
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<float>(         _param, "koeff2",               koeff2_ );
      ::libs::icore::xml::helpers::load<bool>(          _param, "update_color",         update_color_ );
      ::libs::icore::xml::helpers::load<bool>(          _param, "use_counter_as_cond",  use_counter_as_cond_ );
      ::libs::icore::xml::helpers::load<unsigned int>(  _param, "count_cycles",         count_cycles_ );

      ++_param;
    }

    self_correct ();
    return;
  }


  template<class Archive>
  void COldSpaceNoiseRemoverProp::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );

    ar & BOOST_SERIALIZATION_NVP( koeff2_ );
    ar & BOOST_SERIALIZATION_NVP( update_color_ );
    ar & BOOST_SERIALIZATION_NVP( use_counter_as_cond_ );
    ar & BOOST_SERIALIZATION_NVP( count_cycles_ );

    return;
  }
#endif
}
}}}}}}      // namespace libs::ievents::props::videos::noises::space::ext

//BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::props::videos::noises::space::ext::COldSpaceNoiseRemoverProp );
//SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::props::videos::noises::space::ext::COldSpaceNoiseRemoverProp );
