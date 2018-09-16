#pragma once
/**
*\file      path_functs.hpp
*\brief     Функции для работы с файлами и директориями
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\date      01.01.2016
\copyright  www.uuusoft.com
\project    uuu_helpers
*/

namespace libs { namespace helpers { namespace files {
/**
  \brief  Функция возращает путь на основе каталога и имени файла
  */
template <
  typename TTString>
TTString
make_path (const TTString& _beg, const TTString& _end)
{
  TTString _res  = _beg;
  TTString _leak = _end;

  if (!_res.empty ())
    {
      const auto _last_char = _res.back ();

      if (('\\' != _last_char) && ('/' != _last_char))
        {
          _res += "/";
        }
    }

  if (!_leak.empty ())
    {
      const auto _first_char = _leak.front ();

      if (('\\' == _first_char) || ('/' == _first_char))
        {
          _leak.erase (0, 1);
        }
    }

  _res += _leak;

  if (!_res.empty ())
    {
      const auto _last_char = _res.back ();

      if (('\\' == _last_char) || ('/' == _last_char))
        {
          _res.erase (_res.length () - 1, 1);
        }
    }

  return _res;
}
/**
  \brief  Функция возращает путь на основе каталога и имени файла
  */
template <>
inline std::wstring
make_path<std::wstring> (const std::wstring& _beg, const std::wstring& _end)
{
  std::wstring _res  = _beg;
  std::wstring _leak = _end;

  if (!_res.empty ())
    {
      const auto _last_char = _res.back ();

      if ((L'\\' != _last_char) && (L'/' != _last_char))
        {
          _res += L"/";
        }
    }

  if (!_leak.empty ())
    {
      const auto _first_char = _leak.front ();

      if ((L'\\' == _first_char) || (L'/' == _first_char))
        {
          _leak.erase (0, 1);
        }
    }

  _res += _leak;

  if (!_res.empty ())
    {
      const auto _last_char = _res.back ();

      if ((L'\\' == _last_char) || (L'/' == _last_char))
        {
          _res.erase (_res.length () - 1, 1);
        }
    }

  return _res;
}
/**
  \brief      Вспомогательная функция для создания короткого пути к объекту файловой системы, требуется в ряде платформ (win32).
  \param[in]  _path путь к создаваемой директории
  \return     короткий путь к объекту или исходный если преобразование не требуется.
  */
std::string make_short_path (const std::string& _path);
/**
  \brief      Функция создания директории.
  \param[in]  _path путь к создаваемой директории.
  \return     true, при успехе.
  */
bool create_folder (const std::string& _path);
/**
  \brief      Функция удаления директории.
  \param[in]  _path путь к удаляемой директории.
  */
void delete_folder (const std::string& _path);
/**
  \brief      Функция проверки существования директории.
  \param[in]  _path путь потенциальной директории.
  \return     true, если директория существует.
  */
bool is_folder (const std::string& _path);

}}}      // namespace libs::helpers::files
