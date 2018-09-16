//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       ifilter-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      Файл внутреннего интерфейса, который должны поддерживать все реализации фильтрации.
*/

namespace dlls { namespace filter_noise { namespace space {
/**
\brief  Интерфейс, который должны поддерживать все реализаций данного типа фильтрации (т.е., в пространственной области).
*/
class IFilterImpl
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IFilterImpl);

  IFilterImpl ()
  {}

  virtual ~IFilterImpl ()
  {}

  IFilterImpl& operator= (const IFilterImpl& _obj) = delete;
  IFilterImpl (const IFilterImpl& _obj)            = delete;
  //  IFilterImpl interface
  virtual void transform_int (InfoFilter& _props, ::libs::buffs::Buffs* _pbuff) = 0;
  virtual void load_int ()                                                      = 0;
};

}}}      // namespace dlls::filter_noise::space
