#pragma once
/**
\file       expanded-times-helpers.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::statistic::helpers::functors
{
/// Тип для генерации сеанса статистики
class AddOpTime final
{
  public:
  /// Рабочий конструктор
  /// \param[in, out] obj  объект который будет хранит время работы по ключу
  /// \param[in]      key  ключ времени работы
  explicit AddOpTime (
    ExpandedTimes&,
    ExpandedTimes::key_storage_type,
    ExpandedTimes::key_storage_type);

  ~AddOpTime ();
  ///  Функция, помечает текущий измеренный интервал времени как ложный. Т.е. фактически это требование удалить результат работы данного объекта
  void set_skip ();
  // void change_last_name (const std::string& name)

  private:
  ExpandedTimes&                  obj_;          //< ссылка на объект, который хранит всю статитстику
  bool                            skip_;         //< флаг, требование отбросить текущий сеанс работы объекта
  ExpandedTimes::key_storage_type id_set_;       //<
  ExpandedTimes::key_storage_type id_element_;   //<
};

/// Функция сброса статистики времени работы различных алгоритмов из указанного объекта
/// \param[in]      obj    объект со статистикой
/// \param[in, out] logger объект логирования
void dump (ExpandedTimes& obj, ::libs::link::ILink::ptr& logger);

/// Вспомогательный функтор для сброса накопленной статистики у указанного объекта
struct TStatReset final {
  bool
  operator() (ExpandedTimes& obj)
  {
    return obj.clear ();
  }
};

/// Вспомогательный функтор для логирования накопленной статистики у указанного объекта
struct TStatLogger final {
  explicit TStatLogger (::libs::link::ILink::ptr& logger) :
    logger_ (logger)
  {
  }

  ~TStatLogger () = default;

  bool
  operator() (ExpandedTimes& obj)
  {
    dump (obj, logger_);
    return true;
  }

  ::libs::link::ILink::ptr logger_;
};
}   // namespace libs::utility::statistic::helpers::functors
