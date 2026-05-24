/**
\file       codec-brower.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_gen
\brief      Реализация объекта для поиска кодеков в системе
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../vcodec-gen-includes_int.hpp"
#include "codec-brower.hpp"

namespace dlls::codecs::vcodec_gen::browser::consts
{
const std::string id_codecs_in_name_file = "vvd_";
}

namespace dlls::codecs::vcodec_gen::browser
{
CodecBrower::CodecBrower ()
{
}


CodecBrower::~CodecBrower ()
{
}


std::string
CodecBrower::get_codec (const libs::helpers::uids::minor::id_val& id)
{
  lock_type lock (mtx_);
  refresh_list_codecs ();

  const auto find = format2file_.find (id);
  if (format2file_.end () == find)
  {
    U3_LOG_DATA_WRN ("not find codec for format=" + ::libs::helpers::uids::helpers::get_readable_name (id));
    return "";
  }
  return find->second;
}


void
CodecBrower::refresh_list_codecs ()
{
  U3_LOG_DATA_DEV ("START CodecBrower::refresh_list_codecs" + VTOLOG (refreshed_));
  if (refreshed_)
  {
    return;
  }

  format2file_.clear ();
  refreshed_ = true;

  const std::string                     libs_path = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  ::libs::helpers::files::NodeEnumFiles files;

#ifdef U3_BUILD_MODULES_AS_LIBS
  files.files_ = ::libs::proxy::get_list_dlls_as_libs ();
#else
  ::libs::helpers::files::get_files (
    libs_path,
    files,
    { syn::IncludeSubFolders::disabled, syn::IncludeFiles::enabled, syn::Recursives::disabled },
    [] (const boost::filesystem::path& lib_path) {
      const std::string file_name = lib_path.filename ().string ();
      const std::size_t pos       = file_name.find (consts::id_codecs_in_name_file);

      if (std::string::npos == pos)
      {
        return false;
      }
      return true;
    });
#endif

  for (const auto& file : files.files_)
  {
    U3_LOG_DATA_DEV ("get info from codec" + TOLOG (file.name_));
    CodecImplInfo impl;

    helpers::load_codec_from_file (false, file.name_, impl);
    libs::helpers::uids::minor::id_val formats[4];
    impl.get_codec_info_ (formats);

    for (const auto& format : formats)
    {
      if (format == libs::helpers::uids::minor::id_val::unknown)
      {
        continue;
      }
      format2file_.insert (format2file_type::value_type (format, file.name_));
      U3_LOG_DATA_DEV ("found codec format: " + ::libs::helpers::uids::helpers::get_readable_name (format) + TOLOG (file.name_));
    }
  }
}
}   // namespace dlls::codecs::vcodec_gen::browser
