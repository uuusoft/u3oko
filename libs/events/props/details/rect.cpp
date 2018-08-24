//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       rect.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "rect.hpp"

namespace libs { namespace events { namespace props { namespace details {

Rect::Rect (int _width, int _height) :
  width_ (_width),
  height_ (_height)
{}


Rect::~Rect ()
{}


int
Rect::get_width () const
{
  return width_;
}


int
Rect::get_height () const
{
  return height_;
}


bool
Rect::load (base_functs::xml::itn& _param)
{
  return load (*_param);
}


bool
Rect::load (base_functs::xml::node& _param)
{
  pugi::xml_attribute _width  = _param.attribute ("width");
  pugi::xml_attribute _height = _param.attribute ("height");

  if (!_width || !_height)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  width_  = _width.as_int ();
  height_ = _height.as_int ();

  return true;
}


template <class Archive>
void
Rect::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (width_);
  ar& BOOST_SERIALIZATION_NVP (height_);
  return;
}

}}}}      // namespace libs::events::props::details

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::props::details::Rect);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::events::props::details::Rect);
