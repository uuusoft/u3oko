//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       process-alg-info.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang {
/**
  \brief  Тип для группировки параметров вызова функции фильтрации.
  */
struct ProcessAlgInfo
{
  ProcessAlgInfo () :
    buff_ (nullptr),
    sbuff_ (nullptr),
    dbuff_ (nullptr),
    pfinfo_ (nullptr),
    impl_info_ (nullptr)
  {}

  ~ProcessAlgInfo ()
  {}

  void
  reset ()
  {
    buff_      = nullptr;
    sbuff_     = nullptr;
    dbuff_     = nullptr;
    pfinfo_    = nullptr;
    impl_info_ = nullptr;
    return;
  }

  bool
  check () const
  {
    if (!buff_ || !sbuff_ || !pfinfo_ || !impl_info_)
      {
        UASSERT_SIGNAL ("failed");
        return false;
      }

    if (pfinfo_->rprops_->use_cond_buff_)
      {
        if (!dbuff_)
          {
            UASSERT_SIGNAL ("failed");
            return false;
          }
      }
    return true;
  }

  ProxyBuff*                      buff_;           //< Буфер для результата фильтрации.
  const ProxyBuff*                sbuff_;          //< Буфер входных данных.
  const ProxyBuff*                dbuff_;          //< Опциональный буфер условий фильтрации.
  InfoFilter*                     pfinfo_;         //< Указатель на узел графа потока фильтрации.
  MedianSpaceFilterProp::craw_ptr impl_info_;      //< Параметры фильтрации.
};

}}}}}      // namespace dlls::filter_noise::space::impl::rang
