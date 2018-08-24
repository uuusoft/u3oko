//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       get_sort_files_functs.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      empty brief
*/

namespace modules { namespace uuu_log { namespace appl { namespace helpers {
/**
  \brief
  */
inline list_folders_type
get_sort_by_time_folders (const std::string& _path2sessions)
{
  UASSERT (!_path2sessions.empty ());

  NodeEnumFiles     _enum_files;
  list_folders_type _folders;

  ::libs::helpers::files::get_files (
    _path2sessions,
    _enum_files,
    ::libs::helpers::files::TypeIncludeSubFolders::enabled,
    ::libs::helpers::files::TypeIncludeFiles::disabled,
    ::libs::helpers::files::TypeRecursive::disabled);

  std::map<std::size_t, std::string> _sort_files;

  for (const auto& _file : _enum_files.folders_)
    {
      bfs::path         _path (::libs::helpers::files::make_path (_path2sessions, _file.name_));
      bss::error_code   _error;
      const std::size_t _time = bfs::last_write_time (_path, _error);

      UASSERT (!_error);
      UASSERT (_sort_files.end () == _sort_files.find (_time));
      UASSERT (_time);

      _sort_files[_time] = _file.name_;
    }

  std::for_each (
    _sort_files.begin (),
    _sort_files.end (),
    [&_folders](const decltype (_sort_files)::value_type& _node) { _folders.push_back( _node.second );  return; });

  return _folders;
}
/**
  \brief
  */
inline std::vector<std::string>
get_sort_by_time_files (const std::string& _path2session)
{
  UASSERT (!_path2session.empty ());

  NodeEnumFiles            _enum_files;
  std::vector<std::string> _ret;

  ::libs::helpers::files::get_files (
    _path2session,
    _enum_files,
    ::libs::helpers::files::TypeIncludeSubFolders::disabled,
    ::libs::helpers::files::TypeIncludeFiles::enabled,
    ::libs::helpers::files::TypeRecursive::disabled);

  std::map<std::size_t, std::string> _sort_files;

  for (const auto& _file : _enum_files.files_)
    {
      bfs::path         _path (::libs::helpers::files::make_path (_path2session, _file));
      bss::error_code   _error;
      const std::size_t _time = bfs::last_write_time (_path, _error);

      UASSERT (!_error);
      UASSERT (_sort_files.end () == _sort_files.find (_time));
      UASSERT (_time);

      _sort_files[_time] = _file;
    }

  std::for_each (
    _sort_files.begin (),
    _sort_files.end (),
    [&_ret](const decltype (_sort_files)::value_type& _node) { _ret.push_back( _node.second );  return; });

  return _ret;
}

}}}}      // namespace modules::uuu_log::appl::helpers
