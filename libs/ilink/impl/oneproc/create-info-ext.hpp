//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       create-info-ext.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace oneproc {
/**
\brief  Структура для расширения полей оригинальной.
*/
struct CreateInfoExt : public CreateInfo
{
  explicit CreateInfoExt () :
    server_side_ (false)
  {}

  CreateInfoExt&
  operator= (const CreateInfo& _src)
  {
    static_cast<CreateInfo&> (*this) = _src;
    return *this;
  }

  bool server_side_;      //< Флаг стороны канала.
};
/**
\brief  ????
*/
inline std::string
to_str (const CreateInfoExt& _val)
{
  std::string _res;
  std::string _int_res = to_str (static_cast<const CreateInfo&> (_val));
  _res += "CreateInfoExt[" + ::to_str (_val.server_side_) + " " + _int_res + "]";
  return _res;
}

}}}}      // namespace libs::ilink::impl::oneproc
