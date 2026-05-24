#pragma once
/**
\file       process-alg-info.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
*/

namespace dlls::filter_noise::space::impl::rang::syn
{
using MedianSpaceFilterProp = ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp;
}

namespace dlls::filter_noise::space::impl::rang
{
/// Тип для группировки параметров вызова функции фильтрации
struct ProcessAlgInfo final {
  ProcessAlgInfo () :
    buf_ (nullptr),
    sbuf_ (nullptr),
    dbuf_ (nullptr),
    pfinfo_ (nullptr),
    impl_info_ (nullptr)
  {
  }

  ~ProcessAlgInfo ()
  {
  }

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

    if (pfinfo_->rprops_->use_cond_buf_)
    {
      return dbuf_ ? true : false;
    }
    return true;
  }

  ::libs::optim::io::ProxyBuf*         buf_;         //< Буфер для результата фильтрации
  const ::libs::optim::io::ProxyBuf*   sbuf_;        //< Буфер входных данных
  const ::libs::optim::io::ProxyBuf*   dbuf_;        //< Опциональный буфер условий фильтрации
  InfoFilter*                          pfinfo_;      //< Указатель на узел графа потока фильтрации
  syn::MedianSpaceFilterProp::craw_ptr impl_info_;   //< Параметры фильтрации
};
}   // namespace dlls::filter_noise::space::impl::rang
