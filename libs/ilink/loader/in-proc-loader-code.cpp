//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       in-proc-loader-code.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "in-proc-loader-code.hpp"

namespace libs { namespace ilink { namespace loader {
//  int types
using ExceptionLogger = ::modules::uuu_log::appl::thread::ExceptionLogger<::libs::link::ILink::ptr>;

InProcLoaderCode::InProcLoaderCode () :
  info_ (nullptr)
{
  thread_done_.store (true);
}


InProcLoaderCode::~InProcLoaderCode ()
{
  while (!unload (true))
    {
    }
}


void
InProcLoaderCode::load_int (
  const CreateInfo*  _info,
  const std::string& _name_proc,
  const std::string& _name_lib,
  const args_type&   _args)
{
  info_ = _info;

  if (child_thread_.joinable ())
    {
      return;
    }

  thread_done_.store (false);
  set_name_lib (_name_lib);

  XULOG_TRACE ("InProcLoaderCode::load_int::start thread:: " << _name_lib);
  child_thread_ = std::thread (
    ::libs::helpers::thread::generic_thread_funct<InProcLoaderCode, ExceptionLogger>,
    this,
    ExceptionLogger (::libs::link::ILink::ptr ()),
    UUU_ICAST_USHORT (0));
  return;
}


bool
InProcLoaderCode::is_load_int () const
{
  return child_thread_.joinable () ? true : false;
}


bool
InProcLoaderCode::unload_int (bool _force)
{
  if (child_thread_.joinable ())
    {
      if (thread_done_.load ())
        {
          std::this_thread::yield ();
          child_thread_.detach ();
          return true;
        }
    }
  else
    {
      thread_done_.store (true);
    }
  return thread_done_.load () ? true : false;
}


void
InProcLoaderCode::thread_funct_impl (std::size_t _indx_thread)
{
  XULOG_TRACE ("InProcLoaderCode::thread_funct::beg, " << name_lib_);
  boost::filesystem::path _fullpath (::libs::iproperties::appl_paths::get_current_folder ());
  const std::string       _sfullpath = _fullpath.string ();
  InitApplication         _info;

  _info.name_company_ = info_->id2val_[link::consts::text::id_company_name];
  _info.name_appl_    = info_->id2val_[link::consts::text::id_appl_name];
  _info.name_lib_     = info_->id2val_[link::consts::text::id_lib_name];
  _info.name_subsys_  = info_->id2val_[link::consts::text::id_subsys_name];

  XULOG_TRACE (_sfullpath);
  thread_appl_.reset (new ::libs::link::appl::IApplicationProxy (_sfullpath.c_str (), name_lib_.c_str ()));

  auto _impl = thread_appl_->impl ();

  XULOG_TRACE("InProcLoaderCode::thread_funct, " << _sfullpath << ", " << name_lib_ << ", " << to_str (_impl));
  if (_impl)
    {
      _impl->ainit (_info);
      _impl->work ();
    }
  return;
}


void
InProcLoaderCode::thread_postfunct_impl ()
{
  thread_done_.store (true);
  UASSERT (thread_appl_);
  UASSERT (thread_appl_->impl ());
  return;
}


void
InProcLoaderCode::set_name_lib (const std::string& _name_lib)
{
  UASSERT (!_name_lib.empty ());
  name_lib_ = _name_lib;
  return;
}

}}}      // namespace libs::ilink::loader
