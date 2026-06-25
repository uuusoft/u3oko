/**
\file       replace_strings_in_files_func.cpp
\author     Erashov Anton erashov2026@proton.me
\date       25.10.2024
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "libs-helpers-files-includes.hpp"
#include "get_files_func.hpp"
#include "replace_strings_in_files_func.hpp"

namespace libs::helpers::files
{
std::uint32_t
replace_strings_in_files (
  const std::string&                    path2folder,
  const strings::syn::replace_val_type* vals,
  const std::uint32_t                   count_vals,
  const std::string&                    files_mask)
{
  std::uint32_t counter_ops = 0;
  NodeEnumFiles enum_files;

  get_files (
    path2folder,
    enum_files,
    { IncludeSubFolders::disabled, IncludeFiles::enabled, Recursives::disabled },
    DefaultFileMask (files_mask));

  U3_ASSERT (!enum_files.files_.empty ());

  for (const auto& file : enum_files.files_)
  {
    const std::string                    full_path = make_path (path2folder, file.name_);
    ::libs::helpers::mem::IBlockMem::ptr file_data;
    // U3_XLOG_DBG ("change template" + TOLOG (file.name_));
    if (!load_file2mem (full_path, file_data))
    {
      U3_XLOG_ERROR ("open template" + TOLOG (full_path));
      continue;
    }

    std::string buf (::libs::helpers::casts::reinterpret_cast_helper< char* > (file_data->get ()), file_data->get_data_size ());
    std::string dstbuf;

    if (::libs::helpers::strings::replace_substring (vals, count_vals, buf, dstbuf))
    {
      ++counter_ops;
      file_data->resize (dstbuf.length () + 1);
      file_data->set_data_size (dstbuf.length ());
      memcpy (file_data->get (), dstbuf.c_str (), dstbuf.length ());

      if (!save_mem2file (full_path, file_data))
      {
        U3_XLOG_ERROR ("update file" + TOLOG (full_path));
      }
    }
  }
  return counter_ops;
}
}   // namespace libs::helpers::files
