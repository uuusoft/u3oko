/**
\file       isource-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.06.2016
\project    u3_vgen_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "gen-lib-includes_int.hpp"
#include "isource-impl.hpp"

namespace dlls::sources::gen_lib
{
ISourceImpl::ISourceImpl () :
  started_ (false),
  simd_ (syn::CpuExts::usual),
  send_interfaces_ (false)
{
}


ISourceImpl::~ISourceImpl ()
{
}


void
ISourceImpl::init ()
{
  try
  {
    init_int ();
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
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
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
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
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
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
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


void
ISourceImpl::get_raw_data (syn::pkeys2bufs_type& bufs, syn::tevents_type* events)
{
  try
  {
    get_raw_data_int (bufs, events);
  }
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
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
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
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
  catch (const std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
}


bool
ISourceImpl::is_source_started ()
{
  return is_source_started_int ();
}


bool
ISourceImpl::is_source_started_int ()
{
  return started_;
}
}   // namespace dlls::sources::gen_lib
