//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       median-space-filter-prop.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace space { namespace ext { namespace consts {

const int min_size_core = 3;                                                                   //< Минимальное количество буферов во временной области, которое может быть использовано для медианной фильтрации.
const int max_size_core = ::libs::optim::s16bit::conv::consts::buffs::max_size_core_conv;      //< Максимальное количество буферов во временной области, которое может быть использовано для медианной фильтрации.
const int min_dim_core  = 1;                                                                   //< Минимальная размерность ядра.
const int max_dim_core  = 2;                                                                   //< Макимальная размерность ядра.

}}}}}}}}      // namespace libs::ievents::props::videos::noises::space::ext::consts

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace space { namespace ext {
/**
  \brief  Перечисление различных типов сортировок.
  */
enum struct TypeSortAlg
{
  usual    = 0,      //< По умолчанию, фиксированный выбор, не зависит от размера выборки.
  adaptive = 1,      //< Адаптивная, в зависимости от размера выборки. <- рекомендуемый тип.
  skip     = 2,      //< Пропуск этапа сортировки, т.е. пиксели не обновляются. Для тестирования.
  standart = 3,      //< Встроенная сортировка в стандарт C++.
  insert   = 4,      //< Сортировка вставкой.
  count    = 5,      //< Cортировка подсчетом. Самая быстрая практически всегда, кроме малых окрестностей.
  rand     = 6       //< Выбор случайного значения из окрестности. Не фильтрация, не сортировка, для теста.
};
/**
  \brief  Свойства фильтрации во временной области.
  */
class MedianSpaceFilterProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (MedianSpaceFilterProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MedianSpaceFilterProp);
  UUU_DISABLE_ACOPY_TYPE (MedianSpaceFilterProp);

  explicit MedianSpaceFilterProp (const Acessor& = Acessor (0));

  virtual ~MedianSpaceFilterProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/videos/noises/space/ext/median-space-filter-prop";
    return _ret;
  }

  void correct ();

  int         size_core_;           //< Размер ядра медианной фильтрации.
  int         dim_core_;            //< Размерность ядра фильтрации [1..2]
  int         rang_;                //< Ранг выбираемого числа из отсортированной последовательности. 0 <= rang < count_core_ ^ dim_core_
  TypeSortAlg sort_type_;           //< Тип сортировки.
  int         size_cond_core_;      //< Размер ядра фильтрации, если есть признак в буфере условий. 0 - фильтрации не производится.
  int         cond_rang_;           //< Ранг числа, если есть буфер условий.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}}      // namespace libs::ievents::props::videos::noises::space::ext

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp);
