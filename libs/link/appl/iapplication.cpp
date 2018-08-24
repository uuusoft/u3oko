//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       IApplication.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "iapplication.hpp"

namespace libs { namespace link { namespace appl {

IApplication::IApplication () :
  init_ (false)
{}


IApplication::~IApplication ()
{}


void
IApplication::ainit (const InitApplication& _info)
{
  XULOG_TEST ("IApplication::ainit::beg, " << _info.name_subsys_);
  //grd_sync_type _grd(mtx_);
  UASSERT (!init_);

  init_int (_info);
  init_appl_folders_int ();
  init_proxys_int ();
  init_appl_data_int ();
  init_links_int (_info);
  update_catch_functs_int ();
  init_done_int ();

  init_ = true;
  XULOG_TEST ("IApplication::ainit::end, " << _info.name_subsys_);
  return;
}


void
IApplication::work ()
{
  //grd_sync_type _grd(mtx_);
  return work_int ();
}


bool
IApplication::deinit ()
{
  //grd_sync_type _grd(mtx_);
  return deinit_int ();
}

}}}      // namespace libs::link::appl
