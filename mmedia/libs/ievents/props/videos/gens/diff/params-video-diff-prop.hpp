#pragma once
/**
\file       params-video-diff-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::gens::diff
{
/// Структура хранит информацию о операции постобработки разности
struct ParamsVideoDiffProp final {
  ParamsVideoDiffProp (bool enable = false, std::int16_t bound_filling = 0, std::int16_t val_filling = 1);
  virtual ~ParamsVideoDiffProp () = default;

  bool self_test () const;

  bool         enable_        = false;   //< Флаг, включить постобработку вычисленной разности
  std::int16_t bound_filling_ = 0;       //< Значение границы, ниже или равно которой значения пикселей сбрасываются в 0
  std::int16_t val_filling_   = 1;       //< Значение пикселей, начальное значение которых больше границы

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const ParamsVideoDiffProp& src);
ParamsVideoDiffProp tag_invoke (::boost::json::value_to_tag< ParamsVideoDiffProp >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::gens::diff::ParamsVideoDiffProp);
