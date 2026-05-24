#pragma once
/**
\file       params-video-diff-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::gens::diff
{
/// Структура хранит информацию о операции постобработки разности
struct ParamsVideoDiffProp final {
  ParamsVideoDiffProp (bool enable = false, std::int16_t bound_filling = 0, std::int16_t val_filling = 1);
  virtual ~ParamsVideoDiffProp ();

  bool self_test () const;

  bool         enable_;          //< Флаг, включить постобработку вычисленной разности
  std::int16_t bound_filling_;   //< Значение границы, ниже или равно которой значения пикселей сбрасываются в 0
  std::int16_t val_filling_;     //< Значение пикселей, начальное значение которых больше границы

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};

void                tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const ParamsVideoDiffProp& src);
ParamsVideoDiffProp tag_invoke (::boost::json::value_to_tag< ParamsVideoDiffProp >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::gens::diff::ParamsVideoDiffProp);
