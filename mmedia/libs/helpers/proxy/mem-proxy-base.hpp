#pragma once
/**
\file       mem-proxy-base.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
\brief      Интерфейсный файл для типа MemProxyBase
*/

namespace libs::helpers::proxy
{
/// Базовый скрытый класс для облегчения реализации гарантированного существования объекта в единственном экземпляре внутри одного процесса (не системы в целом)
/// Вне зависимости от количества разделяемым модулей и прочего
/// Опирается на именновую разделяемую (только внутри процесса) память
class MemProxyBase
{
  protected:
  //  internal typess
  using shared_mem_type     = boost::interprocess::managed_shared_memory;
  using shared_mem_ptr_type = std::unique_ptr< shared_mem_type >;
  /// Конструктор
  /// \param[in]  prefix   дополнительный префикс к имени памяти, должен быть уникальным для каждого типа, унаследовавшего данный класс
  /// \param[in]  max_size требуемый размер памяти
  MemProxyBase (const std::string&, std::size_t);
  virtual ~MemProxyBase ();

  MemProxyBase (const MemProxyBase&)            = delete;
  MemProxyBase& operator= (const MemProxyBase&) = delete;

  shared_mem_ptr_type pshm_;   //< Разделяемая память процесса
  std::string         mid_;    //< Идентификатор памяти
  std::string         cid_;    //< Идентификатор объекта в памяти
};
}   // namespace libs::helpers::proxy
