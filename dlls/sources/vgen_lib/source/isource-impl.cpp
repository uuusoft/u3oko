//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       isource-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.06.2016.
\copyright  www.uuusoft.com
\project    uuu_gen_lib
\brief      Class for incapsulate acess to driver
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "isource-impl.hpp"

namespace dlls { namespace sources { namespace gen_lib {

ISourceImpl::ISourceImpl () :
  started_ (false),
  simd_ (TypeExtCpu::usual)
{}


ISourceImpl::~ISourceImpl ()
{}


void
ISourceImpl::init ()
{
  init_int ();
  return;
}

void
ISourceImpl::start ()
{
  if (is_started ())
    {
      return;
    }

  started_ = true;
  start_int ();
  return;
}


void
ISourceImpl::stop ()
{
  if (!is_started ())
    {
      return;
    }

  started_ = false;
  stop_int ();
  return;
}


void
ISourceImpl::get_raw_data (keys2buffs_ptr_type& _buffs, transform_events_type* _events)
{
  get_raw_data_int (_buffs, _events);
  return;
}


void
ISourceImpl::set_cpu (TypeExtCpu _cpu)
{
  simd_ = _cpu;
  set_cpu_int (_cpu);
  return;
}


void
ISourceImpl::update_dinfo (const SourceInfo& _info)
{
  const bool _started = is_started ();

  if (_started)
    {
      stop ();
    }

  props_info_ = _info;
  update_dinfo_int (_info);

  if (_started)
    {
      start ();
    }
  return;
}


bool
ISourceImpl::is_started ()
{
  return is_started_int ();
}


bool
ISourceImpl::is_started_int ()
{
  return started_;
}

}}}      // namespace dlls::sources::gen_lib
