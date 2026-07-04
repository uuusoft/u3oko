#pragma once
/**
\file       median-space-filter-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::noises::space::ext::consts
{
inline constexpr std::int32_t min_size_core = 3;                                                               //< Минимальное количество буферов во временной области, которое может быть использовано для медианной фильтрации
inline constexpr std::int32_t max_size_core = ::libs::optim::s16bit::conv::consts::bufs::max_size_core_conv;   //< Максимальное количество буферов во временной области, которое может быть использовано для медианной фильтрации
inline constexpr std::int32_t min_dim_core  = 1;                                                               //< Минимальная размерность ядра
inline constexpr std::int32_t max_dim_core  = 2;                                                               //< Макимальная размерность ядра
}   // namespace libs::events_base::props::videos::noises::space::ext::consts

namespace libs::events_base::props::videos::noises::space::ext
{
/// Перечисление различных типов сортировок
enum class Sortings : std::uint32_t
{
  usual    = 0x00,   //< По умолчанию, фиксированный выбор, не зависит от размера выборки
  adaptive = 0x01,   //< Адаптивная, в зависимости от размера выборки. <- рекомендуемый тип
  skip     = 0x02,   //< Пропуск этапа сортировки (Для тестирования)
  standart = 0x03,   //< Встроенная сортировка в стандарт C++
  insert   = 0x04,   //< Сортировка вставкой
  count    = 0x05,   //< Cортировка подсчетом (самая быстрая практически всегда, кроме малых окрестностей)
  rand     = 0x06,   //< Выбор случайного значения из окрестности (не фильтрация, не сортировка, для теста)
  unknown  = 0xFF    //< Не определенно для общности
};

const std::string& to_string (const Sortings& val);
void               tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Sortings& src);
Sortings           tag_invoke (::boost::json::value_to_tag< Sortings >, const ::boost::json::value& jvs);

class MedianSpaceFilterProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (MedianSpaceFilterProp)
  U3_ADD_MAKE_SHARED_THIS (MedianSpaceFilterProp)
  U3_ADD_DELETE_MOVE_COPY (MedianSpaceFilterProp)

  explicit MedianSpaceFilterProp (const Acessor& = Acessor (0));
  virtual ~MedianSpaceFilterProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/props/videos/noises/space/ext/median-space-filter-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  std::int32_t      size_core_      = 5;                                   //< Размер ядра медианной фильтрации
  std::int32_t      dim_core_       = 2;                                   //< Размерность ядра фильтрации [1.2]
  std::int32_t      rang_           = 2;                                   //< Ранг выбираемого числа из отсортированной последовательности 0 <= rang < count_core_ ^ dim_core_
  Sortings          sort_type_      = Sortings::usual;                     //< Тип сортировки
  std::int32_t      size_cond_core_ = 0;                                   //< Размер ядра фильтрации, если есть признак в буфере условий. 0 - фильтрации не производится
  std::int32_t      cond_rang_      = 0;                                   //< Ранг числа, если есть буфер условий
  syn::off_buf_type indx_cond_buf_  = syn::offs::space_noise_filter_res;   //< Опицональный индекс буфера условий. Буфер условий определяет размер ядра фильтрации (и вообще саму возможность фильтрации)
  bool              use_cond_buf_   = false;                               //< Флаг учета буфера условий при фильтрации

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
  virtual void self_correct_int () override;
};
}   // namespace libs::events_base::props::videos::noises::space::ext

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::noises::space::ext::MedianSpaceFilterProp);
