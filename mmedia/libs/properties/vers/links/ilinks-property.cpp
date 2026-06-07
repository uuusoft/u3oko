/**
\file       ilinks-property.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       02.03.2022
\project    u3_properties_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
// REFACTOR include
#include "../../../events/includes.hpp"
#include "../../../link/libs-link-includes.hpp"

#include "../../ishared-property.hpp"
#include "links-application.hpp"
#include "ilinks-property.hpp"

namespace libs::properties::vers::links
{
ILinksProperty::ILinksProperty (const links_type& links)
{
  links_.copy_links (links);
}


const ILinksProperty::links_type&
ILinksProperty::get_links_lockfree () const
{
  return links_;
}


ILinksProperty::links_type&
ILinksProperty::update_links_lockfree ()
{
  return links_;
}


bool
ILinksProperty::self_test_int () const
{
  U3_ASSERT (links_.self_test ());
  return links_.self_test () ? true : false;
}


void*
ILinksProperty::cast2top_int ()
{
  return this;
}
}   // namespace libs::properties::vers::links
