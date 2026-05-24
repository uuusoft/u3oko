/**
\file       core-icore-funcs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_icore_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-icore-includes_int.hpp"
#include "libs-icore-impl-var1-includes.hpp"
#include "core.hpp"

namespace libs::icore::impl::var1
{
void
Core::get_graphs_int (out_wgraphs_type& graphs)
{
  lock_type lock (mtx_);
  graphs.clear ();
  std::copy (graphs_.begin (), graphs_.end (), std::back_inserter (graphs));
}


::libs::core::graph::IGraph::weak_ptr
Core::create_graph_int ()
{
  lock_type lock (mtx_);
  graphs_.push_back (std::make_shared< impl::var1::graph::Graph > ());
  return ::libs::core::graph::IGraph::weak_ptr (graphs_.back ());
}


bool
Core::delete_graph_int (::libs::core::graph::IGraph::weak_ptr obj)
{
  lock_type lock (mtx_);
  auto      iobj = obj.lock ();

  if (!iobj)
  {
    return false;
  }

  auto ofind = std::find (graphs_.begin (), graphs_.end (), iobj);
  if (ofind == graphs_.end ())
  {
    U3_LOG_DATA_WRN ("delete, graph not found");
    return false;
  }

  graphs_.erase (ofind);
  iobj.reset ();
  return true;
}
}   // namespace libs::icore::impl::var1
