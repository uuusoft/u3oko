#pragma once
/**
\file       info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017

\project    uuu_igui_evenets
*/

namespace libs::igui_events::utils::impl
{
struct Info {
  public:
  Info ()
  {
    reset ();
  }

  bool
  self_test () const
  {
    return true;
  }

  void
  reset ()
  {
    width_  = 0;
    height_ = 0;
  }

  std::int32_t width_;    //<
  std::int32_t height_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (width_);
    ar& BOOST_SERIALIZATION_NVP (height_);
  }
};
}   // namespace libs::igui_events::utils::impl
