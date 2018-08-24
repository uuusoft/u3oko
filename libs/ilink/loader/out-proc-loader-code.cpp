//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       out-proc-loader-code.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "out-proc-loader-code.hpp"

namespace libs { namespace ilink { namespace loader {

OutProcLoaderCode::OutProcLoaderCode () :
  info_ (nullptr)
{
  //thread_done_.store( true );
}


OutProcLoaderCode::~OutProcLoaderCode ()
{
  while (!unload (true))
    {
    }
}


void
OutProcLoaderCode::load_int (
  const CreateInfo*  _info,
  const std::string& _name_proc,
  const std::string& _name_lib,
  const args_type&   _args)
{
  info_ = _info;
  UASSERT_SIGNAL ("process");
#if 0
    if ( !child_process_ )
    {
      child_process_.reset (
        new boost::process::child (
          boost::process::launch ( _name_proc, _args, _cntx ) ) );
    }
#endif
  return;
}


bool
OutProcLoaderCode::is_load_int () const
{
  UASSERT_SIGNAL ("process");
  return false;
#if 0
    //return child_process_ && *child_process_ ? true : false;
    return child_process_ && child_process_-> get_id () ? true : false;
#endif
}


bool
OutProcLoaderCode::unload_int (bool _force)
{
  UASSERT_SIGNAL ("process");
#if 0
    if ( child_process_ )
    {
      if ( _force )
      {
        UASSERT_SIGNAL( "process" );
        //child_process_->terminate (false );
      }

      UASSERT_SIGNAL( "process" );
      //child_process_->wait ();
      child_process_.reset ();
    }
#endif
  return true;
}


void
OutProcLoaderCode::set_name_lib (const std::string& _name_lib)
{
  UASSERT (!_name_lib.empty ());
  name_lib_ = _name_lib;
  return;
}

}}}      // namespace libs::ilink::loader
