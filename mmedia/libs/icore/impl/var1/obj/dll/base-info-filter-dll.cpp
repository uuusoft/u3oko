/**
\file       base-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../libs-icore-includes_int.hpp"
#include "../../libs-icore-impl-var1-includes.hpp"
#include "base-info-filter-dll.hpp"

namespace libs::icore::impl::var1::obj::dll
{
BaseInfoFilter::BaseInfoFilter ()
{
}


BaseInfoFilter::~BaseInfoFilter ()
{
}


bool
BaseInfoFilter::load (const ::pugi::xml_named_node_iterator& node)
{
  U3_ASSERT (!str2props_.empty ());
  const bool res_ = load_int (node);
  sync (false);
  return res_;
}


void
BaseInfoFilter::sync (bool force)
{
  sync_int (force);
}


bool
BaseInfoFilter::load_int (const ::pugi::xml_named_node_iterator& node)
{
  // DATA_LOG (VTOLOG (this));
  auto rit_props = node->children ("property");
  auto it_prop   = rit_props.begin ();

  while (it_prop != rit_props.end ())
  {
    auto attr     = it_prop->attribute ("name");
    auto val_attr = attr.as_string ();
    auto pfind    = str2props_.find (val_attr);

    if (str2props_.end () != pfind)
    {
      auto prop = pfind->second;
      U3_ASSERT (prop);
    }

    ++it_prop;
  }
  return true;
}


void
BaseInfoFilter::sync_int (bool force)
{
}
}   // namespace libs::icore::impl::var1::obj::dll
