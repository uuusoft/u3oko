#pragma once
/**
\file       expanded-times.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::statistic::helpers::functors
{
//  forward
class AddOpTime;
}   // namespace libs::helpers::statistic::helpers::functors

namespace libs::helpers::statistic
{
/// Тип для сбора статистики затраченного времени
class ExpandedTimes final
{
  private:
  friend class libs::helpers::statistic::helpers::functors::AddOpTime;

  public:
  //  ext types
  using key_storage_type = std::string;
  using storage_type     = std::unordered_map< key_storage_type, ExpandedTime >;
  using storages_type    = std::unordered_map< key_storage_type, storage_type >;

  ExpandedTimes () = default;
  ~ExpandedTimes ();

  ExpandedTimes (const ExpandedTimes& src)            = delete;
  ExpandedTimes& operator= (const ExpandedTimes& src) = delete;

  /// Основная рабочая функция со статистикой
  void visit_with (const std::function< void (const storages_type& vals) >& func);

  /// Функция сброса накопленой информации Например, для нового цикла измерений
  bool clear ();

  private:
  //  internal typess
  using ops_storage_type      = std::list< std::pair< std::string, std::string > >;
  using time_ops_storage_type = std::list< ::libs::helpers::statistic::time_type >;

  /// Функция начала подсчета времени работы
  void begin (const key_storage_type& id_set, const key_storage_type& id_element);

  /// Функция завершения подсчета времени работы
  bool end ();

  /// Функция завершения с отменой текущего результата измерения времени работы
  void end_skip ();

  /// Функция меняет идентификатор последнего измерения времени
  // void change_last_name (const key_storage_type& id_set, const key_storage_type& id_element);
  ExpandedTimes::storages_type::iterator find_time (const key_storage_type& id_set);

  storages_type         vals_;    //< cеансы по текстовым ключам
  ops_storage_type      ops_;     //< cписок выполняемых операций, т.к операции могут быть вложенными
  time_ops_storage_type times_;   //< cписок времен выполняемых операций
};

void merge (const ExpandedTimes::storage_type&, ExpandedTimes::storage_type&);
void merge (const ExpandedTimes::storages_type&, ExpandedTimes::storages_type&);
}   // namespace libs::helpers::statistic
