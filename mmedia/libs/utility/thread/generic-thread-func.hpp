#pragma once
/**
\file       generic-thread-func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.12.2016
*/

namespace libs::utility::thread::syn
{
using key_storage_type = libs::properties::vers::links::mids::key_storage_type;
}

namespace libs::utility::thread
{
/// Общий каркас для каждой функции потока в данной системе
/// \tparam     TTOps         тип для уникальных операций в функции потока
/// \param[in]  loglink       идентификатор связи для логирования
/// \param[in]  obj           объект для уникальных операций для которых создается поток
/// \param[in]  thread_indx   индекс потока внутри каждой группы (по типу TTOps), опционально
template< typename TTOps >
void
generic_thread_func (
  const syn::key_storage_type& loglink,
  TTOps*                       obj,
  const std::uint32_t          thread_indx)
{
  // U3_CALL_TRACE_DBG;
  using ttops_func_type = void (TTOps::*) (std::uint32_t thread_indx);

  set_thread_priority (std::this_thread::get_id (), Priorities::normal);

  const ttops_func_type funcs[2] = {
    &TTOps::thread_func_impl,
    &TTOps::thread_postfunc_impl
  };

  for (const auto& func : funcs)
  {
    try
    {
      (obj->*func) (thread_indx);
    }
    catch (boost::exception& excpt)
    {
      modules::mlog::ToLog { loglink, ::libs::events_base::props::modules::log::LogLevels::exception }(boost::diagnostic_information (excpt));
    }
    catch (std::exception& excpt)
    {
      modules::mlog::ToLog { loglink, ::libs::events_base::props::modules::log::LogLevels::exception }(excpt.what ());
    }
    catch (...)
    {
      modules::mlog::ToLog { loglink, ::libs::events_base::props::modules::log::LogLevels::exception }("generic_thread_func::exception ...");
    }
  }
}
}   // namespace libs::utility::thread
