#pragma once
/**
\file       size.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils { namespace impl {
/**
\brief  Тривиальная реализация интерфейса ISize.
*/
class Size : public ISize
{
  public:
  Size (ISize::value_type _width = 0, ISize::value_type _height = 0)
  {
    set (_width, _height);
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
    Size* _temp = new Size;
    _temp->set (info_);
    return ISize::ptr (_temp);
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
  set (ISize::value_type _width, ISize::value_type _height)
  {
    //UASSERT( _width>0);
    //UASSERT( _height>0);
    info_.width_  = _width;
    info_.height_ = _height;

    info_.self_test ();
    return;
  }

  void
  set (const Info& _info)
  {
    _info.self_test ();
    info_ = _info;
    info_.self_test ();
    return;
  }


  protected:
  Info info_;      //< ???


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (ISize);
    ar& BOOST_SERIALIZATION_NVP (info_);
    return;
  }
};
/**
\brief    ???
\param[in]  ??? 
*/
inline void
load (const pugi::xml_node& _node, Size& _res)
{
  _res.reset ();

  pugi::xml_attribute _width  = _node.attribute ("width");
  pugi::xml_attribute _height = _node.attribute ("height");

  CHECK_STATE (!_width.empty (), "failde width not empty");
  CHECK_STATE (!_height.empty (), "failed height not empty");

  _res.set (_width.as_int (), _height.as_int ());
  return;
}

}}}}      // namespace libs::igui_events::utils::impl
