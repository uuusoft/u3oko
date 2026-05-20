#pragma once
/**
\file       http2json-helper-funcs.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_http_module
*/

namespace modules::uuu_http::appl::helpers
{
/// Функция преобразования http запроса в json формат для boost::property_tree
/// \param[in]  http строска запроса
/// \param[out] json выходный формат
inline void
http2json (const std::string& http, std::string& json)
{
  std::size_t beg_pos    = 0;
  std::size_t count_tags = 0;

  json.clear ();
  json.reserve (http.length () * 2);

  json += "{";

  do
  {
    const auto beg_equal = http.find ('=', beg_pos);
    const auto beg_amper = http.find ('&', beg_equal);

    U3_CHECK (std::string::npos != beg_equal, "convert http 2 json, equal not found");

    json += count_tags ? ", " : "";
    json += "\"";
    json += http.substr (beg_pos, beg_equal - beg_pos);
    json += "\": ";

    const std::size_t count_val = std::string::npos == beg_amper ? http.length () - beg_equal - 1 : beg_amper - beg_equal - 1;

    json += "\"";
    json += http.substr (beg_equal + 1, count_val);
    json += "\"";

    if ((std::string::npos == beg_amper) || (beg_amper + 1 == http.length ()))
    {
      break;
    }

    beg_pos = beg_amper + 1;
    ++count_tags;
  } while (true);

  json += "}";
}


inline std::string
http2json (const std::string& http)
{
  std::string ret;
  http2json (http, ret);
  return ret;
}
}   // namespace modules::uuu_http::appl::helpers
