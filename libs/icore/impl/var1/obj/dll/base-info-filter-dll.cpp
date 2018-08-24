//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-info-filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "../../includes.hpp"
#include "base-info-filter-dll.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj { namespace dll {

BaseInfoFilter::BaseInfoFilter ()
{}


BaseInfoFilter::~BaseInfoFilter ()
{}


bool
BaseInfoFilter::load (const base_functs::xml::itn& _node)
{
  UASSERT (!str2props_.empty ());
  const bool res_ = load_int (_node);
  sync (false);
  return res_;
}


void
BaseInfoFilter::sync (bool _force)
{
  sync_int (_force);
  return;
}


bool
BaseInfoFilter::load_int (const base_functs::xml::itn& _node)
{
  XULOG_TRACE ("BaseInfoFilter::load_int: beg, 0x" << this);
  base_functs::xml::ritn _rit_props = _node->children ("property");
  base_functs::xml::itn  _it_prop   = _rit_props.begin ();

  while (_it_prop != _rit_props.end ())
    {
      auto _attr     = _it_prop->attribute ("name");
      auto _val_attr = _attr.as_string ();
      auto _pfind    = str2props_.find (_val_attr);
      XULOG_TRACE ("BaseInfoFilter::load_int, try find {" << _val_attr << "}");

      if (str2props_.end () != _pfind)
        {
          auto _prop = _pfind->second;
          UASSERT (_prop);
          XULOG_TRACE ("BaseInfoFilter::load_int, load {" << _val_attr << "}");
          _prop->load (_it_prop);
        }

      ++_it_prop;
    }
  XULOG_TRACE ("BaseInfoFilter::load_int: end");
  return true;
}


void
BaseInfoFilter::sync_int (bool _force)
{
  return;
}

}}}}}}      // namespace libs::icore::impl::var1::obj::dll
