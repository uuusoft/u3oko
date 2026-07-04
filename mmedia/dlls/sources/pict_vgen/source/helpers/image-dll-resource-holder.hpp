#pragma once
/**
\file       image-dll-resource-holder.hpp
\author     Erashov Anton erashov2026@proton.me
\date       11.05.2022
\project    u3_pict_vgen
*/

namespace dlls::sources::pict_vgen::helpers
{
template<
  typename TTRes,
  void (__stdcall* free_funct) (TTRes*) >
class ResourceHolder final
{
  public:
  explicit ResourceHolder (TTRes* val = nullptr) :
    val_ (val)
  {
  }

  ~ResourceHolder () noexcept
  {
    release ();
  }

  ResourceHolder (const ResourceHolder& lph)
  {
    *this = lph;
  }

  ResourceHolder&
  operator= (const ResourceHolder& lph)
  {
    release ();
    std::swap (val_, lph.val_);
    return *this;
  }

  void
  release () noexcept
  {
    if (val_)
    {
      try
      {
        free_funct (val_);
      }
      catch (const std::exception& excpt)
      {
        U3_LOG_DATA_EXCEPT (excpt.what ());
      }
      catch (...)
      {
        U3_LOG_DATA_EXCEPT ("...");
      }
      val_ = nullptr;
    }
  }

  TTRes*&
  update ()
  {
    release ();
    return val_;
  }

  void
  set (TTRes* val)
  {
    release ();
    val_ = val;
  }

  operator bool () const
  {
    return val_ ? true : false;
  }

  TTRes*
  operator* ()
  {
    U3_CHECK (val_, "operator*");
    return val_;
  }

  private:
  TTRes* val_ = nullptr;
};
}   // namespace dlls::sources::pict_vgen::helpers
