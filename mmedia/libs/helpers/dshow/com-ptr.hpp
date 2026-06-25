#pragma once
/**
\file       com-ptr.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017

\project    u3_dshow_vgen
*/
#ifdef U3_OS_WIN32_DESKTOP

namespace libs::helpers::dshow
{
template< typename TypePointer >
class ComPtr final
{
  public:
  //  ext
  const std::int32_t max_count_cycles_force_release = 10;

  ComPtr ()
  {
    reset ();
  }


  ComPtr (TypePointer* ptr)
  {
    reset ();
    ptr_ = ptr;
    if (ptr_)
    {
      ptr_->AddRef ();
    }
  }


  ComPtr (const ComPtr& src)
  {
    reset ();

    if (this == &src)
    {
      return;
    }
    release ();
    ptr_ = src.ptr_;
    if (ptr_)
    {
      ptr_->AddRef ();
    }
  }


  ~ComPtr ()
  {
    release ();
  }


  unsigned long
  release ()
  {
    unsigned long refs = 0;
    ::libs::helpers::platforms::win32::safe_release (refs, ptr_);
    ptr_ = 0;
    return refs;
  }


  void
  release_force ()
  {
    long          refs = 0;
    unsigned long res  = 0;

    while (ptr_)
    {
      ::libs::helpers::platforms::win32::safe_release (res, ptr_);
      if ((0 == res) || (++refs > max_count_cycles_force_release))
      {
        break;
      }
    }
    U3_ASSERT (nullptr == ptr_);
  }


  TypePointer*&
  update ()
  {
    U3_ASSERT (!ptr_);
    return ptr_;
  }


  TypePointer*
  operator->() const
  {
    U3_ASSERT (ptr_);
    return ptr_;
  }


  TypePointer*
  operator* () const
  {
    U3_ASSERT (ptr_);
    return ptr_;
  }


  ComPtr&
  operator= (TypePointer* ptr)
  {
    release ();
    ptr_ = ptr;
    if (ptr_)
    {
      ptr_->AddRef ();
    }
    return *this;
  }


  ComPtr&
  operator= (const ComPtr& src)
  {
    if (this == &src)
    {
      return *this;
    }
    release ();
    ptr_ = src.ptr_;
    if (ptr_)
    {
      ptr_->AddRef ();
    }
    return *this;
  }


  private:
  TypePointer* ptr_;

  void
  reset ()
  {
    ptr_ = nullptr;
  }
};
}   // namespace libs::helpers::dshow

#endif
