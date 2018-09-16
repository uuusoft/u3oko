//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       loader-code.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "../includes_int.hpp"
#include "loader-code.hpp"

namespace libs { namespace ilink { namespace loader {

LoaderCode::LoaderCode ()
{}


LoaderCode::~LoaderCode ()
{
  impl_.reset ();
}


void
LoaderCode::load (
  const RunCodeType&              _type,
  const CreateInfo*               _info,
  const std::string&              _name_proc,
  const std::string&              _name_lib,
  const std::vector<std::string>& _args)
{
  XULOG_TRACE ("LoaderCode::load:: " << _name_lib);
  if (::libs::link::details::RunCodeType::appl == _type)
    {
      XULOG_ERROR ("temporarily disabled");
      impl_.reset (new OutProcLoaderCode);
    }
  else if (::libs::link::details::RunCodeType::dll == _type)
    {
      impl_.reset (new InProcLoaderCode);
    }

  UASSERT (impl_);
  impl_->load (_info, _name_proc, _name_lib, _args);
  return;
}


bool
LoaderCode::is_load () const
{
  return impl_->is_load ();
}


bool
LoaderCode::unload (bool _force)
{
  return impl_->unload (_force);
}

}}}      // namespace libs::ilink::loader
