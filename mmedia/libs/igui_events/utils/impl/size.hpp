#pragma once
/**
\file       size.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    uuu_igui_evenets
*/

namespace libs::igui_events::utils::impl
{
/// Тривиальная реализация интерфейса ISize
class Size : public ISize
{
  public:
  Size (ISize::value_type width = 0, ISize::value_type height = 0)
  {
    set (width, height);
  }

  virtual ISize::value_type
  get_width () const override
  {
    return info_.width_;
  }

  virtual ISize::value_type
  get_height () const override
  {
    return info_.height_;
  }

  virtual ISize::ptr
  clone () const override
  {
    Size* temp = new Size;
    temp->set (info_);
    return ISize::ptr (temp);
  }

  bool
  self_test () const
  {
    return info_.self_test ();
  }

  void
  reset ()
  {
    info_.reset ();
  }

  void
  set (ISize::value_type width, ISize::value_type height)
  {
    // U3_ASSERT( width>0);
    // U3_ASSERT( height>0);
    info_.width_  = width;
    info_.height_ = height;

    info_.self_test ();
  }

  void
  set (const Info& info)
  {
    info.self_test ();
    info_ = info;
    info_.self_test ();
  }

  protected:
  Info info_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoutilsoISize", ::libs::igui_events::utils::ISize);
    ar& BOOST_SERIALIZATION_NVP (info_);
  }
};


inline void
load (const pugi::xml_node& node, Size& res)
{
  res.reset ();

  pugi::xml_attribute width  = node.attribute ("width");
  pugi::xml_attribute height = node.attribute ("height");

  U3_CHECK (!width.empty (), "failde width not empty");
  U3_CHECK (!height.empty (), "height not empty");

  res.set (width.as_int (), height.as_int ());
}
}   // namespace libs::igui_events::utils::impl
