#pragma once
/**
\file       fps-controller.hpp
\brief      bject for control frame rate action
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  ~FpsController ();

  FpsController (const FpsController& src)            = delete;
  FpsController& operator= (const FpsController& src) = delete;

  void  reset_action ();
  float get_fps ();
  void  set_fps (const float& fps);
  float get_leak ();

  duration_type get_time_after_last ();

  //  return true if needed action or false if skip action anywhere error
  bool is_action ();

  protected:
  float     leak_time_;         //<
  time_type time_last_frame_;   //<
  float     fps_;               //<
  float     inv_fps_;           //<
};
}   // namespace libs::helpers::fps
