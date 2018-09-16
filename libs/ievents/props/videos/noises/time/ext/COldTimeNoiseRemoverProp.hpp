//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       COldTimeNoiseRemoverProp.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
//old shit
namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace time { namespace ext {

#if 0
  /**
  \brief  Свойства фильтрации во временной области. 
          Старый (пивной) вариант. Не используется, сохранен для истории.
  */
  class COldTimeNoiseRemoverProp : public ievents::Event
  {   
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  public:
    //  ext types
    UUU_THIS_TYPE_HAS_POINTERS_TO_SELF( COldTimeNoiseRemoverProp );

    COldTimeNoiseRemoverProp();
    
    virtual ~COldTimeNoiseRemoverProp();


    static const IEvent::hid_type& gen_get_mid()
    {
      static const std::string _ret = "libs/ievents/props/videos/noises/time/ext/COldTimeNoiseRemoverProp";
      return _ret;
    }


    static const IEvent::index_type& gen_get_type_id()
    {
      static const unsigned char _type_1id[16] = { 0x80, 0xb0, 0x90, 0x43, 0xca, 0xa3, 0x4c, 0xf4, 0x99, 0x31, 0x22, 0x9b, 0xdb, 0xc, 0x84, 0x8 };
      static const IEvent::index_type _ret = IEvent::index_type( _type_id );
      return _ret;
    }

    //<Граница для буфера условий при первом шаге. 50
    int   make_cond_bound1_;
    //<Граница для буфера условий при втором шаге. 100
    int   make_cond_bound2_;
    //<Граница бинаризации буфера условий, просто для удобства визуализации, фактически дубль bound_cond_koeff1_. 120
    int   make_cond_bound3_;
     
    int   bound3_1_;

    int   bound3_2_;
    
    int   koeff3_1_;
    
    int   koeff3_2_;
    
    int   koeff3_3_;
    
    int   bound_cond_koeff1_;
    //<Коэффициент, применяемый к пикселю предыдущего кадра, если связанной значение в буфере условий больше границы bound_cond_koeff1_. 0
    int   remove_cond_koeff1_;


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
}}}}}}}      // namespace libs::ievents::props::videos::noises::time::ext

//BOOST_CLASS_EXPORT_KEY( ::libs::ievents::props::videos::noises::time::ext::COldTimeNoiseRemoverProp );
