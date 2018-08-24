#pragma once
/**
\file       functors_with_statistic.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace statistic { namespace helpers { namespace functors {
/**
  \brief  Тип для генерации сеанса статистики. 
  */
class AddTimeStatistic
{
  public:
  /**
    \brief          Рабочий конструктор.
    \param[in, out] _obj  объект который будет хранит время работы по ключу.
    \param[in]      _key  ключ времени работы.
    */
  explicit AddTimeStatistic (ExpandedTimeStatistic& _obj, const std::string& _key) :
    obj_ (_obj),
    skip_ (false)
  {
    obj_.begin (_key);
  }


  ~AddTimeStatistic ()
  {
    if (skip_)
      {
        obj_.end_skip ();
      }
    else
      {
        obj_.end ();
      }
  }
  /**
    \brief  Функция, помечает текущий измеренный интервал времени как ложный. 
            Т.е. фактически это требование удалить результат работы данного объекта.
    */
  void
  set_skip ()
  {
    skip_ = true;
    return;
  }
  /**
     * \brief
     */
  void
  change_name (const std::string& _name)
  {
    obj_.change_last_name (_name);
    return;
  }


  private:
  ExpandedTimeStatistic& obj_;       //< Ссылка на объект, который хранит всю статитстику.
  bool                   skip_;      //< Флаг, требование отбросить текущий сеанс работы объекта.
};
/**
  \brief          Функция сброса статистики времени работы различных алгоритмов из указанного объекта.
  \param[in]      _obj    объект со статистикой.
  \param[in, out] _logger объект логирования.
  */
inline void
dump (ExpandedTimeStatistic& _obj, ::libs::link::ILink::ptr& _logger)
{
  ExpandedTimeStatistic::infos_type _infos;
  _obj.get (_infos);
  for (const std::string& _info : _infos)
    {
      MSG2LOGGER (_logger, _info, "xxx");
    }
  return;
}
/**
  \brief  Вспомогательный функтор для сброса накопленной статистики у указанного объекта.
  */
struct TStatReset
{
  bool
  operator() (ExpandedTimeStatistic& _obj)
  {
    return _obj.clear ();
  }
};
/**
  \brief  Вспомогательный функтор для логирования накопленной статистики у указанного объекта.
  */
struct TStatLogger
{
  /**
    \brief
    */
  explicit TStatLogger (::libs::link::ILink::ptr& _logger) :
    logger_ (_logger)
  {}


  ~TStatLogger ()
  {}


  bool
  operator() (ExpandedTimeStatistic& _obj)
  {
    dump (_obj, logger_);

    return true;
  }

  ::libs::link::ILink::ptr logger_;      //< ???
};

}}}}}      // namespace libs::helpers::statistic::helpers::functors
