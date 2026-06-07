#pragma once
/**
\file       file-ext2mime-func.hpp
\date       15.02.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_http_module
*/

namespace modules::uuu_http::appl::helpers
{
inline const std::string&
file_ext2mime (const std::string& ext)
{
  // source https://mimetype.io/all-types
  static const std::unordered_map< std::string, const std::string > ext2http_type = {
    { ".html", "text/html" },
    { ".htm", "text/html" },
    { ".js", "application/javascript" },
    { ".txt", "text/plain" },
    { ".mp4", "video/mp4" },
    { ".mp4v", "video/mp4" },
    { ".mpg4", "video/mp4" },
    { ".css", "text/css" },
    { ".jpe", "image/jpeg" },
    { ".jpeg", "image/jpeg" },
    { ".jpg", "image/jpeg" },
    { ".pjpg", "image/jpeg" },
    { ".jfif", "image/jpeg" },
    { ".jfif-tbnl", "image/jpeg" },
    { ".png", "image/png" },
    { ".php", "text/html" },
    { ".json", "application/json" },
    { ".xml", "application/xml" },
    { ".swf", "application/x-shockwave-flash" },
    { ".flv", "video/x-flv" },
    { ".gif", "image/gif" },
    { ".bmp", "image/bmp" },
    { ".ico", "image/vnd.microsoft.icon" },
    { ".tiff", "image/tiff" },
    { ".tif", "image/tiff" },
    { ".svg", "image/svg+xml" },
    { ".svgz", "image/svg+xml" },
    { "", "application/text" }
  };

  auto finger = ext2http_type.find (ext);
  if (ext2http_type.end () == finger)
  {
    finger = ext2http_type.find ("");
  }
  return finger->second;
}
}   // namespace modules::uuu_http::appl::helpers
