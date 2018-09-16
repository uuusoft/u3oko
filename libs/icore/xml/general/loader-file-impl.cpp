//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       loader-file-impl.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "loader-file-impl.hpp"

namespace libs { namespace icore { namespace xml { namespace general {

LoaderFileImpl::LoaderFileImpl (const TInitInfo& _info) :
  iinfo_ (_info)
{}


LoaderFileImpl::~LoaderFileImpl ()
{}


void
LoaderFileImpl::get_enum_int (const TypePath& _storage_type, NodeEnumFiles& _enum_files)
{
  const std::string _root = iinfo_.paths_->get_path (_storage_type);

  CHECK_STATE (::libs::helpers::files::is_folder (_root), "failed, root not dir" + _root);

  _enum_files.clear ();

  ::libs::helpers::files::get_files (
    _root,
    _enum_files,
    ::libs::helpers::files::TypeIncludeSubFolders::enabled,
    ::libs::helpers::files::TypeIncludeFiles::enabled,
    ::libs::helpers::files::TypeRecursive::enabled);

  return;
}


bool
LoaderFileImpl::get_int (const std::string& _file_name, const TypePath& _storage_type, IBlockMem::ptr& _ret)
{
  const std::string _dir_path  = iinfo_.paths_->get_path (_storage_type);
  const std::string _file_path = ::libs::helpers::files::make_path (_dir_path, _file_name);

  return ::libs::helpers::files::load_file2mem (_file_path, _ret);
}

}}}}      // namespace libs::icore::xml::general
