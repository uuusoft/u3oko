/**
\file       isource-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
\project    u3_vgen_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "gen-lib-includes_int.hpp"
#include "isource-impl.hpp"

namespace dlls::sources::gen_lib
{
void
ISourceImpl::init ()
{
  try
  {
    init_int ();
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
}


void
ISourceImpl::start ()
{
  try
  {
    if (is_source_started ())
    {
      return;
    }

    started_ = true;
    start_int ();
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
}


void
ISourceImpl::stop ()
{
  try
  {
    if (!is_source_started ())
    {
      return;
    }

    started_         = false;
    send_interfaces_ = false;
    stop_int ();
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
}


void
ISourceImpl::get_sources (std::vector< syn::DataSourceInfo >& sources)
{
  try
  {
    sources.clear ();
    get_sources_int (sources);
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
}


void
ISourceImpl::get_raw_data (syn::pkeys2bufs_type& bufs, syn::tevents_type* events)
{
  try
  {
    get_raw_data_int (bufs, events);
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
}


void
ISourceImpl::set_cpu (syn::CpuExts cpu)
{
  try
  {
    simd_ = cpu;
    set_cpu_int (cpu);
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
}


void
ISourceImpl::update_source_info (const SourceImplInfo& info)
{
  try
  {
    const bool started = is_source_started ();
    if (started)
    {
      stop ();
    }

    srcimpinfo_ = info;
    update_source_info_int (info);

    if (started)
    {
      start ();
    }
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
}


auto
ISourceImpl::is_source_started () -> bool
{
  return is_source_started_int ();
}


auto
ISourceImpl::is_source_started_int () -> bool
{
  return started_;
}
}   // namespace dlls::sources::gen_lib
