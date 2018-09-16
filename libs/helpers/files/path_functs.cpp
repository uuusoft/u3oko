//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       path_functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\brief      Функции для работы с файлами и директориями
\project    uuu_helpers
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "includes.hpp"
#include "path_functs.hpp"

namespace libs { namespace helpers { namespace files {

std::string
make_short_path (const std::string& _path)
{
  CHECK_STATE (!_path.empty (), "failed, empty path");

#if defined UUU_OS_WIN32_DESKTOP
  const auto _req_size = GetShortPathNameA (_path.c_str (), nullptr, 0);
  if (!_req_size)
    {
      XULOG_ERROR ("failed get buffer size from GetShortPathNameA, " << _path);
      return _path;
    }

  std::vector<char> _temp (_req_size);
  if (!GetShortPathNameA (_path.c_str (), &_temp[0], _temp.size ()))
    {
      XULOG_ERROR ("failed call GetShortPathNameA, for path " << _path);
      return _path;
    }
  return std::string (&_temp[0]);
#else
  return _path;
#endif
}


bool
create_folder (const std::string& _path)
{
  if (_path.empty ())
    {
      XULOG_WARNING ("try create empty path");
      return false;
    }

  std::string            _temp_path = _path;
  std::string::size_type _off_find  = 0;
  const std::string      _dividers  = "/\\";

  while (true)
    {
      std::string::size_type _find_div  = _temp_path.find_first_of (_dividers, _off_find);
      const std::string      _check_dir = _temp_path.substr (0, _find_div);

      _off_find = _find_div + 1;
      if (_check_dir.empty ())
        {
          continue;
        }

      boost::system::error_code _error;
      boost::filesystem::path   _check_path = _check_dir;

      XULOG_TRACE ("uuu_helpers::create_folder::prepare check " << _check_dir);
      if (!boost::filesystem::exists (_check_path, _error))
        {
          XULOG_TRACE ("uuu_helpers::create_folder::prepare make " << _check_dir);
          boost::filesystem::create_directory (_check_path, _error);
          if (_error)
            {
              XULOG_WARNING ("uuu_helpers::create_folder::failed make path " << _error.message ());
              return false;
            }
        }
      if (std::string::npos == _find_div)
        {
          break;
        }
    }
  return true;
}


void
delete_folder (const std::string& _path)
{
  boost::system::error_code _error;
  boost::filesystem::remove_all (_path, _error);
  UASSERT (!_error);
  return;
}


bool
is_folder (const std::string& _ppath)
{
  boost::filesystem::path _path = _ppath;
  return is_directory (_path) ? true : false;
}

}}}      // namespace libs::helpers::files
