#pragma once
/**
\file       state-impls-type.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl {
/**
\brief  Перечисление состояний, в которым могут находиться реализации индексации и хранения бинарных данных.
*/
enum struct StateImplsType
{
  run,      //< Хранилище запущено.
  stop      //< Хранилище становлено.
};

inline std::string
to_str (const StateImplsType& _val)
{
  switch (_val)
    {
    case StateImplsType::run:
      return "run";
    case StateImplsType::stop:
      return "stop";
    }

  XULOG_WARNING ("unknown type StateImplsType, " << UUU_ICAST_INT (_val));
  return "x81";
}

}}}}      // namespace modules::uuu_storage::appl::impl
