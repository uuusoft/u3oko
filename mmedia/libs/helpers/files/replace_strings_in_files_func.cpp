/**
\file       replace_strings_in_files_funct.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
void
replace_strings_in_files (
  const std::string&                                     path2folder,
  const ::libs::helpers::strings::syn::replace_val_type* vals,
  const std::uint32_t                                    count_vals,
  const std::string&                                     files_mask)
{
  ::libs::helpers::files::NodeEnumFiles enum_files;

  ::libs::helpers::files::get_files (
    path2folder,
    enum_files,
    { ::libs::helpers::files::IncludeSubFolders::disabled, ::libs::helpers::files::IncludeFiles::enabled, ::libs::helpers::files::Recursives::disabled },
    ::libs::helpers::files::DefaultFileMask (files_mask));

  U3_ASSERT (!enum_files.files_.empty ());

  for (const auto& file : enum_files.files_)
  {
    const std::string                    full_path = ::libs::helpers::files::make_path (path2folder, file.name_);
    ::libs::helpers::mem::IBlockMem::ptr file_data;
    // U3_XLOG_DBG ("change template" + TOLOG (file.name_));
    if (!::libs::helpers::files::load_file2mem (full_path, file_data))
    {
      U3_XLOG_ERROR ("open template" + TOLOG (full_path));
      continue;
    }

    std::string buf (::libs::helpers::casts::reinterpret_cast_helper< char* > (file_data->get ()), file_data->get_data_size ());
    std::string dstbuf;

    if (::libs::helpers::strings::replace_substring (vals, count_vals, buf, dstbuf))
    {
      file_data->resize (dstbuf.length () + 1);
      file_data->set_data_size (dstbuf.length ());
      memcpy (file_data->get (), dstbuf.c_str (), dstbuf.length ());

      if (!::libs::helpers::files::save_mem2file (full_path, file_data))
      {
        U3_XLOG_ERROR ("update file" + TOLOG (full_path));
      }
    }
  }
}
}   // namespace libs::helpers::files
