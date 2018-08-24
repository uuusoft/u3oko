#pragma once
/**
\file       com-ptr.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/

namespace libs { namespace helpers { namespace dshow {

#if defined(UUU_OS_WIN32_DESKTOP)
/**
  \brief  empty brief
  */
template <
  typename TypePointer>
class ComPtr
{
  public:
  //  ext
  const int max_count_cycles_force_release = 10;

  ComPtr ()
  {
    reset ();
  }


  ComPtr (TypePointer* _ptr)
  {
    reset ();
    ptr_ = _ptr;
    if (ptr_)
      {
        ptr_->AddRef ();
      }
  }


  ComPtr (const ComPtr& _src)
  {
    reset ();

    if (this == &_src)
      {
        return;
      }
    release ();
    ptr_ = _src.ptr_;
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
    unsigned long _refs = 0;
    ::libs::helpers::win32::safe_release (_refs, ptr_);
    ptr_ = 0;
    return _refs;
  }


  void
  release_force ()
  {
    long          _refs = 0;
    unsigned long _res  = 0;

    while (ptr_)
      {
        ::libs::helpers::win32::safe_release (_res, ptr_);
        if ((0 == _res) || (++_refs > max_count_cycles_force_release))
          {
            break;
          }
      }
    UASSERT (nullptr == ptr_);
    return;
  }


  TypePointer*&
  update ()
  {
    UASSERT (!ptr_);      //  возможна только установка указателя, но ни в коем случае не сброс.
    return ptr_;
  }


  TypePointer* operator-> () const
  {
    UASSERT (ptr_);
    return ptr_;
  }


  TypePointer* operator* () const
  {
    UASSERT (ptr_);
    return ptr_;
  }


  ComPtr&
  operator= (TypePointer* _ptr)
  {
    release ();
    ptr_ = _ptr;
    if (ptr_)
      {
        ptr_->AddRef ();
      }
    return *this;
  }


  ComPtr&
  operator= (const ComPtr& _src)
  {
    if (this == &_src)
      {
        return *this;
      }
    release ();
    ptr_ = _src.ptr_;
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
    return;
  }
};
#endif

}}}      // namespace libs::helpers::dshow
