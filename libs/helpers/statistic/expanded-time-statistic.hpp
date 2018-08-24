#pragma once
/**
\file       expanded-time-statistic.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace statistic { namespace helpers { namespace functors {
//  forward
class AddTimeStatistic;
}}}}}      // namespace libs::helpers::statistic::helpers::functors

namespace libs { namespace helpers { namespace statistic {
/**
  \brief  Тип для сбора статистики затраченного времени.
  */
class ExpandedTimeStatistic
{
  friend class libs::helpers::statistic::helpers::functors::AddTimeStatistic;

  public:
  //  ext types
  using infos_type = std::list<std::string>;
  /// Конструктор по умолчанию.
  ExpandedTimeStatistic ();
  /// Деструктор.
  ~ExpandedTimeStatistic ();

  ExpandedTimeStatistic (const ExpandedTimeStatistic& _src) = delete;
  ExpandedTimeStatistic& operator= (const ExpandedTimeStatistic& _src) = delete;
  /**
    \brief      Функция получения накопленной информации.
    \param[out] _info возврашаемая информация.
    */
  void get (infos_type& _info);
  /**
    \brief  Функция сброса накопленой информации. Например, для нового цикла измерений.
    \return true, при успехе.
    */
  bool clear ();


  private:
  //  int types
  using storage_type      = std::map<std::string, ElementStatInfo>;
  using storage_ops_type  = std::list<std::string>;
  using storage_time_type = std::list<time_type>;
  /**
    \brief      Функция подсчета времени работы.
    \param[in]  _name ключ сеанса.
    */
  void begin (const std::string& _name);
  /**
    \brief    Функция завершения времени работы.
    \return   true, при успехе.
    */
  bool end ();
  /**
    \brief    Функция завершения с отменой текущего результата измерения времени работы.
    */
  void end_skip ();
  /**
     * \brief Функция меняет идентификатор последнего измерения времени.
     */
  void change_last_name (const std::string& _name);

  storage_type      vals_;       //< Сеансы статистик по текстовым ключам.
  storage_ops_type  ops_;        //< Список выполняемых операций. Т.к. операции могут быть вложенными.
  storage_time_type times_;      //< Список времен выполняемых операций.
};

}}}      // namespace libs::helpers::statistic
