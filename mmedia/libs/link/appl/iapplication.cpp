/**
\file       iapplication.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../_make/libs-link-includes_int.hpp"
#include "iapplication.hpp"

namespace libs::link::appl
{
void
IApplication::appl_init (const InitApplication& info)
{
  U3_CALL_TRACE_INFO_DBG (TOLOG (info.service_name_) + TOLOG (info.company_name_) + TOLOG (info.appl_name_) + TOLOG (info.lib_name_));
  try
  {
    ::libs::utility::checks::throw_ifn (!init_);
    ::libs::utility::checks::throw_ifn (info.check ());

    appl_info_ = info;

    appl_init_int (info);
    init_appl_folders_int ();
    init_proxys_int ();
    init_appl_data_int ();
    init_links_int (info);
    update_catch_funcs_int ();
    init_done_int ();
    init_ = true;
  }
  catch (const std::exception& excpt)
  {
    U3_XLOG_ERROR (excpt.what ());
    // U3_LOG_APPL_EXCEPT (excpt.what ());
  }
}


void
IApplication::appl_work ()
{
  try
  {
    appl_work_int ();
  }
  catch (const std::exception& excpt)
  {
    U3_XLOG_ERROR (excpt.what ());
  }
}


auto
IApplication::appl_deinit () -> bool
{
  try
  {
    return appl_deinit_int ();
  }
  catch (const std::exception& excpt)
  {
    U3_XLOG_ERROR (excpt.what ());
  }
  return false;
}


void
IApplication::appl_force_stop ()
{
  try
  {
    appl_force_stop_int ();
  }
  catch (const std::exception& excpt)
  {
    U3_XLOG_ERROR (excpt.what ());
  }
}
}   // namespace libs::link::appl
