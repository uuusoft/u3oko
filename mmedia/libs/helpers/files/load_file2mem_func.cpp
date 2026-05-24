/**
\file       load_file2mem_funct.cpp
\date       23.02.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_lib_helpers
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "libs-helpers-files-includes.hpp"
#include "get_files_func.hpp"
#include "load_file2mem_func.hpp"

namespace libs::helpers::files
{
bool
load_file2mem (
  const std::string&                    file_path,
  ::libs::helpers::mem::IBlockMem::ptr& ret)
{
  U3_ASSERT (!file_path.empty ());
  ret.reset ();

  std::ifstream file (file_path, std::ios::binary | std::ios::in);
  auto          mem_allocator = ::utils::mem_funcs::impl::BlockMemAllocatorProxy::instance ()->impl ();

  if (!mem_allocator)
  {
    U3_XLOG_ERROR ("load_file2mem: empty mem allocator, skip path=" + file_path);
    return false;
  }
  if (!file.is_open ())
  {
    U3_XLOG_ERROR ("load_file2mem: open file for load, skip path=" + file_path);
    return false;
  }

  file.ignore (std::numeric_limits< std::streamsize >::max ());

  const auto size = file.gcount ();
  if (size <= 0)
  {
    // U3_XLOG_MARK ("load_file2mem: open empty file for load: " << file_path);
    // return false;
  }

  file.clear ();
  file.seekg (0, std::ios::beg);
  ret = mem_allocator->alloc (size);
  ret->set_data_size (size);
  file.read (::utils::mem_funcs::helpers::get_as< char > (ret.get ()), size);
  //::utils::mem_funcs::helpers::get_as< char > (ret.get ())[size] = '\0';
  return true;
}


bool
save_mem2file (
  const std::string&                          file_path,
  const ::libs::helpers::mem::IBlockMem::ptr& buf)
{
  std::ofstream file (file_path, std::ios::binary | std::ios::out | std::ios::ate);
  U3_ASSERT (!file_path.empty ());

  if (!file.is_open ())
  {
    U3_XLOG_ERROR ("save_mem2file: open file for save path=" + file_path);
    return false;
  }

  file.write (U3_CAST_REINTERPRET< char* > (buf->get ()), buf->get_data_size ());
  return true;
}


bool
is_file_exist (const std::string& file_path)
{
  U3_ASSERT (!file_path.empty ());
  std::error_code error;
  return std::filesystem::exists (file_path, error);
}


std::size_t
get_file_size (const std::string& path2file)
{
  U3_ASSERT (!path2file.empty ());
  std::ifstream file (path2file, std::ios::binary | std::ios::in | std::ios::ate);

  if (!file.is_open ())
  {
    U3_XLOG_WARN ("load_file2mem: to open file, skip path" + path2file);
    return 0;
  }
  return file.tellg ();
}
}   // namespace libs::helpers::files
