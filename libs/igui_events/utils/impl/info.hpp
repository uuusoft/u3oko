#pragma once
/** 
\file       info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils { namespace impl {
/**
\brief  empty brief
*/
struct Info
{
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

  int width_;       //< ???
  int height_;      //< ???


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (width_);
    ar& BOOST_SERIALIZATION_NVP (height_);
    return;
  }
};

}}}}      // namespace libs::igui_events::utils::impl
