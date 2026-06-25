#pragma once
/**
\file       generic-thread-func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.12.2016
\project    u3_helpers_lib
*/

namespace libs::helpers::thread::syn
{
using key_storage_type = libs::properties::vers::links::mids::key_storage_type;
}

namespace libs::helpers::thread
{
/// Общий каркас для каждой функции потока в данной системе
/// \tparam     TTOps         тип для уникальных операций в функции потока
/// \param[in]  ops           объект для уникальных операций для которых создается поток
/// \param[in]  indx_thread   индекс потока внутри каждой группы (по типу TTOps), опционально
template< typename TTOps >
void
generic_thread_funct (const syn::key_storage_type& sval, TTOps* ops, const std::uint32_t indx_thread)
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
    catch (boost::exception& excpt)
    {
      modules::mlog::ToLog { sval, ::libs::ievents::props::modules::log::LogLevels::exception }(boost::diagnostic_information (excpt));
    }
    catch (std::exception& excpt)
    {
      modules::mlog::ToLog { sval, ::libs::ievents::props::modules::log::LogLevels::exception }(excpt.what ());
    }
    catch (...)
    {
      modules::mlog::ToLog { sval, ::libs::ievents::props::modules::log::LogLevels::exception }("unknown... exception");
    }
  }
}
}   // namespace libs::helpers::thread
