#pragma once
/**
\file       sqlite-call-helper-functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.09.2018
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace modules { namespace uuu_events { namespace appl {
/**
\brief  ???
*/
inline void
call_exec (sqlite3* _pbase, const std::string& _cmd, const std::string& _info)
{
  UASSERT (!_cmd.empty ());
  UASSERT (_pbase);

  char* _error_msg = nullptr;
  if (SQLITE_OK == sqlite3_exec (_pbase, _cmd.c_str (), nullptr, nullptr, &_error_msg))
    {
      return;
    }

  XULOG_ERROR ("failed " << _info << ", " << _error_msg);
  sqlite3_free (_error_msg);
  _error_msg = nullptr;
  return;
}
/**
\brief  ???
*/
inline std::string
to_sql_str (const std::string& _val)
{
  return "'" + _val + "'";
}

}}}      // namespace modules::uuu_events::appl
