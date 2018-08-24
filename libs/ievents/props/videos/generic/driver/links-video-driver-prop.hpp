//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       links-video-driver-prop.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace driver {
//  syn
using ::utils::mem_functs::impl::BlockMemAllocatorProxy;
using utils::dbuffs::allocator::BuffAllocatorProxy;
/**
  \brief  empty brief
  */
class LinksVideoDriverProp : public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (LinksVideoDriverProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (LinksVideoDriverProp);
  UUU_DISABLE_ACOPY_TYPE (LinksVideoDriverProp);

  explicit LinksVideoDriverProp (const Acessor& = Acessor (0));

  virtual ~LinksVideoDriverProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/driver/links-video-driver-prop";
    return _ret;
  }

  BuffAllocatorProxy::raw_ptr     pdriver2buff_;      //< ???
  BlockMemAllocatorProxy::raw_ptr pdriver2mem_;       //< ???


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::driver

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::driver::LinksVideoDriverProp);
