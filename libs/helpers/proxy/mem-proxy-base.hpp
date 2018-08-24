#pragma once
/**
\file       mem-proxy-base.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Интерфейсный файл для типа MemProxyBase
*/

namespace libs { namespace helpers { namespace proxy {
/**
  \brief  Базовый скрытый класс для облегчения реализации гарантированного существования объекта в единственном экземпляре внутри одного процесса (не системы в целом).
          Вне зависимости от количества разделяемым модулей и прочего. Опирается на именновую разделяемую (только внутри процесса) память.
  */
class MemProxyBase
{
  protected:
  //  int types
  using shared_mem_type     = boost::interprocess::managed_shared_memory;
  using shared_mem_ptr_type = std::unique_ptr<shared_mem_type>;
  /**
    \brief      Конструктор.
    \param[in]  _prefix   дополнительный префикс к имени памяти, должен быть уникальным для каждого типа, унаследовавшего данный класс.
    \param[in]  _max_size требуемый размер памяти.
    */
  MemProxyBase (const std::string& _prefix, std::size_t _max_size);

  ~MemProxyBase ();

  MemProxyBase (const MemProxyBase& _src) = delete;
  MemProxyBase& operator= (const MemProxyBase& _src) = delete;

  shared_mem_ptr_type pshm_;      //< Разделяемая память процесса.
  std::string         mid_;       //< Идентификатор памяти.
  std::string         cid_;       //< Идентификатор объекта в памяти.
};

}}}      // namespace libs::helpers::proxy
