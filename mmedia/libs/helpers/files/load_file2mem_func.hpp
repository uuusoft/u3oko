#pragma once
/**
\file       load_file2mem_func.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_lib_helpers
*/

namespace libs::helpers::files
{
/// Свободная функция загрузки содержимого файла в память
/// \param[in]  file_path  путь к файлу
/// \param[out] ret        возвращаемый блок памяти с содержимым файла
/// \return     true, если загрузка прошла успешно
bool load_file2mem (const std::string& file_path, ::libs::helpers::mem::IBlockMem::ptr& ret);

/// Свободная функция сохранения блока памяти в файл
/// \param[in]  file_path  путь к файлу
/// \param[out] ret        блок памяти с новым содержимым файла
/// \return     true, если загрузка прошла успешно
bool save_mem2file (const std::string& file_path, const ::libs::helpers::mem::IBlockMem::ptr& ret);

bool is_file_exist (const std::string& file_path);

/// Свободная функция загрузки содержимого файла в память
/// \param[in]  file_path  путь к файлу
/// \param[out] ret        возвращаемый блок памяти с содержимым файла
/// \return     true, если загрузка прошла успешно
template< typename TContainer >
bool
load_file2mem (const std::string& file_path, TContainer& ret)
{
  std::ifstream file (file_path, std::ios::binary | std::ios::in);
  U3_ASSERT (!file_path.empty ());

  ret.clear ();

  if (!file.is_open ())
  {
    U3_XLOG_ERROR ("load_file2mem: failed opening file => skip file load" + TOLOG (file_path));
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
  ret.resize (size);
  file.read (::libs::helpers::casts::reinterpret_cast_helper< char* > (ret.data ()), size);
  // ret[size] = '\0';
  return true;
}

/// Свободная функция получения размера файла
/// \param[in]  path2file  путь к файлу
/// \return     размер файла
std::size_t get_file_size (const std::string& path2file);
}   // namespace libs::helpers::files
