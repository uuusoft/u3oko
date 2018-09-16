//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file   CVideoSharperProp.cpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date   01.01.2017
\copyright  www.uuusoft.com
\project  uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "CVideoSharperProp.hpp"

namespace libs {
namespace ievents {
namespace props {
namespace videos {
namespace generics {
namespace sharper {
#if 0
  template<class Archive>
  void EventBuffsInfo::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );
    ar & BOOST_SERIALIZATION_NVP( koeff_ );
    return;
  }


  CVideoSharperProp::CVideoSharperProp ()
  {
    property_name_ = "libs/ievents/props/videos/generic/sharper/CVideoSharperProp";
    type_id_ = index_type ({ 0xb8, 0x7d, 0xd6, 0x4a, 0x8d, 0x3d, 0x41, 0x5e, 0xa1, 0x80, 0xa6, 0x51, 0x8d, 0xfd, 0x4e, 0x62 });
  }


  ::libs::events::IEvent::ptr CVideoSharperProp::clone_int( const ::libs::events::DeepEventCloneType& _deep ) const
  {
    if( ::libs::events::DeepEventCloneType::empty == _deep )
    {
      return std::m1ake_shared<CVideoSharperProp>();
    }

    return std::m1ake_shared<CVideoSharperProp>(*this);
  }


  void CVideoSharperProp::load_int( const base_functs::xml::itn& _prop )
  {
    super::load_int( _prop );

    base_functs::xml::ritn  _params = _prop->children ( ::libs::events::buff::consts::node_name.c_str() );
    base_functs::xml::itn _param  = _params.begin ();

    buffs_.clear();
    buffs_.reserve(16);

    while ( _param != _params.end () )
    {
      pugi::xml_attribute _sindx = _param->attribute ("sindx");
      pugi::xml_attribute _dindx = _param->attribute ("dindx");
      pugi::xml_attribute _koeff = _param->attribute ("koeff");

      if( _sindx && _dindx && _koeff )
      {
        EventBuffsInfo _add;

        //_add.indx_sbuff_  = ::libs::helpers::utils::ret_check_bound<int>( _sindx.as_int(), 0, utils::dbuffs::video::consts::offs::count_buffs-1 );
        _add.indx_sbuff_  = utils::dbuffs::video::consts::offs::str2eoffbuff( _sindx.as_string() );
        //_add.indx_dbuff_  = ::libs::helpers::utils::ret_check_bound<int>( _dindx.as_int(), 0, utils::dbuffs::video::consts::offs::count_buffs-1 );
        _add.indx_dbuff_  = utils::dbuffs::video::consts::offs::str2eoffbuff( _dindx.as_string() );
        _add.koeff_     = _koeff.as_float();

        _add.check();

        buffs_.push_back( _add);
      }

      ++_param;
    }

    self_correct ();
    return;
  }


  template<class Archive>
  void CVideoSharperProp::serialize (Archive & ar, const unsigned int /* file_version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( super );
    ar & BOOST_SERIALIZATION_NVP( buffs_ );

    return;
  }
#endif
}
}}}}}      // namespace libs::ievents::props::videos::generics::sharper

//BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::props::videos::generics::sharper::EventBuffsInfo );
//SERIALIZE_TYPE_TO_ARCHIVES( ::libs::ievents::props::videos::generics::sharper::CVideoSharperProp );
