#pragma once
/**
\file       guarde-gdi.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace win32 {
#if defined(UUU_OS_WIN32_DESKTOP)
/**
  \brief  empty brief
  */
template <
  typename TTypeGDI = HRGN>
class GuardeGDI
{
  public:
  GuardeGDI () :
    handle_ (0)
  {}

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

    ::libs::helpers::win32::safe_delete_go (handle_);
    handle_ = 0;
    return;
  }

  bool
  is_valid ()
  {
    return (0 != handle_) ? true : false;
  }

  TTypeGDI&
  operator= (const TTypeGDI& _handle)
  {
    free_handle ();
    handle_ = _handle;
    return handle_;
  }


  private:
  TTypeGDI handle_;      //<

  GuardeGDI (const GuardeGDI& _src) = delete;
};
#endif
}}}      // namespace libs::helpers::win32
