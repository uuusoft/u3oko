//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mem-proxy-base.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mem-proxy-base.hpp"
#include "mmedia/libs/helpers/process/process_functs.hpp"

namespace libs { namespace helpers { namespace proxy { namespace consts {

const std::size_t min_size = 1 * 1024;       //< Минимальный размер памяти под разделяемый буфер.
const std::size_t max_size = 16 * 1024;      //< Максимальный размер памяти под разделяемый буфер.

}}}}      // namespace libs::helpers::proxy::consts

namespace libs { namespace helpers { namespace proxy {

MemProxyBase::MemProxyBase (const std::string& _prefix, std::size_t _req_size)
{
  UASSERT (!_prefix.empty ());
  UASSERT (_req_size <= consts::max_size);
  const int              _pid    = process::get_id ();
  const std::string      _pids   = to_str (_pid);
  const signed long long _stime  = process::get_start_time ();
  const std::string      _stimes = to_str (_stime);

  mid_ = _prefix + "p_" + _pids + "t_" + _stimes;
  cid_ = mid_ + ".obj";

  boost::interprocess::permissions _perm;
  const std::size_t                _rsize = std::min<std::size_t> (std::max<std::size_t> (_req_size, consts::min_size), consts::max_size);

  _perm.set_unrestricted ();
  pshm_.reset (new shared_mem_type (boost::interprocess::open_or_create, mid_.c_str (), _rsize, 0, _perm));
  return;
}


MemProxyBase::~MemProxyBase ()
{
  if (!mid_.empty ())
    {
      pshm_.reset ();
      mid_.clear ();
    }
  return;
}

}}}      // namespace libs::helpers::proxy
