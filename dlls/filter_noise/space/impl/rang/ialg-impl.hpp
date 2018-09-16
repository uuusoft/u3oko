//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       ialg-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang {
/**
\brief  Общий интерфейс для различных реализаций варианта ранговой фильтрации изображения в пространственной области.
*/
class IAlgImpl
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IAlgImpl);

  IAlgImpl ()
  {}

  virtual ~IAlgImpl ()
  {}

  IAlgImpl (const IAlgImpl& _src) = delete;
  IAlgImpl& operator= (const IAlgImpl& _src) = delete;


  virtual void process (const ProcessAlgInfo& _info) = 0;
};

}}}}}      // namespace dlls::filter_noise::space::impl::rang
