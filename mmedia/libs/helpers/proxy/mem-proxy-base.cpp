/**
\file       mem-proxy-base.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mem-proxy-base.hpp"
#include "mmedia/libs/helpers/process/process-helper-funcs.hpp"

namespace libs::helpers::proxy::consts
{
constexpr std::size_t min_size = 1 * 1024;    //< Минимальный размер памяти под разделяемый буфер
constexpr std::size_t max_size = 16 * 1024;   //< Максимальный размер памяти под разделяемый буфер
}   // namespace libs::helpers::proxy::consts


namespace libs::helpers::proxy
{
MemProxyBase::MemProxyBase (const std::string& prefix, std::size_t req_size)
{
  U3_ASSERT (!prefix.empty ());
  U3_ASSERT (req_size <= consts::max_size);

  const std::int32_t pid    = process::get_id ();
  const std::string  pids   = std::to_string (pid);
  const std::int64_t stime  = process::get_start_time ();
  const std::string  stimes = std::to_string (stime);

  mid_ = prefix + "p_" + pids + "t_" + stimes;
  cid_ = mid_ + ".obj";

  boost::interprocess::permissions perm;
  const std::size_t                rsize = std::min< std::size_t > (std::max< std::size_t > (req_size, consts::min_size), consts::max_size);

  perm.set_unrestricted ();
  pshm_.reset (new shared_mem_type (boost::interprocess::open_or_create, mid_.c_str (), rsize, 0, perm));
}


MemProxyBase::~MemProxyBase ()
{
  if (!mid_.empty ())
  {
    pshm_.reset ();
    mid_.clear ();
  }
}
}   // namespace libs::helpers::proxy
