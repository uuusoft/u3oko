#pragma once
/**
\file       morph-operation-params.hpp
\date       10.09.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::morph::syn
{
using off_buf_type = ::utils::dbufs::video::consts::offs::off_buf_type;
}

namespace libs::ievents::props::videos::generic::morph
{
struct MorphOperationParams final {
  explicit MorphOperationParams (
    const MorphOps&    type          = MorphOps::empty,
    const std::int32_t size_spot     = 3,
    const std::int32_t bound_filling = 1,
    const std::int32_t val_filling   = 255);

  virtual ~MorphOperationParams ();

  bool self_test () const;

  MorphOps     morph_type_;      //<
  std::int32_t size_spot_;       //<
  std::int32_t bound_filling_;   //<
  std::int32_t val_filling_;     //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */);
};

void                 tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const MorphOperationParams& src);
MorphOperationParams tag_invoke (::boost::json::value_to_tag< MorphOperationParams >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::generic::morph

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::morph::MorphOperationParams);
