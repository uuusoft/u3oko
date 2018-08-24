//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       codec-brower.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      Реализация объекта для поиска кодеков в системе.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "codec-brower.hpp"

namespace dlls { namespace codecs { namespace vcodec_gen { namespace browser { namespace consts {

const std::string id_codecs_in_name_file = "vvd_";      //< ???

}}}}}      // namespace dlls::codecs::vcodec_gen::browser::consts


namespace dlls { namespace codecs { namespace vcodec_gen { namespace browser {
//  syn
using ::libs::helpers::files::NodeEnumFiles;

CodecBrower::CodecBrower () :
  refreshed_ (false)
{}


CodecBrower::~CodecBrower ()
{}


std::string
CodecBrower::get_codec (const cuuid& _id)
{
  guard_type _grd (mtx_);

  refresh_list_codecs ();

  const auto _find = guid2file_.find (_id);
  if (guid2file_.end () == _find)
    {
      XULOG_WARNING ("failed find codec for guid, " << _id.name () << " as " << ::libs::helpers::uids::helpers::get_readable_name (_id));
      return "";
    }
  return _find->second;
}


void
CodecBrower::refresh_list_codecs ()
{
  if (refreshed_)
    {
      return;
    }

  guid2file_.clear ();

  refreshed_ = true;

  const std::string _path = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  NodeEnumFiles     _enum_files;

  ::libs::helpers::files::get_files (
    _path,
    _enum_files,
    ::libs::helpers::files::TypeIncludeSubFolders::disabled,
    ::libs::helpers::files::TypeIncludeFiles::enabled,
    ::libs::helpers::files::TypeRecursive::disabled,
    [](const boost::filesystem::path& _path) {
      const std::string _file_name = _path.filename ().string ();
      const std::size_t _pos       = _file_name.find (consts::id_codecs_in_name_file);

      if (std::string::npos == _pos)
        {
          return false;
        }
      /*
        //  может начинатся не с начала имени файла в ряде платформ.
        if( 0 != _pos )
        {
          return false;
        }
        */
      return true;
    });

  for (const auto& _file_name : _enum_files.files_)
    {
      CodecImplInfo _info;
      cuuid         _guid;

      helpers::load_codec_from_file (false, _file_name, _info);
      _info.pf_get_info_ (&_guid);
      guid2file_.insert (guid2file_type::value_type (_guid, _file_name));
    }
  return;
}

}}}}      // namespace dlls::codecs::vcodec_gen::browser
