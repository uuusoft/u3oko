#pragma once
/**
\file       isize.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/

namespace libs::igui_events::utils
{
/// Интерфейс для работы с размерами любых объектов в GUI
class ISize
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ISize)
  typedef int value_type;
  //  ISize interface
  virtual value_type get_width () const  = 0;
  virtual value_type get_height () const = 0;
  virtual ptr        clone () const      = 0;

  protected:
  virtual ~ISize ()
  {
  }

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    return;
  }
};
}   // namespace libs::igui_events::utils
