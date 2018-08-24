#pragma once
/**
\file       ilinks-property.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_properties
\brief      empty brief
*/

namespace libs { namespace properties { namespace vers { namespace links {
/**
  \brief  Свойство для хранения общепроцессных свойств по связям между компонентами внутри одного процесса.
  */
class ILinksProperty : public ISharedProperty
{
  public:
  //  ext types
  using links_type = LinksApplication<::libs::link::ILink::weak_ptr>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ILinksProperty);

  explicit ILinksProperty (links_type _links) :
    links_ (_links)
  {}

  virtual ~ILinksProperty ()
  {}

  const links_type&
  get_links_lockfree () const
  {
    return links_;
  }

  links_type&
  update_links_lockfree ()
  {
    return links_;
  }


  private:
  virtual bool
  self_test_int () const override
  {
    UASSERT (links_.self_test ());
    return links_.self_test () ? true : false;
  }

  virtual void*
  cast2top_int () override
  {
    return this;
  }

  links_type links_;      //< Слабые связи модулей в данном процессе.
};

}}}}      // namespace libs::properties::vers::links
