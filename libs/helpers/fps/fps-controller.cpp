//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       fps-controller.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\brief      Object for control frame rate action
\project    uuu_helpers
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "fps-controller.hpp"

namespace libs { namespace helpers { namespace fps {

FpsController::FpsController () :
  leak_time_ (0.0f),
  fps_ (0.0f),
  inv_fps_ (0.0f)
{
  time_last_frame_ = boost::posix_time::microsec_clock::universal_time ();
  set_fps (0.0f);
}


FpsController::~FpsController ()
{}


void
FpsController::reset_action ()
{
  leak_time_       = 0.0f;
  time_last_frame_ = boost::posix_time::microsec_clock::universal_time ();
  return;
}


float
FpsController::get_leak ()
{
  return leak_time_;
}


float
FpsController::get_fps ()
{
  return fps_;
}


void
FpsController::set_fps (const float& _fps)
{
  fps_     = _fps;
  inv_fps_ = std::numeric_limits<float>::max ();

  if (fps_ < 0.0f)
    {
      XULOG_WARNING ("invalid fps number, correct");
      fps_ = 0.0f;
    }

  if (fps_ == 0.0f)
    {
      return;
    }

  inv_fps_ = 1.0f / fps_;
  return;
}


FpsController::duration_type
FpsController::get_time_after_last ()
{
  XULOG_TRACE ("FpsController::get_time_after_last, " << time_last_frame_);
  time_type     _now_time = boost::posix_time::microsec_clock::universal_time ();
  duration_type _ret      = _now_time - time_last_frame_;
  return _ret;
}


bool
FpsController::is_action ()
{
  XULOG_TRACE ("FpsController::is_action: beg");
  time_type _ntime = boost::posix_time::microsec_clock::universal_time ();

  if (0.0f == fps_)
    {
      time_last_frame_ = _ntime;
      XULOG_TRACE ("FpsController::is_action: skip check, " << time_last_frame_);
      return true;
    }

  duration_type _diff_time = _ntime - time_last_frame_;
  float         _atime     = _diff_time.total_milliseconds () * 0.001f + leak_time_;

  if (_atime < inv_fps_)
    {
      XULOG_TRACE ("FpsController::is_action: too fast");
      return false;
    }

  leak_time_ = _atime - inv_fps_;
  leak_time_ = (leak_time_ < 0.0f) ? 0.0f : leak_time_;

  //  if leak too large probably needed reset
  leak_time_       = (leak_time_ <= (inv_fps_ + 1.0f)) ? leak_time_ : (inv_fps_ + 1.0f);
  time_last_frame_ = _ntime;
  XULOG_TRACE ("FpsController::is_action: end");
  return true;
}

}}}      // namespace libs::helpers::fps
