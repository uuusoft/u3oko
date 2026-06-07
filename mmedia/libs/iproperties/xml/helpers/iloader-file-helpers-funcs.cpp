/**
\file       load_funcs_atomic_value.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       17.02.2022
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../libs-iproperties-xml-includes_int.hpp"

namespace libs::iproperties::xml::helpers
{
void
enum_files_function (
  ::libs::helpers::files::NodeEnumFiles& node,
  const std::string&                     add_root,
  const func_enum_files_type&            funct)
{
  funct (node, add_root);
  for (auto& folder : node.folders_)
  {
    const std::string next_add_root = ::libs::helpers::files::make_path (add_root, folder.name_);
    enum_files_function (folder, next_add_root, funct);
  }
}


void
copy_files (
  Loader&                  loader,
  const appl_paths::Paths& path_type,
  const std::string&       source_folder,
  const std::string&       dest)
{
  ::libs::helpers::files::NodeEnumFiles root_node;
  bool                                  find_source_folder = false;

  ::libs::helpers::files::create_folder (dest);
  loader.get_enum (path_type, root_node, "");

  enum_files_function (
    root_node,
    "",
    [&dest, &path_type, &loader, &source_folder, &find_source_folder] (
      const ::libs::helpers::files::NodeEnumFiles& node,
      const std::string&                           add_root) {
      const std::string prev_path              = ::libs::helpers::files::make_path (dest, add_root);
      bool              now_find_source_folder = (find_source_folder || add_root.empty ()) && (source_folder == add_root.substr (0, source_folder.length ()));

      for (const auto& folder : node.folders_)
      {
        if (source_folder.empty () || (!find_source_folder && folder.name_ == source_folder) || now_find_source_folder)
        {
          find_source_folder = true;

          const std::string path_folder = ::libs::helpers::files::make_path (prev_path, folder.name_);
          ::libs::helpers::files::create_folder (path_folder);
        }
      }

      if (!source_folder.empty () && !now_find_source_folder)
      {
        return;
      }

      for (const auto& file : node.files_)
      {
        const std::string                    src_path_file = ::libs::helpers::files::make_path (add_root, file.name_);
        const std::string                    dst_path_file = ::libs::helpers::files::make_path (prev_path, file.name_);
        ::libs::helpers::mem::IBlockMem::ptr file_data;

        loader.load (src_path_file, path_type, file_data);

        if (file_data)
        {
          std::ofstream file_stream (dst_path_file.c_str (), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
          if (file_data->get_data_size ())
          {
            file_stream.write (::libs::helpers::casts::reinterpret_cast_helper< char* > (file_data->get ()), file_data->get_data_size ());
          }
        }
        else
        {
          U3_XLOG_ERROR ("load file to memory" + TOLOG (src_path_file) + " for copy to" + TOLOG (dst_path_file));
        }
      }
      return;
    });
}
}   // namespace libs::iproperties::xml::helpers
