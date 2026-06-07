/**
\file       fps-controller.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\brief      Object for control frame rate action
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "fps-controller.hpp"

namespace libs::helpers::fps
{
FpsController::FpsController ()
{
  time_last_frame_ = boost::posix_time::microsec_clock::universal_time ();
  set_fps (0.0F);
}


void
FpsController::reset_action ()
{
  leak_time_       = 0.0F;
  time_last_frame_ = boost::posix_time::microsec_clock::universal_time ();
}


float
FpsController::get_leak () const
{
  return leak_time_;
}


float
FpsController::get_fps () const
{
  return fps_;
}


void
FpsController::set_fps (const float& fps)
{
  fps_     = fps;
  inv_fps_ = std::numeric_limits< float >::max ();

  if (fps_ < 0.0F)
  {
    U3_XLOG_WARN ("invalid fps number, correct");
    fps_ = 0.0F;
  }

  if (fps_ == 0.0F)
  {
    return;
  }

  inv_fps_ = 1.0F / fps_;
}


FpsController::duration_type
FpsController::get_time_after_last ()
{
  time_type     now_time = boost::posix_time::microsec_clock::universal_time ();
  duration_type ret      = now_time - time_last_frame_;
  return ret;
}


bool
FpsController::is_action ()
{
  time_type ntime = boost::posix_time::microsec_clock::universal_time ();

  if (0.0F == fps_)
  {
    time_last_frame_ = ntime;

    return true;
  }

  duration_type diff_time = ntime - time_last_frame_;
  float         atime     = diff_time.total_milliseconds () * 0.001f + leak_time_;

  if (atime < inv_fps_)
  {
    return false;
  }

  leak_time_ = atime - inv_fps_;
  leak_time_ = (leak_time_ < 0.0F) ? 0.0F : leak_time_;

  //  if leak too large probably needed reset
  leak_time_       = (leak_time_ <= (inv_fps_ + 1.0F)) ? leak_time_ : (inv_fps_ + 1.0F);
  time_last_frame_ = ntime;
  return true;
}
}   // namespace libs::helpers::fps
