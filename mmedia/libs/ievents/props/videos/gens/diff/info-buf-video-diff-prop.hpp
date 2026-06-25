#pragma once
/**
\file       info-buf-video-diff-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::gens::diff
{
/// Структура для группировки параметров алгоритма вычисления разности между кадрами
struct InfoBuffVideoDiffProp final {
  InfoBuffVideoDiffProp ()          = default;
  virtual ~InfoBuffVideoDiffProp () = default;

  ::utils::dbufs::video::consts::offs::off_buf_type bindx_diff_ = utils::dbufs::video::consts::offs::invalid;   //< Буфера источника и назначения для разности
  ParamsVideoDiffProp                               op_;                                                        //< Операция постобработки разности

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                  tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoBuffVideoDiffProp& src);
InfoBuffVideoDiffProp tag_invoke (::boost::json::value_to_tag< InfoBuffVideoDiffProp >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::gens::diff::InfoBuffVideoDiffProp);
