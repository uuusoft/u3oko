/**
\file       caller-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_optim_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-optims-optim-mcalls-includes_int.hpp"
#include "mmedia/libs/helpers/thread/generic-thread-func.hpp"
#include "caller-impl.hpp"
#include "mmedia/libs/helpers/statistic/helpers/expanded-times-helpers.hpp"

namespace libs::optim::mcalls
{
std::atomic< std::uint32_t > CallerImpl::impl_counter_ = 0;

CallerImpl::CallerImpl ()
{
  lock_type lock (mtx_);
  U3_CHECK (impl_counter_ >= 0 && impl_counter_ <= 1, VTOLOG (impl_counter_));
  ++impl_counter_;
  max_threads_ = 1;
  create_threads ();
}


CallerImpl::~CallerImpl ()
{
  lock_type lock (mtx_);
  --impl_counter_;
  stop_and_wait_threads ();
}


unsigned long
get_count_work_threads_by_count_cpu (unsigned long val)
{
  return val <= 1 ? 1 : (val <= 4 ? val - 1 : (val <= 8 ? val - 2 : val - 4));
}

// EAI-REFACT
void
get_thread_per_height (
  const MTFuncInfo&             funct,
  ::libs::optim::io::MCallInfo& info,
  const std::uint16_t           athreads,
  std::uint32_t&                thread_per_height,
  std::uint32_t&                selected_src_height,
  std::uint32_t&                selected_dst_height,
  std::uint32_t&                width_macro)
{
  thread_per_height   = 0;
  selected_src_height = 0;
  selected_dst_height = 0;
  width_macro         = 0;

  //  get info about function from key
  bool          find_fulled_buf       = false;
  std::uint32_t thread_per_height_src = std::numeric_limits< std::uint32_t >::max ();
  std::uint32_t thread_per_height_dst = std::numeric_limits< std::uint32_t >::max ();

  width_macro = 1;

  if (!info.srcs_.empty ())
  {
    // ищем первый заполненный буфер.
    for (const auto& src : info.srcs_)
    {
      if (!src.self_test ())
      {
        // допустимо, некоторые алгоритмы допускают наличие пустых буферов.
        continue;
      }

      selected_src_height = src.height_;
      ::libs::optim::mcalls::helpers::split_height (athreads, funct.src_align_.px_y_, selected_src_height, thread_per_height_src);
      find_fulled_buf = true;
      break;
    }
  }

  if (!info.dsts_.empty ())
  {
    for (const auto& dst : info.dsts_)
    {
      if (!dst.self_test ())
      {
        // допустимо, некоторые алгоритмы допускают наличие пустых буферов.
        continue;
      }

      selected_dst_height = dst.height_;

      ::libs::optim::mcalls::helpers::split_height (
        athreads,
        funct.dst_align_.px_y_,
        selected_dst_height,
        thread_per_height_dst);

      find_fulled_buf = true;
      break;
    }
  }

  U3_ASSERT (width_macro);
  U3_ASSERT (1 == width_macro);
  U3_ASSERT (find_fulled_buf);

  if (find_fulled_buf)
  {
    thread_per_height = std::min< std::uint32_t > (thread_per_height_src, thread_per_height_dst);
  }
  else
  {
    thread_per_height = 1;
  }

  U3_ASSERT (thread_per_height);
  U3_ASSERT (thread_per_height != std::numeric_limits< std::uint32_t >::max ());
}


void
get_count_threads_funct (
  const MTFuncInfo&   funct,
  io::MCallInfo&      info,
  const std::uint16_t max_threads,
  std::uint16_t&      athreads)
{
  U3_ASSERT (info.srcs_.size () || info.dsts_.size ());   // очевидно, какие то данные алгоритм должен или получать или генерировать

  // Ищем минимальный размер буфера среди всех переданных, как источников, так и приемников результата.
  std::uint32_t min_src_height = std::numeric_limits< std::uint32_t >::max ();
  for (const io::ProxyBuf& csrc : info.srcs_)
  {
    if (csrc.self_test ())
    {
      min_src_height = std::min< std::uint32_t > (min_src_height, csrc.height_);
    }
  }

  std::uint32_t min_dst_height = std::numeric_limits< std::uint32_t >::max ();
  for (const io::ProxyBuf& cdst : info.dsts_)
  {
    if (cdst.self_test ())
    {
      min_dst_height = std::min< std::uint32_t > (min_dst_height, cdst.height_);
    }
  }

  athreads = U3_CAST_UINT16 (::libs::helpers::utils::ret_check_bound< std::uint32_t > (athreads, 1, min_src_height / funct.src_align_.px_y_));
  athreads = U3_CAST_UINT16 (::libs::helpers::utils::ret_check_bound< std::uint32_t > (athreads, 1, min_dst_height / funct.dst_align_.px_y_));
  athreads = U3_CAST_UINT16 (::libs::helpers::utils::ret_check_bound< std::uint32_t > (athreads, 1, max_threads));
}

// EAI-REFACT
void
CallerImpl::mthreads_call_int (
  const MTFuncInfo&             funct,
  ::libs::optim::io::MCallInfo& info,
  std::uint16_t                 athreads)
{
  funct.self_test ();

  if (0 == max_threads_)
  {
    //  Идет завершение работы системы и поступил вызов на обработку? Игнорируем?
    U3_XLOG_MARK ("stop request, skip call");
    return;
  }

  athreads = (0 == athreads) ? max_threads_ : athreads;            // вызывающий может явно установить количество потоков для обработки, иначе испольуем максимум
  athreads = std::min< std::uint16_t > (athreads, max_threads_);   // явно установленное значение не может быть больше максимального
  U3_ASSERT (max_threads_ > 0);
  U3_ASSERT (athreads <= max_threads_);
  U3_ASSERT (athreads > 0);

  //  Тестовый запуск потоков при пустой функции
  if (funct.is_empty ())
  {
    sinfo_.bstart_->arrive_and_wait ();
    sinfo_.bstart_->arrive_and_wait ();
    return;
  }

  //  Ищем минимальный размер буфера среди всех переданных, как источников, так и приемников результата.
  get_count_threads_funct (funct, info, max_threads_, athreads);

  thread_funcs_.assign (max_threads_, io::mtcall_func ());

  calls_.resize (max_threads_);
  src_heights_.resize (max_threads_);

  for (auto& call : calls_)
  {
    call.params_ = info.params_;
  }

  U3_CHECK (info.dsts_.size () || info.srcs_.size (), "useless call without data" + VTOLOG (info.dsts_.size ()) + VTOLOG (info.srcs_.size ()));

  std::uint32_t thread_per_height   = 0;
  std::uint32_t selected_src_height = 0;
  std::uint32_t selected_dst_height = 0;
  std::uint32_t width_macro         = 0;

  // вычисляем количество рабочих потоков на основе выравнивания данных в алгоритме и размеров буферов
  get_thread_per_height (
    funct,
    info,
    athreads,
    thread_per_height,
    selected_src_height,
    selected_dst_height,
    width_macro);

  info.count_threads_ = thread_per_height;

  std::uint32_t thread_indx = 0;

  for (std::uint32_t indxy = 0; indxy < thread_per_height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width_macro; ++indxx)
    {
      io::MCallInfo& ccall = calls_[thread_indx];

      ccall.thread_indx_     = thread_indx;
      ccall.count_threads_   = thread_per_height;
      ccall.full_height_src_ = selected_src_height;
      ccall.full_height_dst_ = selected_dst_height;

      ccall.srcs_.clear ();
      ccall.dsts_.clear ();

      if (thread_indx >= athreads)
      {
        continue;
      }

      for (const io::ProxyBuf& cbuf : info.srcs_)
      {
        io::ProxyBuf new_add = cbuf;
        new_add.reset_const ();

        if (new_add.buf ())
        {
          const std::uint32_t macro_height      = new_add.height_ / funct.src_align_.px_y_;
          const std::uint32_t height_prev_block = macro_height / thread_per_height;
          std::uint32_t       height_cur_block  = height_prev_block;

          if (indxy + 1 == thread_per_height)
          {
            if (height_cur_block * thread_per_height < macro_height)
            {
              height_cur_block += macro_height - height_cur_block * thread_per_height;
            }
          }

          new_add.width_  = new_add.width_ / width_macro;
          new_add.height_ = height_cur_block * funct.src_align_.px_y_;

          std::uint32_t off_rows = indxy * height_prev_block * funct.src_align_.px_y_;
          std::uint32_t off_cols = indxx * new_add.width_ * sizeof (std::int16_t);
          std::uint32_t off_src  = off_rows * new_add.stride_ + off_cols;

          new_add.set_ubuf (new_add.ubuf () + off_src);
        }

        ccall.srcs_.push_back (new_add);
      }

      for (const io::ProxyBuf& cbuf : info.dsts_)
      {
        io::ProxyBuf new_add = cbuf;
        U3_CHECK (new_add.buf (), "new add buf empty");
        if (new_add.buf ())
        {
          const std::uint32_t macro_height      = new_add.height_ / funct.dst_align_.px_y_;
          const std::uint32_t height_prev_block = macro_height / thread_per_height;
          std::uint32_t       height_cur_block  = height_prev_block;

          if (indxy + 1 == thread_per_height)
          {
            if (height_cur_block * thread_per_height < macro_height)
            {
              height_cur_block += macro_height - height_cur_block * thread_per_height;
            }
          }

          new_add.width_  = new_add.width_ / width_macro;
          new_add.height_ = height_cur_block * funct.dst_align_.px_y_;

          std::uint32_t off_rows = indxy * height_prev_block * funct.dst_align_.px_y_ * funct.dest_mul_koeffy_ / funct.dest_div_koeffy_;
          std::uint32_t off_cols = indxx * new_add.width_ * sizeof (std::int16_t);
          std::uint32_t off_src  = off_rows * new_add.stride_ + off_cols;

          new_add.set_ubuf (new_add.ubuf () + off_src);
        }

        ccall.dsts_.push_back (new_add);
      }

      thread_funcs_[thread_indx] = funct.pfunc_->get ();
      ++thread_indx;
    }
  }

  //  run threads
  sinfo_.bstart_->arrive_and_wait ();
  //  wait result
  sinfo_.bstart_->arrive_and_wait ();
}


void
CallerImpl::stop_and_wait_threads ()
{
  U3_XLOG_MARK ("CallerImpl::stop_and_wait_threads::---->");
  try
  {
    MTFuncInfo    fake_funct;
    io::MCallInfo fake_info;
    io::ProxyBuf  proxy;

    sinfo_.exit_request_ = true;

    proxy.width_  = 320;
    proxy.height_ = 240;
    proxy.stride_ = proxy.width_ * sizeof (std::int16_t);

    fake_info.dsts_.push_back (proxy);

    mthreads_call_int (fake_funct, fake_info, 0);

    for (auto& thread : threads_)
    {
      if (thread.joinable ())
      {
        thread.join ();
      }
    }
  }
  catch (const std::exception& excpt)
  {
    U3_XLOG_ERROR (excpt.what ());
  }
  catch (...)
  {
    U3_XLOG_ERROR ("...");
  }

  max_threads_ = 0;
  U3_XLOG_MARK ("CallerImpl::stop_and_wait_threads::<----");
}


void
CallerImpl::create_threads ()
{
  U3_XLOG_DBG ("CallerImpl::create_threads::---->");
  sinfo_.bstart_       = std::make_unique< MTFuncSharedInfo::barier_type > (max_threads_ + 1);
  sinfo_.exit_request_ = false;

  threads_.clear ();
  threads_.reserve (max_threads_);

  U3_XLOG_DBG ("CallerImpl::create_threads::" + VTOLOG (max_threads_));
  for (std::uint16_t thread_indx = 0; thread_indx < max_threads_; ++thread_indx)
  {
    threads_.emplace_back (
      ::libs::helpers::thread::generic_thread_funct< CallerImpl >,
      libs::properties::vers::links::mids::mdata2appl,
      this,
      thread_indx);
  }

  U3_ASSERT (threads_.size () == max_threads_);
  U3_XLOG_DBG ("CallerImpl::create_threads::<----");
}


void
CallerImpl::thread_func_impl (const std::uint32_t thread_indx)
{
  ::libs::helpers::thread::set_thread_priority (std::this_thread::get_id (), ::libs::helpers::thread::Priorities::below_normal);

  do
  {
    sinfo_.bstart_->arrive_and_wait ();
    //  check state its not end
    if (sinfo_.exit_request_)
    {
      //  release main thread
      sinfo_.bstart_->arrive_and_wait ();
      break;
    }
    if (!thread_funcs_[thread_indx])
    {
      // release main thread
      sinfo_.bstart_->arrive_and_wait ();
      continue;
    }

    try
    {
      U3_ASSERT (calls_.size () > thread_indx);
      U3_ASSERT (src_heights_.size () > thread_indx);
      thread_funcs_[thread_indx](calls_[thread_indx]);
    }
    catch (boost::exception& excpt)
    {
      U3_XLOG_ERROR ("CallerImpl::thread_func_impl: exception " + std::string (boost::diagnostic_information_what (excpt)));
      U3_ASSERT_SIGNAL_NT ("failed");
    }
    catch (std::exception& excpt)
    {
      U3_XLOG_ERROR ("CallerImpl::thread_func_impl: exception " + std::string (excpt.what ()) + TOLOG (calls_[thread_indx].func_id_) + VTOLOG (thread_indx));
      U3_ASSERT_SIGNAL_NT ("failed");
    }
    catch (...)
    {
      U3_XLOG_ERROR ("CallerImpl::thread_func_impl: exception...");
      U3_ASSERT_SIGNAL_NT ("failed");
    }

    //  release main thread
    sinfo_.bstart_->arrive_and_wait ();
  } while (true);
}


void
CallerImpl::thread_postfunc_impl (std::uint32_t thread_indx)
{
}
}   // namespace libs::optim::mcalls
