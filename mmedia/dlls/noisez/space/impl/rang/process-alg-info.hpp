#pragma once
/**
\file       process-alg-info.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_filter_space
*/

namespace dlls::noisez::space::impl::rang
{
/// Тип для группировки параметров вызова функции фильтрации
struct ProcessAlgInfo final {
  ProcessAlgInfo ()  = default;
  ~ProcessAlgInfo () = default;

  void
  reset ()
  {
    buf_       = nullptr;
    sbuf_      = nullptr;
    dbuf_      = nullptr;
    pfinfo_    = nullptr;
    impl_info_ = nullptr;
  }

  bool
  check () const
  {
    if (!buf_ || !sbuf_ || !pfinfo_ || !impl_info_)
    {
      U3_ASSERT_SIGNAL_NT ("failed");
      return false;
    }

    // if (pfinfo_->rprops_->use_cond_buf_)
    if (impl_info_->use_cond_buf_)
    {
      return dbuf_ ? true : false;
    }
    return true;
  }

  ::libs::optim::io::ProxyBuf*         buf_       = nullptr;   //< Буфер для результата фильтрации
  const ::libs::optim::io::ProxyBuf*   sbuf_      = nullptr;   //< Буфер входных данных
  const ::libs::optim::io::ProxyBuf*   dbuf_      = nullptr;   //< Опциональный буфер условий фильтрации
  InfoFilter*                          pfinfo_    = nullptr;   //< Указатель на узел графа потока фильтрации
  syn::MedianSpaceFilterProp::craw_ptr impl_info_ = nullptr;   //< Параметры фильтрации
};
}   // namespace dlls::noisez::space::impl::rang
