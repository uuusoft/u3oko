#pragma once
/**
\file       path_funcs.hpp
\brief      Функции для работы с файлами и директориями
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_helpers_lib
*/

namespace libs::utility::files::consts
{
inline constexpr char special_convert_path_symbol = '#';
}

namespace libs::utility::files
{
/// Функция возвращает путь на основе каталога и имени файла
template< typename TTString >
TTString
make_path (const TTString& beg, const TTString& end)
{
  TTString res  = beg;
  TTString leak = end;

  if (!res.empty ())
  {
    const auto last_char = res.back ();

    if (('\\' != last_char) && ('/' != last_char))
    {
      res += "/";
    }
  }

  if (!leak.empty ())
  {
    const auto first_char = leak.front ();

    if (('\\' == first_char) || ('/' == first_char))
    {
      leak.erase (0, 1);
    }
  }

  res += leak;

  if (!res.empty ())
  {
    const auto last_char = res.back ();

    if (('\\' == last_char) || ('/' == last_char))
    {
      res.erase (res.length () - 1, 1);
    }
  }

  return res;
}

/// Функция возращает путь на основе каталога и имени файла
template<>
inline std::wstring
make_path< std::wstring > (const std::wstring& beg, const std::wstring& end)
{
  std::wstring res  = beg;
  std::wstring leak = end;

  if (!res.empty ())
  {
    const auto last_char = res.back ();

    if ((L'\\' != last_char) && (L'/' != last_char))
    {
      res += L"/";
    }
  }

  if (!leak.empty ())
  {
    const auto first_char = leak.front ();

    if ((L'\\' == first_char) || (L'/' == first_char))
    {
      leak.erase (0, 1);
    }
  }

  res += leak;

  if (!res.empty ())
  {
    const auto last_char = res.back ();

    if ((L'\\' == last_char) || (L'/' == last_char))
    {
      res.erase (res.length () - 1, 1);
    }
  }

  return res;
}

/// Вспомогательная функция для создания короткого пути к объекту файловой системы, требуется в ряде платформ (win32)
/// \param[in]  path путь к создаваемой директории
/// \return     короткий путь к объекту или исходный если преобразование не требуется
std::string make_short_path (const std::string& path);

/// Функция создания директории
/// \param[in]  path путь к создаваемой директории
/// \return     true, при успехе
bool create_folder (const std::string& path);

/// Функция удаления директории
/// \param[in]  path путь к удаляемой директории
void delete_folder (const std::string& path);

/// Функция проверки существования директории
/// \param[in]  path путь потенциальной директории
/// \return     true, если директория существует
bool is_folder (const std::string& path);

std::string get_name_from_path (const std::string& path);
std::string prepare_for_file_name (const std::string_view& src);
}   // namespace libs::utility::files
