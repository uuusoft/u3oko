//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       loader.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "loader.hpp"

namespace libs { namespace icore { namespace xml {

Loader::Loader (const TInitInfo& _info) :
  iinfo_ (_info)
{
#if defined(UUU_OS_WIN32_DESKTOP)
  impl_ = ::std::make_shared<general::LoaderFileImpl> (iinfo_);
#elif defined(UUU_OS_GNU_LINUX)
  impl_ = ::std::make_shared<general::LoaderFileImpl> (iinfo_);
#elif defined(UUU_OS_RASPBERRY)
  impl_ = ::std::make_shared<general::LoaderFileImpl> (iinfo_);
#elif defined(UUU_OS_ANDROID)
  impl_ = ::std::make_shared<android::LoaderAssetAndroidImpl> (iinfo_);
#else
#error select OS
#endif
  return;
}


void
Loader::load (const std::string& _file_name, const TypePath& _storage_type, IBlockMem::ptr& _bmem)
{
  XULOG_TRACE ("Loader::load::_file_name=" << _file_name.c_str ());
  UASSERT (!_file_name.empty ());
  CHECK_CALL (impl_->get (_file_name, _storage_type, _bmem), ("failed get file, " + _file_name).c_str ());
  //CHECK_STATE( _bmem->get() && _bmem->get_data_size(), ("failed load file, empty _bmem,"  + _file_name ).c_str() );
  return;
}


void
Loader::get_enum (const TypePath& _storage_type, NodeEnumFiles& _enum)
{
  return impl_->get_enum (_storage_type, _enum);
}

}}}      // namespace libs::icore::xml
