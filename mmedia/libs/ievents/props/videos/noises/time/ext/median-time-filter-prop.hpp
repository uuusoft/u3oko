#pragma once
/**
\file       median-time-filter-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::noises::time::ext::consts
{
constexpr std::uint32_t min_count_bufs = 3;    //< Минимальное количество буферов во временной области, которое может быть использовано для медианной фильтрации
constexpr std::uint32_t max_count_bufs = 31;   //< Максимальное количество буферов во временной области, которое может быть использовано для медианной фильтрации
}   // namespace libs::ievents::props::videos::noises::time::ext::consts

namespace libs::ievents::props::videos::noises::time::ext
{
/// Перечисление различных типов сортировок
enum class Sortings : std::uint32_t
{
  usual             = 0x00,   //< По умолчанию, обычно это сортировка вставкой
  adaptive          = 0x01,   //< Адаптивная, в зависимости от размера выборки <- рекомендуемый
  skip              = 0x02,   //< Пропуск этапа сортировки, т.е. пиксели не обновляются. Используется строго для тестирования времени работы в алгоритме сортировки
  standart          = 0x03,   //< Встроенная сортировка реализации STL C++
  insert            = 0x04,   //< Сортировка вставкой. Самый быстрый вариант для последовательностей длиной меньше или равно 11 на ALU
  inplace_3_element = 0x70,   //< Сортировка обменом на месте для последовательностей из трех элементов
  unknown           = 0xFF    //< Не определенно для общности
};

void     tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Sortings& src);
Sortings tag_invoke (::boost::json::value_to_tag< Sortings >, const ::boost::json::value& jvs);

/// Свойства фильтрации во временной области
class MedianTimeFilterProp final : virtual public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (MedianTimeFilterProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MedianTimeFilterProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (MedianTimeFilterProp)

  explicit MedianTimeFilterProp (const Acessor& = Acessor (0));
  virtual ~MedianTimeFilterProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/videos/noises/time/ext/median-time-filter-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  std::uint32_t     count_bufs_    = 3;                                                    //< Количество буферов медианной фильтрации
  std::uint32_t     rang_          = 2;                                                    //< Ранг выбираемого числа из отсортированной последовательности 0 <= rang < count_bufs_
  bool              motion_detect_ = false;                                                //< Флаг учета движения в кадре при фильтрации
  Sortings          sort_type_     = Sortings::usual;                                      //< Тип сортировки
  syn::off_buf_type indx_diff_buf_ = utils::dbufs::video::consts::offs::move_detect_res;   //<
  bool              use_diff_buf_  = false;                                                //<

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // overrides ievents::Event
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
  virtual void self_correct_int () override;
};
}   // namespace libs::ievents::props::videos::noises::time::ext

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);
