/**
\file       link-impl-any-proc.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "link-impl-any-proc.hpp"

namespace libs::ilink::impl::anyproc
{
LinkImplAnyProc::~LinkImplAnyProc ()
{
  U3_CHECK_NT (destroy_int (::libs::link::LinkDestroys::force), "LinkImplAnyProc::~LinkImplAnyProc");
}


auto
LinkImplAnyProc::make_for_create () -> bool
{
  U3_ASSERT_SIGNAL ("failed");
  return false;

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  const bool active_side = ::libs::link::details::ETypeActivity::etaa_active == info_.active_side_ ? true : false;
  U3_ASSERT (active_side);

  remove_names ();

  cmd_send_msgs_.reset (
    new msgs_type (
      boost::interprocess::create_only,
      std::string (info_.id_arg2val_[::libs::link::consts::text::id_name_queue2dest] + ".send").c_str (),
      ::libs::link::consts::max_count_msgs,
      ::libs::link::consts::max_size_msg));

  cmd_recv_msgs_.reset (
    new msgs_type (
      boost::interprocess::create_only,
      std::string (info_.id_arg2val_[::libs::link::consts::text::id_name_queue2dest] + ".recv").c_str (),
      ::libs::link::consts::max_count_msgs,
      ::libs::link::consts::max_size_msg));


  smem_.reset (
    new boost::interprocess::managed_shared_memory (
      boost::interprocess::create_only,
      info_.id_arg2val_[::libs::link::consts::text::id_name_shared_mem].c_str (),
      info_.size_shared_mem_bytes_));

  if (!info_.id_arg2val_[::libs::link::consts::text::id_proc_name].empty ())
  {
    boost::process::context cntx;

    // cntx.stdout_behavior = boost::process::capture_stream ();
    // cntx.stdin_behavior = boost::process::capture_stream ();
    // cntx.environment = boost::process::self::get_environment ();

    const std::string name_sync = info_.id_arg2val_[::libs::link::consts::text::id_sync_init_event];
    const std::string name_flag = name_sync + ".flag";
    const std::string name_cond = name_sync + ".cond";

    boost::interprocess::named_mutex                                     sync_mtx (boost::interprocess::create_only, name_sync.c_str ());
    boost::interprocess::scoped_lock< boost::interprocess::named_mutex > synclock (sync_mtx);
    bool*                                                                pflag = smem_->construct< bool > (name_flag.c_str ()) (true);
    boost::interprocess::named_condition                                 sync_cond (boost::interprocess::create_only, name_cond.c_str ());

    do
    {
      loader_.load (
        info_.run_as_,
        &info_,
        info_.id_arg2val_[::libs::link::consts::text::id_proc_name],
        info_.id_arg2val_[::libs::link::consts::text::id_lib_name],
        info_.args_,
        cntx);

      // sync_cond.notify_all();
      sync_cond.wait (synclock);
    } while (*pflag);
  }

  const bool proc_name_exist = info_.id_arg2val_[::libs::link::consts::text::id_proc_name].empty () ? false : true;

  return proc_name_exist ? (loader_.is_load () ? true : false) : true;
#endif
}


auto
LinkImplAnyProc::make_for_creation () -> bool
{
  U3_ASSERT_SIGNAL ("failed");
  return false;

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  const bool        active_side = ::libs::link::details::ETypeActivity::etaa_active == info_.active_side_ ? true : false;
  const std::string send_msg_id = info_.id_arg2val_[::libs::link::consts::text::id_name_queue2dest] + (active_side ? ".send" : ".recv");

  cmd_send_msgs_.reset (
    new boost::interprocess::message_queue (boost::interprocess::open_only, send_msg_id.c_str ()));

  const std::string recv_msg_id = info_.id_arg2val_[::libs::link::consts::text::id_name_queue2dest] + (active_side ? ".recv" : ".send");

  cmd_recv_msgs_.reset (
    new boost::interprocess::message_queue (
      boost::interprocess::open_only,
      recv_msg_id.c_str ()));

  smem_.reset (
    new boost::interprocess::managed_shared_memory (
      boost::interprocess::open_only,
      info_.id_arg2val_[::libs::link::consts::text::id_name_shared_mem].c_str ()));

  const std::string name_sync = info_.id_arg2val_[::libs::link::consts::text::id_sync_init_event];
  const std::string name_flag = name_sync + ".flag";
  const std::string name_cond = name_sync + ".cond";

  boost::interprocess::named_mutex                                     sync_mtx (boost::interprocess::open_or_create, name_sync.c_str ());
  boost::interprocess::scoped_lock< boost::interprocess::named_mutex > synclock (sync_mtx);
  boost::interprocess::named_condition                                 sync_cond (boost::interprocess::open_or_create, name_cond.c_str ());

  bool* pflag = smem_->find_or_construct< bool > (name_flag.c_str ()) (false);
  ? ? ? destproy requared

          * pflag = false;
  sync_cond.notify_all ();

  return true;
#endif
}


void
LinkImplAnyProc::remove_names ()
{
  volatile ::libs::utility::hboost::NameRemover remover_msgs (info_.id_arg2val_[::libs::link::consts::text::id_name_queue2dest]);
  volatile ::libs::utility::hboost::NameRemover remover_send_msgs (info_.id_arg2val_[::libs::link::consts::text::id_name_queue2dest] + ".send");
  volatile ::libs::utility::hboost::NameRemover remover_recv_msgs (info_.id_arg2val_[::libs::link::consts::text::id_name_queue2dest] + ".recv");
  volatile ::libs::utility::hboost::NameRemover remover_shared_mem (info_.id_arg2val_[::libs::link::consts::text::id_name_shared_mem]);
  volatile ::libs::utility::hboost::NameRemover remover_sync_init_event (info_.id_arg2val_[::libs::link::consts::text::id_sync_init_event]);
  volatile ::libs::utility::hboost::NameRemover remover_sync_init_event_flag (info_.id_arg2val_[::libs::link::consts::text::id_sync_init_event] + ".flag");
  volatile ::libs::utility::hboost::NameRemover remover_sync_init_event_cond (info_.id_arg2val_[::libs::link::consts::text::id_sync_init_event] + ".cond");
}
}   // namespace libs::ilink::impl::anyproc
