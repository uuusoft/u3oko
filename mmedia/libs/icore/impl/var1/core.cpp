/**
\file       core.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-icore-includes_int.hpp"
#include "libs-icore-impl-var1-includes.hpp"
#include "core.hpp"

namespace libs::icore::impl::var1
{
Core::Core ()
{
}


Core::~Core ()
{
  delete_graphs ();
}


void
Core::delete_graphs ()
{
  lock_type lock (mtx_);
  for (auto& graph : graphs_)
  {
    const auto count = graph.use_count ();
    if (1 != count)
    {
      U3_LOG_DATA_WRN ("try delete graph with ref count" + VTOLOG (count));
      U3_ASSERT (1 == count);   //  внешних ссылок не должно быть.
    }
    graph.reset ();
  }
}
}   // namespace libs::icore::impl::var1
