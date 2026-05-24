#pragma once
/**
\file       generic-thread-func.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.12.2016
\project    u3_helpers_lib
*/

namespace libs::helpers::thread
{
/// Общий каркас для каждой функции потока в данной системе
/// \tparam     TTOps         тип для уникальных операций в функции потока
/// \tparam     TTLinkVal     тип для логирования в функции потока
/// \param[in]  ops           объект для уникальных операций для которых создается поток
/// \param[in]  indx_thread   индекс потока внутри каждой группы (по типу TTOps), опционально
template< typename TTOps, libs::properties::vers::links::mids::key_storage_type TTLinkVal >
void
generic_thread_funct (TTOps* ops, const std::uint32_t indx_thread)
{
  ::libs::helpers::thread::set_thread_priority (std::this_thread::get_id (), ::libs::helpers::thread::Priorities::normal);

  using ttops_func_ptr_type = void (TTOps::*) (std::uint32_t indx_thread);

  const ttops_func_ptr_type funcs[2] = {
    &TTOps::thread_func_impl,
    &TTOps::thread_postfunc_impl
  };

  for (auto& func : funcs)
  {
    try
    {
      (ops->*func) (indx_thread);
    }
    catch (boost::exception& e)
    {
      modules::uuu_log::ToLog { TTLinkVal, ::libs::ievents::props::modules::log::LogLevels::exception }(boost::diagnostic_information (e));
    }
    catch (std::exception& e)
    {
      modules::uuu_log::ToLog { TTLinkVal, ::libs::ievents::props::modules::log::LogLevels::exception }(e.what ());
    }
    catch (...)
    {
      modules::uuu_log::ToLog { TTLinkVal, ::libs::ievents::props::modules::log::LogLevels::exception }("unknown... exception");
    }
  }
}
}   // namespace libs::helpers::thread
