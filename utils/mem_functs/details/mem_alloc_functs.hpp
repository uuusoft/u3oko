#pragma once
/**
\file       mem_alloc_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      Интерфейсный файл низкогоуровневых функций для работы с памятью.
*/

namespace utils { namespace mem_functs { namespace details {

extern "C" BOOST_SYMBOL_EXPORT void afree (void** _pptr);
extern "C" BOOST_SYMBOL_EXPORT void aalloc (void** _pptr, const std::size_t _size);
extern "C" BOOST_SYMBOL_EXPORT void arealloc (void** _pptr, const std::size_t _size);

}}}      // namespace utils::mem_functs::details
