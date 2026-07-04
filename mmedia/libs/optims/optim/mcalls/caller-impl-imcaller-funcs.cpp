/**
\file       caller-impl-imcaller-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_optim_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-optims-optim-mcalls-includes_int.hpp"
#include "caller-impl.hpp"
#include "mmedia/libs/utility/statistic/helpers/expanded-times-helpers.hpp"

namespace libs::optim::mcalls
{
void
CallerImpl::mthreads_call (
  const ::libs::core::graph::NodeID& id_node,
  const MTFuncInfo&                  funct,
  ::libs::optim::io::MCallInfo&      info,
  syn::ExpandedTimes&                expand_time_algs,
  const std::uint16_t                athreads)
{
  try
  {
    lock_type      lock (mtx_);
    syn::AddOpTime exp_stat (expand_time_algs, ::libs::core::graph::get_ext_graph_node_id (id_node), funct.pfunc_->get_algoritm_name ());
    mthreads_call_int (funct, info, athreads);
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
  catch (...)
  {
    U3_LOG_DATA_EXCEPT ("...");
  }
}


void
CallerImpl::set_count_threads (std::uint16_t count)
{
  U3_XLOG_MARK ("update the number of work threads" + VTOLOG (count))
  lock_type lock (mtx_);
  ::libs::utility::utils::check_bound< std::uint16_t > (count, 1, consts::max_threads);
  stop_and_wait_threads ();
  max_threads_ = count;
  create_threads ();
}


auto
CallerImpl::get_count_threads () const -> std::uint16_t
{
  lock_type lock (mtx_);
  return max_threads_;
}
}   // namespace libs::optim::mcalls
