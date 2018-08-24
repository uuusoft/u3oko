#pragma once
/**
\file       buff-allocator.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление реализации интерфейся для выделения буферов под видео/аудио данные.
*/

namespace utils { namespace dbuffs { namespace allocator {
//  syn
using ::utils::mem_functs::impl::BlockMemAllocatorProxy;
/**
  \brief  Реализация по управлению буферами для данных. Полное описание функций в суперклассе.
  */
class BuffAllocator : public IBuffAllocator
{
  public:
  /**
    \brief  Функция возврата одиночки в слабом смысле (только для статически линкуемых модулей).
            Т.к. она определена только в модулей dbuffs.
    */
  static BuffAllocator* instance ();
  //  IBuffAllocator
  virtual utils::dbuffs::video::IVideoBuff::ptr get () override;
  virtual void                                  dump_state () override;


  private:
  //  int type
  using buffs_type   = std::list<utils::dbuffs::video::IVideoBuff::ptr>;
  using sync_type    = std::mutex;
  using guard_type   = std::lock_guard<sync_type>;
  using counter_type = signed long long;
  /// Закрытый конструктор.
  BuffAllocator ();
  /// Закрытый деструктор.
  virtual ~BuffAllocator ();
  /// Функция освобождения буферов.
  void clear ();
  /// Внутренняя реализации без блокировки.
  void dump_state_int ();

  buffs_type   buffs_;                      //< Список созданных буферов.
  sync_type    mtx_;                        //< Примитив для синронизации доступа к реализации.
  counter_type counter_alloc_buffers_;      //< Счетчик успешых операций выделения новых буферов.
  counter_type counter_reuse_buffers_;      //< Счетчик успешых операций повторного использования буферов.
};

}}}      // namespace utils::dbuffs::allocator
