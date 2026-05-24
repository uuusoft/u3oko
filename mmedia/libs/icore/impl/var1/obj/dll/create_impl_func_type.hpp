#pragma once
/**
\file       create_impl_func_type.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj::dll
{
class IFilter;
}


namespace libs::icore::impl::var1::obj::dll
{
using create_impl_func_type = libs::icore::impl::var1::obj::dll::IFilter*();   //< Cоответственно описание указателя на точку входа в dll/so, которая реализует объект графа обработки данных
}   // namespace libs::icore::impl::var1::obj::dll
