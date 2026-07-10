#pragma once
/**
\file       ialg-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_filter_space
*/

namespace dlls::noisez::space::impl::rang
{
/// Общий интерфейс для различных реализаций варианта ранговой фильтрации изображения в пространственной области
class IAlgImpl
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (IAlgImpl)
  U3_ADD_DELETE_MOVE_COPY (IAlgImpl);

  IAlgImpl ()          = default;
  virtual ~IAlgImpl () = default;

  virtual void process (const ProcessAlgInfo& info) = 0;
};
}   // namespace dlls::noisez::space::impl::rang
