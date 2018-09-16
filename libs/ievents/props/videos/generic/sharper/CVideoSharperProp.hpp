#pragma once
/**
\file   CVideoSharperProp.hpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date   01.01.2017
\copyright  www.uuusoft.com
\project  uuu_ievents
\brief    
*/
//old shit
namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace sharper {

#if 0
  /**
  \brief  empty brief
  */
  struct EventBuffsInfo : public ::libs::events::buff::EventBuffsInfo
  {
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  public:

    EventBuffsInfo () : koeff_ (0.0f )
    {}


    void check () const
    {
      super::check ();

      return;
    }


    float   koeff_;


  protected:

    virtual ::libs::events::IEvent::ptr clone_int( const ::libs::events::DeepEventCloneType& _deep ) const override;
    virtual void copy_int( const IEvent::ptr& _src ) override;
    virtual void load_int ( const base_functs::xml::itn& _node ) override
    {
      check ();
      return;
    }

  private:

    UUU_THIS_TYPE_HAS_SUPER_CLASS( ::libs::events::buff::EventBuffsInfo );

    friend class boost::serialization::access;

    template<class Archive>
    void serialize (Archive & ar, const unsigned int /* file_version */);
  };
  /**
  \brief  empty brief
  */
  class CVideoSharperProp : public ievents::Event
  {   
  public:
    UUU_THIS_TYPE_HAS_POINTERS_TO_SELF( CVideoSharperProp );
    
    CVideoSharperProp();
    
    virtual ~CVideoSharperProp()
    {}

    
    std::vector< EventBuffsInfo >    buffs_;


  protected:
    
    virtual void load_int( const base_functs::xml::itn& _node ) override;


  private:    
    UUU_THIS_TYPE_HAS_SUPER_CLASS( ievents::Event );

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */);
  };
#endif
}}}}}}      // namespace libs::ievents::props::videos::generics::sharper

//BOOST_CLASS_EXPORT_KEY( ::libs::ievents::props::videos::generics::sharper::EventBuffsInfo );
//BOOST_CLASS_EXPORT_KEY( ::libs::ievents::props::videos::generics::sharper::CVideoSharperProp );
