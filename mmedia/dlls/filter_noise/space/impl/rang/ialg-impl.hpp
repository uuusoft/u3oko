#pragma once
/**
\file       ialg-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
*/

namespace dlls::filter_noise::space::impl::rang
{
/// Общий интерфейс для различных реализаций варианта ранговой фильтрации изображения в пространственной области
class IAlgImpl
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IAlgImpl)

  IAlgImpl ()
  {
  }

  virtual ~IAlgImpl ()
  {
  }

  IAlgImpl (const IAlgImpl& src)            = delete;
  IAlgImpl& operator= (const IAlgImpl& src) = delete;

  virtual void process (const ProcessAlgInfo& info) = 0;
};
}   // namespace dlls::filter_noise::space::impl::rang
