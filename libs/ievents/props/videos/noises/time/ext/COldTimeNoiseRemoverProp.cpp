//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       COldTimeNoiseRemoverProp.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../../includes_int.hpp"
#include "COldTimeNoiseRemoverProp.hpp"
//old shit
namespace libs {
namespace ievents {
namespace props {
namespace videos {
namespace noises {
namespace time {
namespace ext {
#if 0
  COldTimeNoiseRemoverProp::COldTimeNoiseRemoverProp () :
    make_cond_bound1_ (5 ),
    make_cond_bound2_ (200),
    make_cond_bound3_ (100),
    bound3_1_ (20),
    bound3_2_ (50),
    koeff3_1_ (100),
    koeff3_2_ (-40),
    koeff3_3_ (-40),
    bound_cond_koeff1_ (1),
    remove_cond_koeff1_ (20)
  {
    property_name_ = gen_get_mid();
    
  }


  COldTimeNoiseRemoverProp::~COldTimeNoiseRemoverProp ()
  {}


  ::libs::events::IEvent::ptr COldTimeNoiseRemoverProp::clone_int( const ::libs::events::DeepEventCloneType& _deep ) const
  {
    if( ::libs::events::DeepEventCloneType::empty == _deep )
    {
      return std::m1ake_shared<COldTimeNoiseRemoverProp>();
    }

    return std::m1ake_shared<COldTimeNoiseRemoverProp>(*this);
  }


  void COldTimeNoiseRemoverProp::load_int( const base_functs::xml::itn& _prop ) 
  {
    super::load_int( _prop );

    base_functs::xml::ritn  _params = _prop->children ("param");
    base_functs::xml::itn _param  = _params.begin ();

    while ( _param != _params.end () )
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param = _param->attribute ("val");
      
      ::libs::icore::xml::helpers::load<int>( _param, "make_cond_bound1",     make_cond_bound1_ );
      ::libs::icore::xml::helpers::load<int>( _param, "make_cond_bound2",     make_cond_bound2_ );
      ::libs::icore::xml::helpers::load<int>( _param, "make_cond_bound3",     make_cond_bound3_ );
      ::libs::icore::xml::helpers::load<int>( _param, "bound3_1",         bound3_1_ );
      ::libs::icore::xml::helpers::load<int>( _param, "bound3_2",         bound3_2_ );
      ::libs::icore::xml::helpers::load<int>( _param, "koeff3_1",         koeff3_1_ );
      ::libs::icore::xml::helpers::load<int>( _param, "koeff3_2",         koeff3_2_ );
      ::libs::icore::xml::helpers::load<int>( _param, "koeff3_3",         koeff3_3_ );
      ::libs::icore::xml::helpers::load<int>( _param, "bound_cond_koeff1",    bound_cond_koeff1_ );
      ::libs::icore::xml::helpers::load<int>( _param, "remove_cond_koeff1",   remove_cond_koeff1_ );

      ++_param;
    }

    make_cond_bound1_ = ::libs::helpers::utils::ret_check_bound( make_cond_bound1_, 0, make_cond_bound2_ - 1 );
    self_correct ();
    return;
  }


  template<class Archive>
  void COldTimeNoiseRemoverProp::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );

    ar & BOOST_SERIALIZATION_NVP( make_cond_bound1_ );
    ar & BOOST_SERIALIZATION_NVP( make_cond_bound2_ );
    ar & BOOST_SERIALIZATION_NVP( make_cond_bound3_ );
    ar & BOOST_SERIALIZATION_NVP( bound3_1_ );
    ar & BOOST_SERIALIZATION_NVP( bound3_2_ );
    ar & BOOST_SERIALIZATION_NVP( koeff3_1_ );
    ar & BOOST_SERIALIZATION_NVP( koeff3_2_ );
    ar & BOOST_SERIALIZATION_NVP( koeff3_3_ );
    ar & BOOST_SERIALIZATION_NVP( bound_cond_koeff1_ );
    ar & BOOST_SERIALIZATION_NVP( remove_cond_koeff1_ );

    return;
  }
#endif
}
}}}}}}      // namespace libs::ievents::props::videos::noises::time::ext

//BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::props::videos::noises::time::ext::COldTimeNoiseRemoverProp );
//SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::props::videos::noises::time::ext::COldTimeNoiseRemoverProp );
