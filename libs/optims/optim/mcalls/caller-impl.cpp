//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       caller-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017.
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "caller-impl.hpp"
#include "mmedia/libs/helpers/statistic/helpers/functors_with_statistic.hpp"

namespace libs { namespace optim { namespace mcalls {

CallerImpl::CallerImpl ()
{
  guard_type _grd (mtx_);

  max_threads_ = 1;
  simd_        = TypeExtCpu::usual;
  create_threads ();
}


CallerImpl::~CallerImpl ()
{
  guard_type _grd (mtx_);
  CHECK_CALL_NO_THROW (stop_and_wait_threads ());
}


void
CallerImpl::mcall (
  const InfoMFunct&    _funct,
  io::MCallInfo&       _info,
  const unsigned short _athreads)
{
  guard_type       _grd (mtx_);
  AddTimeStatistic _stat_grd (expand_time_algs_, _funct.pfunct_->get_text ());
  CHECK_CALL (mcall_int (_funct, _info, _athreads), "failed, mcall_int");
  return;
}


void
CallerImpl::set_count_threads (unsigned short _count)
{
  guard_type _grd (mtx_);

  ::libs::helpers::utils::check_bound<unsigned short> (_count, 1, consts::max_threads);
  CHECK_CALL (stop_and_wait_threads (), "failed, stop threads");
  max_threads_ = _count;
  create_threads ();
  return;
}


const unsigned short
CallerImpl::get_count_threads () const
{
  guard_type _grd (mtx_);
  return max_threads_;
}


void
CallerImpl::set_cpu (const TypeExtCpu& _simd)
{
  guard_type _grd (mtx_);
  simd_ = _simd;
  return;
}

}}}      // namespace libs::optim::mcalls
