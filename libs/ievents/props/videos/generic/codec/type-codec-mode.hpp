//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-codec-mode.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace codec {
/**
\brief  Тип для режимов кодека.
*/
enum struct TypeCodecMode
{
  coder   = 0,      //< Режим кодера.
  decoder = 1       //< Режим декодер.
};

}}}}}}      // namespace libs::ievents::props::videos::generics::codec
