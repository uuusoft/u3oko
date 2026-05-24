/**
\file       load_codec_funct.cpp
\date       14.04.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../vcodec-gen-includes_int.hpp"
#include "load_codec_func.hpp"

namespace dlls::codecs::vcodec_gen::helpers
{
std::string
make_name_function (const std::string& lib_name, const std::string& prefix_funct)
{
  return prefix_funct + "_" + libs::helpers::dlls::undecorate_dll_name (lib_name);
}


void
load_codec_from_file (
  bool               decorate_name,
  const std::string& file_name,
  CodecImplInfo&     info)
{
  const std::string path          = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  const std::string dec_file_name = decorate_name ? ::libs::helpers::dlls::decorate_dll_name (file_name) : file_name;
  const std::string full_path     = ::libs::helpers::files::make_path (path, dec_file_name);

  info.lib_.load (full_path.c_str (), boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);

#ifdef U3_BUILD_MODULES_AS_LIBS
  info.create_codec_   = ::libs::proxy::get_create_codec_func (file_name);
  info.free_codec_     = ::libs::proxy::get_free_codec_func (file_name);
  info.get_codec_info_ = ::libs::proxy::get_info_codec_func (file_name);
#else
#  if defined(U3_OS_ANDROID)
  const auto native    = info.lib_.native ();
  info.create_codec_   = reinterpret_cast< funcs::get_codec_func_type* > (dlsym (native, make_name_function (file_name, consts::func_name_create_codec).c_str ()));
  info.free_codec_     = reinterpret_cast< funcs::free_codec_func_type* > (dlsym (native, make_name_function (file_name, consts::func_name_delete_codec).c_str ()));
  info.get_codec_info_ = reinterpret_cast< funcs::get_codec_info_func_type* > (dlsym (native, make_name_function (file_name, consts::func_name_get_info).c_str ()));
#  else
  info.create_codec_   = ::boost::dll::import_symbol< funcs::get_codec_func_type > (info.lib_, make_name_function (file_name, consts::func_name_create_codec));
  info.free_codec_     = ::boost::dll::import_symbol< funcs::free_codec_func_type > (info.lib_, make_name_function (file_name, consts::func_name_delete_codec));
  info.get_codec_info_ = ::boost::dll::import_symbol< funcs::get_codec_info_func_type > (info.lib_, make_name_function (file_name, consts::func_name_get_info));
#  endif
#endif

  U3_CHECK (info.create_codec_, "empty info.create_codec_");
  U3_CHECK (info.free_codec_, "empty info.free_codec_");
  U3_CHECK (info.get_codec_info_, "empty info.get_codec_info_");
  U3_CHECK (info.check (), "failed load codec" + TOLOG (file_name) + TOLOG (full_path));
}
}   // namespace dlls::codecs::vcodec_gen::helpers
