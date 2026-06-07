#pragma once
/**
\file       buf-allocator.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2016
\project    u3_dbufs
*/

namespace utils::dbufs::allocator
{
/// Реализация по управлению буферами для данных
/// Полное описание функций в суперклассе
class BufAllocator final : public IBufAllocator
{
  public:
  /// Функция возврата одиночки в слабом смысле (только для статически линкуемых модулей) т.к. она определена только в модулей dbufs
  static BufAllocator* instance ();
  //  IBufAllocator
  virtual utils::dbufs::video::IVideoBuf::ptr create (IBufAllocator::size_type size) override;
  virtual std::string                         dump_bufs_state () override;

  private:
  //  internal types
  using bufs_type    = std::list< utils::dbufs::video::IVideoBuf::ptr >;
  using sync_type    = std::mutex;
  using lock_type    = std::scoped_lock< sync_type >;
  using counter_type = std::int64_t;

  BufAllocator ();
  virtual ~BufAllocator ();

  /// Функция освобождения буферов
  void clear ();
  /// Внутренняя реализации без блокировки
  std::string dump_state_int ();

  bufs_type    bufs_;                 //< Список созданных буферов
  sync_type    mtx_;                  //< Примитив для синронизации доступа к реализации
  counter_type counter_alloc_bufs_;   //< Счетчик успешых операций выделения новых буферов
  counter_type counter_reuse_bufs_;   //< Счетчик успешых операций повторного использования буферов
};
}   // namespace utils::dbufs::allocator
