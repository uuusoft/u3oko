#pragma once
/**
\file       info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017

\project    u3_events_gui
*/

namespace libs::events_gui::utils::impl
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
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    arh& BOOST_SERIALIZATION_NVP (width_);
    arh& BOOST_SERIALIZATION_NVP (height_);
  }
};
}   // namespace libs::events_gui::utils::impl
