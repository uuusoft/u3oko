//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_class_ptrs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Объявление макроса для декларирования типов-указателей на объекты  заданного типа.
*/

#ifndef UUU_THIS_TYPE_HAS_POINTERS_TO_SELF
// Вспомогательный макрос для декларирования указателей на экземпляры типа внутри типа.
#define UUU_THIS_TYPE_HAS_POINTERS_TO_SELF(_type) \
                                                  \
  using ptr       = std::shared_ptr<_type>;       \
  using cptr      = std::shared_ptr<const _type>; \
  using weak_ptr  = std::weak_ptr<_type>;         \
  using cweak_ptr = std::weak_ptr<const _type>;   \
  using uniq_ptr  = std::unique_ptr<_type>;       \
  using cuniq_ptr = std::unique_ptr<const _type>; \
  using raw_ptr   = _type*;                       \
  using craw_ptr  = const _type*;

#endif

#ifndef UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE
//  ???
#define UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE(_type)                                \
  template <typename... T>                                                        \
  static ::std::shared_ptr<_type>                                                 \
  make_shared_this (T&&... args)                                                  \
  {                                                                               \
    return ::std::make_shared<_type> (Acessor{ 0 }, ::std::forward<T> (args)...); \
  }

#endif
