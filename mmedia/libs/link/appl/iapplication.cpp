/**
\file       iapplication.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_link
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../libs-link-includes_int.hpp"
#include "iapplication.hpp"

namespace libs::link::appl
{
void
IApplication::appl_init (const InitApplication& info)
{
  U3_XLOG_DBG ("IApplication::appl_init::---->" + TOLOG (info.service_name_) + TOLOG (info.company_name_) + TOLOG (info.appl_name_) + TOLOG (info.subsys_name_) + TOLOG (info.lib_name_));
  U3_ASSERT (!init_)
  U3_ASSERT (info.check ())

  appl_info_ = info;

  appl_init_int (info);
  init_appl_folders_int ();
  init_proxys_int ();
  init_appl_data_int ();
  init_links_int (info);
  update_catch_funcs_int ();
  init_done_int ();

  init_ = true;
  U3_XLOG_DBG ("IApplication::appl_init::<----" + TOLOG (info.service_name_) + TOLOG (info.company_name_) + TOLOG (info.appl_name_) + TOLOG (info.subsys_name_) + TOLOG (info.lib_name_));
}


void
IApplication::appl_work ()
{
  appl_work_int ();
}


auto
IApplication::appl_deinit () -> bool
{
  return appl_deinit_int ();
}


void
IApplication::appl_force_stop ()
{
  appl_force_stop_int ();
}
}   // namespace libs::link::appl
