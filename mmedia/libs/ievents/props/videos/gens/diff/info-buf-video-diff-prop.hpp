#pragma once
/**
\file       info-buf-video-diff-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::gens::diff
{
/// Структура для группировки параметров алгоритма вычисления разности между кадрами
struct InfoBuffVideoDiffProp final {
  InfoBuffVideoDiffProp ();
  virtual ~InfoBuffVideoDiffProp ();

  ::utils::dbufs::video::consts::offs::off_buf_type bindx_diff_;   //< Буфера источника и назначения для разности
  ParamsVideoDiffProp                               op_;           //< Операция постобработки разности

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};

void                  tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const InfoBuffVideoDiffProp& src);
InfoBuffVideoDiffProp tag_invoke (::boost::json::value_to_tag< InfoBuffVideoDiffProp >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::gens::diff::InfoBuffVideoDiffProp);
