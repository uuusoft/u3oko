#pragma once
/**
\file       ilinks-property.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_properties_libs
*/

namespace libs::properties::vers::links
{
///  Свойство для хранения общепроцессных свойств по связям между компонентами внутри одного процесса
class ILinksProperty : public ISharedProperty
{
  public:
  //  ext types
  using links_type = LinksApplication< ::libs::link::ILink::weak_ptr >;

  U3_ADD_POINTERS_TO_SELF (ILinksProperty)

  explicit ILinksProperty (const links_type& links);
  virtual ~ILinksProperty () = default;

  auto get_links_lockfree () const -> const links_type&;
  auto update_links_lockfree () -> links_type&;

  private:
  // ISharedProperty overrides
  virtual bool  self_test_int () const override;
  virtual void* cast2top_int () override;

  links_type links_;   //< Слабые связи модулей в данном процессе
};
}   // namespace libs::properties::vers::links
