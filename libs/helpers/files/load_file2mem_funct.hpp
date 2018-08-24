//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       load_file2mem_funct.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_lib_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace files {
//  syn
using ::utils::mem_functs::IBlockMem;
/**
  \brief      Свободная функция загрузки содержимого файла в память.
  \param[in]  _file_path  путь к файлу.
  \param[out] _ret        возвращаемый блок памяти с содержимым файла.
  \return     true, если загрузка прошла успешно.
  */
inline bool
load_file2mem (const std::string& _file_path, IBlockMem::ptr& _ret)
{
  std::ifstream _file (_file_path, std::ios::binary | std::ios::in | std::ios::ate);
  UASSERT (!_file_path.empty ());

  _ret.reset ();

  if (!_file.is_open ())
    {
      XULOG_WARNING ("load_file2mem: failed load file, skip, " << _file_path);
      return false;
    }

  const std::size_t _size = _file.tellg ();

  _file.seekg (0, std::ios::beg);
  _ret = ::utils::mem_functs::impl::BlockMemAllocatorProxy::instance ()->impl ()->alloc (_size + 1);
  _ret->set_data_size (_size);
  _file.read (::utils::mem_functs::helpers::get_as<char> (_ret.get ()), _size);
  ::utils::mem_functs::helpers::get_as<char> (_ret.get ())[_size] = '\0';
  return true;
}
/**
  \brief      Свободная функция загрузки содержимого файла в память.
  \param[in]  _file_path  путь к файлу.
  \param[out] _ret        возвращаемый блок памяти с содержимым файла.
  \return     true, если загрузка прошла успешно.
  */
template <typename TContainer>
bool
load_file2mem (const std::string& _file_path, TContainer& _ret)
{
  XULOG_TRACE ("load_file2mem: beg, " << _file_path);
  std::ifstream _file (_file_path, std::ios::binary | std::ios::in | std::ios::ate);
  UASSERT (!_file_path.empty ());

  _ret.clear ();

  if (!_file.is_open ())
    {
      XULOG_WARNING ("load_file2mem: failed load file, skip, " << _file_path);
      return false;
    }

  const std::size_t _size = _file.tellg ();

  _file.seekg (0, std::ios::beg);
  _ret.resize (_size + 1);
  _file.read (UUU_MEM_CAST<char*> (_ret.data ()), _size);
  _ret[_size] = '\0';

  XULOG_TRACE ("load_file2mem: end, " << _file_path);
  return true;
}

}}}      // namespace libs::helpers::files
