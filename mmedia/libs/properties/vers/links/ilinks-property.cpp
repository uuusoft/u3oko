/**
\file       ilinks-property.cpp
\author     Erashov Anton erashov2026@proton.me
\date       02.03.2022
\project    u3_properties_libs
*/
// REFACTOR include
#include "../../libs-properties-includes_int.hpp"
#include "../../../events/includes.hpp"
#include "../../../link/_make/libs-link-includes.hpp"

#include "../../ishared-property.hpp"
#include "links-application.hpp"
#include "ilinks-property.hpp"

namespace libs::properties::vers::links
{
ILinksProperty::ILinksProperty (const links_type& links)
{
  links_.copy_links (links, true);
}


auto
ILinksProperty::get_links_lockfree () const -> const ILinksProperty::links_type&
{
  return links_;
}


auto
ILinksProperty::update_links_lockfree () -> ILinksProperty::links_type&
{
  return links_;
}


auto
ILinksProperty::self_test_int () const -> bool
{
  U3_ASSERT (links_.self_test ());
  return links_.self_test () ? true : false;
}


auto
ILinksProperty::cast2top_int () -> void*
{
  return this;
}
}   // namespace libs::properties::vers::links
