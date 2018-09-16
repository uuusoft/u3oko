//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       caller-impl-thread-functs.cpp
\date       01.09.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "caller-impl.hpp"

namespace libs { namespace optim { namespace mcalls {

#if 0
using ::modules::uuu_log::appl::thread::ExceptionLogger<::libs::link::ILink::ptr> ExceptionLogger;
#else
//  debug
struct ExceptionLogger
{
  ExceptionLogger (::libs::link::ILink::ptr _ptr)
  {}

  void
  operator() (const std::string& _text)
  {}
};
#endif

bool
CallerImpl::stop_and_wait_threads ()
{
  InfoMFunct    _fake_funct;
  io::MCallInfo _fake_info;
  io::ProxyBuff _proxy;

  sinfo_.exit_request_ = true;

  _proxy.width_  = 320;
  _proxy.height_ = 240;
  _proxy.stride_ = _proxy.width_ * sizeof (short);

  _fake_info.dsts_.push_back (_proxy);

  bool _ret = mcall_int (_fake_funct, _fake_info, 0);

  UASSERT (_ret);

  for (auto& _thread : threads_)
    {
      if (_thread.joinable ())
        {
          _thread.join ();
        }
    }

  max_threads_ = 0;
  UASSERT (_ret);
  return _ret;
}


void
CallerImpl::create_threads ()
{
  sinfo_.bstart_.reset (new (std::nothrow) boost::barrier (max_threads_ + 1));
  sinfo_.bend_.reset (new (std::nothrow) boost::barrier (max_threads_ + 1));
  sinfo_.exit_request_ = false;

  threads_.clear ();
  threads_.reserve (max_threads_);

  for (decltype (max_threads_) _indx_thread = 0; _indx_thread < max_threads_; ++_indx_thread)
    {
      threads_.push_back (
        std::move (
          std::thread (
            ::libs::helpers::thread::generic_thread_funct<CallerImpl, ExceptionLogger>,
            this,
            ExceptionLogger (::libs::link::ILink::ptr ()),
            UUU_ICAST_USHORT (_indx_thread))));
    }

  UASSERT (threads_.size () == max_threads_);
  return;
}


void
CallerImpl::thread_funct_impl (const unsigned short _indx_thread)
{
  do
    {
      //  wait work or die
      (*sinfo_.bstart_).wait ();
      //  check state
      //  its not end
      if (sinfo_.exit_request_)
        {
          //  release main thread
          (*sinfo_.bend_).wait ();
          break;
        }

      if (!thread_functs_[_indx_thread])
        {
          //release main thread
          (*sinfo_.bend_).wait ();
          continue;
        }

      UASSERT (calls_.size () > _indx_thread);
      UASSERT (src_heights_.size () > _indx_thread);

      try
        {
          thread_functs_[_indx_thread](calls_[_indx_thread]);
        }
      catch (boost::exception& _e)
        {
          XULOG_ERROR ("CallerImpl::thread_funct_impl: exception, " << boost::diagnostic_information_what (_e));
          (*sinfo_.bend_).wait ();
          UASSERT_SIGNAL ("failed");
          throw;
        }
      catch (std::exception& _e)
        {
          XULOG_ERROR ("CallerImpl::thread_funct_impl: exception, " << _e.what ());
          (*sinfo_.bend_).wait ();
          UASSERT_SIGNAL ("failed");
          throw;
        }

      //  release main thread
      (*sinfo_.bend_).wait ();
    }
  while (true);
  return;
}


void
CallerImpl::thread_postfunct_impl ()
{
  return;
}

}}}      // namespace libs::optim::mcalls
