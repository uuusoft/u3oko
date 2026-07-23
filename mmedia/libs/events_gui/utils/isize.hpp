#pragma once
/**
\file       isize.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/

namespace libs::events_gui::utils
{
/// Интерфейс для работы с размерами любых объектов в GUI
class ISize
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (ISize)
  typedef int value_type;
  //  ISize interface
  virtual value_type get_width () const  = 0;
  virtual value_type get_height () const = 0;
  virtual ptr        clone () const      = 0;

  protected:
  virtual ~ISize () = default;

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    return;
  }
};
}   // namespace libs::events_gui::utils
