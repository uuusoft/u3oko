#pragma once
/**
\file       guarde-gdi.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::platforms::win32
{
template< typename TTypeGDI = HRGN >
class GuardeGDI final
{
  public:
  GuardeGDI () :
    handle_ (0)
  {
  }

  ~GuardeGDI ()
  {
    free_handle ();
  }

  const TTypeGDI&
  get_handle () const
  {
    return handle_;
  }

  void
  free_handle ()
  {
    if (!is_valid ())
    {
      return;
    }

    ::libs::utility::platforms::win32::safe_delete_gdi_object (handle_);
    handle_ = 0;
  }

  bool
  is_valid ()
  {
    return (0 != handle_) ? true : false;
  }

  TTypeGDI&
  operator= (const TTypeGDI& handle)
  {
    free_handle ();
    handle_ = handle;
    return handle_;
  }

  private:
  TTypeGDI handle_;   //<

  GuardeGDI (const GuardeGDI&) = delete;
};
}   // namespace libs::utility::platforms::win32
