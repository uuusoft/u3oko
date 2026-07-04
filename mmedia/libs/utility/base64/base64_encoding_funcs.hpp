/**
\file       base64_encoding_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2018
\project    u3_helpers_lib
*/

namespace libs::utility::base64
{
/// https://stackoverflowcom/questions/180947/base64-decode-snippet-in-c
std::string base64_encode (const std::uint8_t* buf, std::uint64_t bufLen);
/// https://stackoverflowcom/questions/180947/base64-decode-snippet-in-c
std::string base64_encode (const std::string& src);
/// https://stackoverflowcom/questions/180947/base64-decode-snippet-in-c
std::vector< std::uint8_t > buf_base64_decode (const std::string& src);
/// https://stackoverflowcom/questions/180947/base64-decode-snippet-in-c
std::string base64_decode (const std::string& src);
}   // namespace libs::utility::base64
