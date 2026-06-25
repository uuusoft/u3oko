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
  typename ResTType,
  void (__stdcall* free_funct) (ResTType*) >
class ResourceHolder final
{
  public:
  explicit ResourceHolder (ResTType* val = nullptr) :
    resval_ (val)
  {
  }

  ~ResourceHolder () noexcept
  {
    release ();
  }

  ResourceHolder (const ResourceHolder& lph) :
    resval_ (nullptr)
  {
    *this = lph;
  }

  ResourceHolder&
  operator= (const ResourceHolder& lph)
  {
    release ();
    std::swap (resval_, lph.resval_);
    return *this;
  }

  void
  release () noexcept
  {
    if (nullptr == resval_)
    {
      return;
    }

    try
    {
      free_funct (resval_);
    }
    catch (const std::exception& excpt)
    {
      U3_LOG_DATA_EXCEPT (excpt.what ());
    }
    catch (...)
    {
      U3_LOG_DATA_EXCEPT ("...");
    }

    resval_ = nullptr;
  }

  ResTType*&
  update ()
  {
    release ();
    return resval_;
  }

  void
  set (ResTType* val)
  {
    release ();
    resval_ = val;
  }

  operator bool () const
  {
    return resval_ ? true : false;
  }

  ResTType*
  operator* ()
  {
    U3_CHECK (resval_, "operator*");
    return resval_;
  }

  private:
  ResTType* resval_;
};
}   // namespace dlls::sources::pict_vgen::helpers
