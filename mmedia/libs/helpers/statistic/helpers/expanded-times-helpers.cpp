/**
\file       expanded-times-helpers.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/ilink/consts/libs-ilink-const-vals.hpp"
#include "mmedia/libs/events/includes.hpp"
#include "mmedia/libs/link/libs-link-includes.hpp"
#include "../../helpers-lib-includes_int.hpp"
#include "expanded-times-helpers.hpp"

namespace libs::helpers::statistic::helpers::functors
{
AddOpTime::AddOpTime (
  ExpandedTimes&                         obj,
  const ExpandedTimes::key_storage_type& id_set,
  const ExpandedTimes::key_storage_type& id_element) :
  obj_ (obj),
  skip_ (false),
  id_set_ (id_set),
  id_element_ (id_element)
{
  obj_.begin (id_set_, id_element_);
}


AddOpTime::~AddOpTime ()
{
  if (skip_)
  {
    obj_.end_skip ();
  }
  else
  {
    obj_.end ();
  }
}


void
AddOpTime::set_skip ()
{
  skip_ = true;
}


#ifdef U3_FAKE_DISABLE
void
change_last_name (const std::string& name)
{
  obj_.change_last_name (name);
}
#endif

void
dump (ExpandedTimes& obj, ::libs::link::ILink::ptr& logger)
{
#ifdef U3_FAKE_DISABLE
  ExpandedTimes::infos_type infos;
  obj.get (infos);
  for (const std::string& info : infos)
  {
    U ~3_MSG2LOGGER(logger, info, "statxx", ::libs::ievents::props::modules::log::LogLevels::info);
  }
#endif
}
}   // namespace libs::helpers::statistic::helpers::functors
