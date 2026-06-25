#pragma once
/**
\file       fps-controller.hpp
\brief      bject for control frame rate action
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_helpers_lib
*/

namespace libs::helpers::fps
{
class FpsController final
{
  public:
  //  ext types
  using time_type     = boost::posix_time::ptime;
  using duration_type = boost::posix_time::time_duration;

  FpsController ();
  ~FpsController () = default;

  FpsController (const FpsController& src)            = delete;
  FpsController& operator= (const FpsController& src) = delete;

  void  reset_action ();
  float get_fps () const;
  void  set_fps (const float& fps);
  float get_leak () const;

  duration_type get_time_after_last ();

  //  return true if needed action or false if skip action anywhere error
  bool is_action ();

  protected:
  float     leak_time_       = 0.0F;                                                   //<
  time_type time_last_frame_ = boost::posix_time::microsec_clock::universal_time ();   //<
  float     fps_             = 0.0F;                                                   //<
  float     inv_fps_         = 0.0F;                                                   //<
};
}   // namespace libs::helpers::fps
