#pragma once
/**
\file       expanded-time.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
*/

namespace libs::helpers::statistic
{
/// Структура для времен одного элемента статистики
class ExpandedTime final
{
  public:
  ExpandedTime () = default;
  virtual ~ExpandedTime ();

  duration_type min_   = count_time_type (0);   //< минимальное время
  duration_type max_   = count_time_type (0);   //< максимальное время
  duration_type sum_   = count_time_type (0);   //< сумма всех времен
  std::uint64_t count_ = 0;                     //< количество элементов

  ExpandedTime& operator+= (const ExpandedTime& val);

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void         tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jsn, const ExpandedTime& src);
ExpandedTime tag_invoke (::boost::json::value_to_tag< ExpandedTime >, const ::boost::json::value& jsn);
}   // namespace libs::helpers::statistic

BOOST_CLASS_EXPORT_KEY (::libs::helpers::statistic::ExpandedTime);
