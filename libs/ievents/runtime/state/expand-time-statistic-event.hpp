//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       expand-time-statistic-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      Объявление типа для хранения и передачи статистики по затраченному времени.
*/

namespace libs { namespace ievents { namespace runtime { namespace state {
//  syn
using ::libs::helpers::statistic::ExpandedTimeStatistic;
/**
\brief  Тип источника времени работы.
*/
enum struct TypeStatisticSource
{
  alg      = 0,      //< Источником данных является конкретный алгогитм.
  path_obj = 1       //< Источником данных является объект пути.
};
/**
\brief  Тип действия, которое надо произвести над источником.
*/
enum struct TypeStatisticAction
{
  get   = 0,      //< Получить статистику источника.
  reset = 1       //< Сбросить статистику источника.
};
/**
\brief  Событие со статистикой по затраченному времени по агентам.
 */
class ExpandTimeStatisticEvent : public RuntimeEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ExpandTimeStatisticEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ExpandTimeStatisticEvent);
  UUU_DISABLE_ACOPY_TYPE (ExpandTimeStatisticEvent);

  explicit ExpandTimeStatisticEvent (const Acessor& = Acessor (0), const ExpandedTimeStatistic::infos_type& _infos = ExpandedTimeStatistic::infos_type (), const TypeStatisticSource& _source = TypeStatisticSource::alg);

  virtual ~ExpandTimeStatisticEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/runtime/state/expand-time-statistic-event";
    return _ret;
  }

  const ExpandedTimeStatistic::infos_type& get_stat () const;

  void set_stat (const ExpandedTimeStatistic::infos_type& _infos);

  const TypeStatisticSource& get_source () const;

  void set_source (const TypeStatisticSource& _source);

  const TypeStatisticAction& get_action () const;

  void set_action (const TypeStatisticAction& _source);


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent);

  TypeStatisticAction               action_;      //< Тип действия с данными источника.
  TypeStatisticSource               source_;      //< Тип источника данных (по алгоритмам/по объектам пути/etc).
  ExpandedTimeStatistic::infos_type infos_;       //< Собственно список с затраченном временем по агентам.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;
};

}}}}      // namespace libs::ievents::runtime::state

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::state::ExpandTimeStatisticEvent);
