#pragma once
/**
\file       fps-controller.hpp
\brief      bject for control frame rate action
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace fps {
/**
  \brief  empty brief
  */
class FpsController
{
  public:
  //  ext types
  using time_type     = boost::posix_time::ptime;
  using duration_type = boost::posix_time::time_duration;

  FpsController ();

  ~FpsController ();

  FpsController (const FpsController& _src) = delete;
  FpsController& operator= (const FpsController& _src) = delete;

  void reset_action ();

  float get_fps ();

  void set_fps (const float& _fps);

  float get_leak ();

  duration_type get_time_after_last ();

  //  return true if needed action or false if skip action anywhere error
  bool is_action ();


  protected:
  float     leak_time_;            //< ???
  time_type time_last_frame_;      //< ???
  float     fps_;                  //< ???
  float     inv_fps_;              //< ???
};

}}}      // namespace libs::helpers::fps
