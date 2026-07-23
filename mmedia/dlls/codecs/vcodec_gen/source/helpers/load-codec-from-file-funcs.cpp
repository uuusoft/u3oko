/**
\file       load-codec-from-file-funcs.cpp
\date       14.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_vcodec_gen
*/
#include "../vcodec-gen-includes_int.hpp"
#include "load-codec-from-file-funcs.hpp"

namespace dlls::codecs::vcodec_gen::helpers
{
auto
make_name_function (const std::string& lib_name, const std::string& prefix_funct) -> std::string
{
  return prefix_funct + "_" + libs::utility::dlls::undecorate_dll_name (lib_name);
}


void
load_codec_from_file (
  bool               decorate_name,
  const std::string& file_name,
  CodecImplInfo&     info)
{
  const std::string path          = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  const std::string dec_file_name = decorate_name ? ::libs::utility::dlls::decorate_dll_name (file_name) : file_name;
  const std::string full_path     = ::libs::utility::files::make_path (path, dec_file_name);

  info.lib_.load (full_path.c_str (), boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);

#if (U3_BUILD_MODULES_AS_LIBS == 1)
  info.create_codec_   = ::libs::proxy::get_create_codec_func (file_name);
  info.free_codec_     = ::libs::proxy::get_free_codec_func (file_name);
  info.get_codec_info_ = ::libs::proxy::get_info_codec_func (file_name);
#else
  info.create_codec_ = ::boost::dll::import_symbol< funcs::get_codec_func_type > (
    info.lib_, make_name_function (file_name, consts::func_name_create_codec));

  info.free_codec_ = ::boost::dll::import_symbol< funcs::free_codec_func_type > (
    info.lib_, make_name_function (file_name, consts::func_name_delete_codec));

  info.get_codec_info_ = ::boost::dll::import_symbol< funcs::get_codec_info_func_type > (
    info.lib_, make_name_function (file_name, consts::func_name_get_info));
#endif

  U3_CHECK (info.create_codec_, "empty info.create_codec_");
  U3_CHECK (info.free_codec_, "empty info.free_codec_");
  U3_CHECK (info.get_codec_info_, "empty info.get_codec_info_");
  U3_CHECK (info.check (), "failed load codec" + TOLOG (file_name) + TOLOG (full_path));
}
}   // namespace dlls::codecs::vcodec_gen::helpers
