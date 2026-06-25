/**
\file       path_funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
\brief      Функции для работы с файлами и директориями
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "libs-helpers-files-includes.hpp"
#include "path_funcs.hpp"

namespace boost::interprocess::ipcdetail
{
#ifdef U3_OS_ANDROID
void
get_shared_dir (std::string& shared_dir)
{
  shared_dir = "storage/emulated/0/Android/data/com.uuusoft.u3oko/files";
  U3_XLOG_DEV ("get_shared_dir::probably invalid shared directory! fix" + TOLOG (shared_dir));
}
#endif
}   // namespace boost::interprocess::ipcdetail


namespace libs::helpers::files
{
std::string
make_short_path (const std::string& path)
{
  U3_CHECK (!path.empty (), "empty path");

#ifdef U3_OS_WIN32_DESKTOP
  const auto req_size = GetShortPathNameA (path.c_str (), nullptr, 0);
  if (0 == req_size || req_size >= 0xFFFFu)
  {
    U3_XLOG_ERROR ("invalid buf size from GetShortPathNameA" + TOLOG (path) + VTOLOG (req_size));
    return path;
  }

  std::vector< char > temp (req_size + 1);
  if (!GetShortPathNameA (path.c_str (), &temp[0], U3_CAST_UINT32 (temp.size ())))
  {
    U3_XLOG_ERROR ("call GetShortPathNameA, for path=" + path);
    return path;
  }
  return std::string (&temp[0]);
#else
  return path;
#endif
}


bool
create_folder (const std::string& path)
{
  if (path.empty ())
  {
    U3_XLOG_WARN ("try create empty path");
    return false;
  }

  std::string            temp_path = path;
  std::string::size_type off_find  = 0;
  const std::string      dividers  = "/\\";

  while (true)
  {
    std::string::size_type find_div  = temp_path.find_first_of (dividers, off_find);
    const std::string      check_dir = temp_path.substr (0, find_div);

    off_find = find_div + 1;
    if (check_dir.empty ())
    {
      continue;
    }

    std::error_code       error;
    std::filesystem::path check_path = check_dir;

    if (!std::filesystem::exists (check_path, error))
    {
      std::filesystem::create_directory (check_path, error);
      if (error)
      {
        U3_XLOG_WARN ("failed create a folder" + TOLOG (check_path.string ()) + " error=" + error.message ());
        return false;
      }
    }

    if (std::string::npos == find_div)
    {
      break;
    }
  }
  return true;
}


void
delete_folder (const std::string& path)
{
  boost::system::error_code error;
  boost::filesystem::remove_all (path, error);
  U3_ASSERT (!error);
}


bool
is_folder (const std::string& ppath)
{
  boost::filesystem::path path = ppath;
  return is_directory (path) ? true : false;
}


std::string
get_name_from_path (const std::string& path)
{
  auto indx = path.rfind ("/");
  if (std::string::npos == indx)
  {
    indx = path.rfind ("\\");
  }
  if (std::string::npos == indx)
  {
    return path;
  }
  return path.substr (indx + 1);
}


std::string
prepare_for_file_name (const std::string_view& src)
{
  std::string ret { src.data (), src.size () };

  std::transform (
    ret.begin (),
    ret.end (),
    ret.begin (),
    [] (char val) -> char {
      return (val == '\\') || (val == '/') ? consts::special_convert_path_symbol : val;
    });
  return ret;
}
}   // namespace libs::helpers::files
