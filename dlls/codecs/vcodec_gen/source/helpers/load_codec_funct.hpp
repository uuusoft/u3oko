//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       load_codec_funct.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace vcodec_gen { namespace helpers {
/**
\brief  ???
*/
inline void
load_codec_from_file (
  bool               _decorate_name,
  const std::string& _file_name,
  CodecImplInfo&     _info)
{
  const std::string _path          = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  const std::string _dec_file_name = _decorate_name ? ::utils::mem_functs::files::decorate_dll_name (_file_name) : _file_name;
  const std::string _full_path     = ::libs::helpers::files::make_path (_path, _dec_file_name);

  _info.lib_.load (_full_path.c_str (), boost::dll::load_mode::rtld_now);

  _info.pf_create_codec_ = boost::dll::import<functs::get_codec_funct_type> (_info.lib_, consts::name_funct_create_codec);
  _info.pf_free_codec_   = boost::dll::import<functs::free_codec_funct_type> (_info.lib_, consts::name_funct_delete_codec);
  _info.pf_get_info_     = boost::dll::import<functs::get_codec_info_funct_type> (_info.lib_, consts::name_get_funct_info);

  UASSERT (_info.check ());
  return;
}

}}}}      // namespace dlls::codecs::vcodec_gen::helpers
