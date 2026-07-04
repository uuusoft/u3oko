/**
\file       mem-proxy-base.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"
#include "mem-proxy-base.hpp"
#include "memory"
#include "mmedia/libs/utility/process/process-helper-funcs.hpp"

namespace libs::utility::proxy::consts
{
constexpr std::size_t min_size = static_cast< const std::size_t > (1 * 1024);    //< Минимальный размер памяти под разделяемый буфер
constexpr std::size_t max_size = static_cast< const std::size_t > (16 * 1024);   //< Максимальный размер памяти под разделяемый буфер
}   // namespace libs::utility::proxy::consts


namespace libs::utility::proxy
{
MemProxyBase::MemProxyBase (const std::string& prefix, std::size_t req_size)
{
  U3_ASSERT (!prefix.empty ());
  U3_ASSERT (req_size <= consts::max_size);

  const std::string pid   = std::to_string (process::get_id ());
  const std::string times = std::to_string (process::get_start_time ());

  mem_id_ = prefix + "pid_" + pid + "times_" + times;
  obj_id_ = mem_id_ + ".obj";

  const auto rsize = std::min< std::size_t > (std::max< std::size_t > (req_size, consts::min_size), consts::max_size);

  boost::interprocess::permissions perm;
  perm.set_unrestricted ();
  pshm_ = std::make_unique< shared_mem_type > (boost::interprocess::open_or_create, mem_id_.c_str (), rsize, nullptr, perm);
}


MemProxyBase::~MemProxyBase ()
{
  if (!mem_id_.empty ())
  {
    pshm_.reset ();
    mem_id_.clear ();
    obj_id_.clear ();
  }
}
}   // namespace libs::utility::proxy
