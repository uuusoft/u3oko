#pragma once
/**
\file   CVideoMatrixProp.hpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date   01.01.2017
\copyright  www.uuusoft.com
\project  uuu_ievents
\brief    
*/
//old shit
namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace matrix {
#if 0
  /**
  \brief  empty brief
  */
  class CVideoMatrixProp : public ievents::Event
  {   
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  public:    
    UUU_THIS_TYPE_HAS_POINTERS_TO_SELF( CVideoMatrixProp );
    UUU_DISABLE_ACOPY_TYPE();
    
    CVideoMatrixProp();
    
    virtual ~CVideoMatrixProp()
    {}

    
    bool      enable_;
    int       koeff_;
    int       bound_;
    bool      change_color_;
    bool      replicate_images_;
    std::string   folder_;


  protected:
    
    virtual ::libs::events::IEvent::ptr clone_int( const ::libs::events::DeepEventCloneType& _deep ) const override;
    virtual void load_int( const base_functs::xml::itn& _node ) override;
    virtual void copy_int( const IEvent::ptr& _src ) override;


  private:
    UUU_THIS_TYPE_HAS_SUPER_CLASS( ievents::Event );

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */);
  };
#endif
}}}}}}      // namespace libs::ievents::props::videos::generics::matrix

//BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::matrix::CVideoMatrixProp);
