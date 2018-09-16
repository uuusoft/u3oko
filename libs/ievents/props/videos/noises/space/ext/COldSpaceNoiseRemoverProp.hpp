//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       COldSpaceNoiseRemoverProp.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
//old shit
namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace space { namespace ext {

#if 0
  /**
  \brief  Свойства фильтрации в пространственной области. Старый (пивной) вариант. Не используется, сохранен для истории.
  */
  class COldSpaceNoiseRemoverProp : public ievents::Event
  {   
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  public:
    //  ext types
    UUU_THIS_TYPE_HAS_POINTERS_TO_SELF( COldSpaceNoiseRemoverProp );

    COldSpaceNoiseRemoverProp();
    
    virtual ~COldSpaceNoiseRemoverProp();

    static const IEvent::hid_type& gen_get_mid()
    {
      static const std::string _ret = "libs/ievents/props/videos/noises/space/ext/COldSpaceNoiseRemoverProp";
      return _ret;
    }

    static const IEvent::index_type& gen_get_type_id()
    {
      static const IEvent::index_type _ret = IEvent::index_type({ 0x55, 0x1a, 0x2c, 0xf2, 0x41, 0x47, 0x4d, 0xf5, 0xb4, 0xdd, 0x8d, 0xcd, 0x77, 0x32, 0x82, 0xc8 });
      return _ret;
    }

    float     koeff2_;    //< ???
    bool      update_color_;      //< ???
    bool      use_counter_as_cond_;    //< ???
    unsigned int  count_cycles_;//< ???


  private:
    UUU_THIS_TYPE_HAS_SUPER_CLASS( ievents::Event );

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */);

    virtual ::libs::events::IEvent::ptr clone_int( const ::libs::events::DeepEventCloneType& _deep ) const override;
    virtual void load_int( const base_functs::xml::itn& _node ) override;
    virtual void copy_int( const IEvent::ptr& _src ) override;
  };
#endif
}}}}}}}      // namespace libs::ievents::props::videos::noises::space::ext

//BOOST_CLASS_EXPORT_KEY( ::libs::ievents::props::videos::noises::space::ext::COldSpaceNoiseRemoverProp );
