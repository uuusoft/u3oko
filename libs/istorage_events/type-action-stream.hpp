#pragma once
/**
\file       type-action-stream.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.08.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events {
/**
  \brief  Перечисление различных действий в потоке данных.
  */
enum struct TypeActionStream
{
  read         = 0,      //< Через поток возможно только чтение.
  write        = 1,      //< Через поток возможно только запись.
  modification = 2       //< Через поток возможно удаление/чтение/запись.
};

inline std::string
to_str (const TypeActionStream& _val)
{
  switch (_val)
    {
    case TypeActionStream::read:
      return "read";
    case TypeActionStream::write:
      return "write";
    case TypeActionStream::modification:
      return "modification";
    }
  XULOG_WARNING ("unknown TypeActionStream val, " << UUU_ICAST_INT (_val));
  return "xxx";
}

}}      // namespace libs::istorage_events
