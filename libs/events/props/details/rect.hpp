#pragma once
/**
\file       rect.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events { namespace props { namespace details {
/**
  \brief  empty brief
  */
class Rect
{
  public:
  explicit Rect (int _width = 0, int _height = 0);

  virtual ~Rect ();

  int get_width () const;

  int get_height () const;

  bool load (base_functs::xml::itn& _param);

  bool load (base_functs::xml::node& _param);


  private:
  int width_;

  int height_;

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}}      // namespace libs::events::props::details

BOOST_CLASS_EXPORT_KEY (::libs::events::props::details::Rect);
