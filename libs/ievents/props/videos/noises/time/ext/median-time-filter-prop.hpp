//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       median-time-filter-prop.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace time { namespace ext { namespace consts {

const int min_count_buffs = 3;        //< Минимальное количество буферов во временной области, которое может быть использовано для медианной фильтрации.
const int max_count_buffs = 121;      //< Максимальное количество буферов во временной области, которое может быть использовано для медианной фильтрации.

}}}}}}}}      // namespace libs::ievents::props::videos::noises::time::ext::consts

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace time { namespace ext {
/**
  \brief  Перечисление различных типов сортировок.
  */
enum struct TypeSortAlg
{
  usual    = 0,      //< По умолчанию. Обычно это сортировка вставкой.
  adaptive = 1,      //< Адаптивная, в зависимости от размера выборки. <- рекомендуемый.
  skip     = 2,      //< Пропуск этапа сортировки, т.е. пиксели не обновляются. Используется строго для тестирования времени работы в алгоритме сортировки.
  standart = 3,      //< Встроенная сортировка реализации STL C++.
  insert   = 4       //< Сортировка вставкой. Самый быстрый вариант для последовательностей длиной меньше или равно 11 на ALU.
};
/**
  \brief  Свойства фильтрации во временной области.
  */
class MedianTimeFilterProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (MedianTimeFilterProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MedianTimeFilterProp);
  UUU_DISABLE_ACOPY_TYPE (MedianTimeFilterProp);

  explicit MedianTimeFilterProp (const Acessor& = Acessor (0));

  virtual ~MedianTimeFilterProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/noises/time/ext/median-time-filter-prop";
    return _ret;
  }

  int         count_buffs_;        //< Количество буферов медианной фильтрации.
  int         rang_;               //< Ранг выбираемого числа из отсортированной последовательности. 0 <= rang < count_buffs_
  bool        motion_detect_;      //< Флаг учета движения в кадре при фильтрации
  TypeSortAlg sort_type_;          //< Тип сортировки.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}}      // namespace libs::ievents::props::videos::noises::time::ext

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);
