#pragma once
/**
\file       buf-allocator.hpp
\author     Erashov Anton erashov2026@proton.me
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
  U3_ADD_POINTERS_TO_SELF (BufAllocator)

  /// Функция возврата одиночки в слабом смысле (только для статически линкуемых модулей) т.к. она определена только в модулей dbufs
  static IBufAllocator::raw_ptr instance ();

  //  IBufAllocator
  virtual auto create (size_buf_type) -> utils::dbufs::video::IVideoBuf::ptr override;
  virtual auto dump_bufs_state () -> std::string override;

  private:
  //  internal types
  using bufs_type    = std::list< utils::dbufs::video::IVideoBuf::ptr >;
  using sync_type    = std::mutex;
  using lock_type    = std::scoped_lock< sync_type >;
  using counter_type = std::int64_t;

  BufAllocator () = default;
  virtual ~BufAllocator ();

  /// Функция освобождения буферов
  void clear ();
  /// Внутренняя реализации без блокировки
  std::string dump_state_int ();

  bufs_type    bufs_;                     //< Список созданных буферов
  sync_type    mtx_;                      //< Примитив для синхронизации доступа к реализации
  counter_type counter_alloc_bufs_ = 0;   //< Счетчик успешых операций выделения новых буферов debug
  counter_type counter_reuse_bufs_ = 0;   //< Счетчик успешых операций повторного использования буферов debug
};
}   // namespace utils::dbufs::allocator
