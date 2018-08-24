//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       core.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Реализация внешних функций ядра.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "includes.hpp"
#include "core.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 {

Core::Core ()
{}


Core::~Core ()
{
  delete_paths ();
}

}}}}      // namespace libs::icore::impl::var1
