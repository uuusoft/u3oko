//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       destroy-link-type.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link {
/**
\brief  Перечисление различных режимов удаления связи.
*/
enum struct DestroyLinkType
{
  soft  = 0,      //< Мягкое удаление ссылки на связь. Сам обьект может существовать (а может и нет, если общее количество ссылок на него меньше или равно 0).
  force = 1       //< Принудительное удаление объекта, вне зависимости от количества ссылок на него.
};

}}      // namespace libs::link
