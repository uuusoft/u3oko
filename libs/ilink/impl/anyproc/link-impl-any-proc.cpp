//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       link-impl-any-proc.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes.hpp"
#include "link-impl-any-proc.hpp"

namespace libs { namespace ilink { namespace impl { namespace anyproc {

namespace bip = boost::interprocess;


LinkImplAnyProc::LinkImplAnyProc ()
{}


LinkImplAnyProc::~LinkImplAnyProc ()
{
  CHECK_CALL_NO_THROW (destroy_int (DestroyLinkType::force));

  return;
}


bool
LinkImplAnyProc::make_for_create ()
{
  UASSERT_SIGNAL ("failed");
  return false;
#if 0
    const bool _active_side = ::libs::link::details::ETypeActivity::etaa_active == info_.active_side_ ? true : false;

    UASSERT( _active_side );
      
    remove_names ();

    XULOG_TRACE ("uuu_soft::helpers::CHelper::create::create side::cmd_send_msgs_.reset", "uuu_appl_tag");
    XULOG_TRACE (info_.id2val_[consts::id_name_queue2dest].c_str (), "uuu_appl_tag");

    cmd_send_msgs_.reset (
      new msgs_type (
        bip::create_only,
        std::string (info_.id2val_[::libs::link::consts::text::id_name_queue2dest] + ".send").c_str (),
        ::libs::link::consts::max_count_msgs,
        ::libs::link::consts::max_size_msg
      )
    );

    cmd_recv_msgs_.reset (
      new msgs_type (
        bip::create_only,
        std::string (info_.id2val_[::libs::link::consts::text::id_name_queue2dest] + ".recv").c_str (),
        ::libs::link::consts::max_count_msgs,
        ::libs::link::consts::max_size_msg
      )
    );

    XULOG_TRACE ("uuu_soft::helpers::CHelper::create::create side::smem_.reset", "uuu_appl_tag");
    XULOG_TRACE (info_.id2val_[consts::id_name_shared_mem].c_str (), "uuu_appl_tag");

    smem_.reset (
      new bip::managed_shared_memory (
      bip::create_only,
      info_.id2val_[::libs::link::consts::text::id_name_shared_mem].c_str (),
      info_.size_shared_mem_bytes_
      )
    );

    if ( !info_.id2val_[::libs::link::consts::text::id_proc_name].empty () )
    {
      boost::process::context _cntx;

      //_cntx.stdout_behavior = boost::process::capture_stream ();
      //_cntx.stdin_behavior = boost::process::capture_stream ();
      //_cntx.environment = boost::process::self::get_environment ();

      const std::string _name_sync = info_.id2val_[::libs::link::consts::text::id_sync_init_event];
      const std::string _name_flag = _name_sync + ".flag";
      const std::string _name_cond = _name_sync + ".cond";

      bip::named_mutex                    _sync_mtx (bip::create_only, _name_sync.c_str ());
      bip::scoped_lock<bip::named_mutex>  _sync_grd (_sync_mtx);
      bool*                               _pflag = smem_->construct<bool> (_name_flag.c_str ())(true);
      bip::named_condition                _sync_cond (bip::create_only, _name_cond.c_str ());

      do
      {
        loader_.load (
          info_.run_as_,
          &info_,
          info_.id2val_[::libs::link::consts::text::id_proc_name],
          info_.id2val_[::libs::link::consts::text::id_lib_name],
          info_.args_,
          _cntx );

        //_sync_cond.notify_all();
        _sync_cond.wait (_sync_grd);
      }
      while (*_pflag);
    }

    const bool _proc_name_exist = info_.id2val_[ ::libs::link::consts::text::id_proc_name].empty() ? false : true;

    return _proc_name_exist ? ( loader_.is_load() ? true : false ) : true;
#endif
}


bool
LinkImplAnyProc::make_for_creation ()
{
  UASSERT_SIGNAL ("failed");
  return false;
#if 0
    const bool        _active_side = ::libs::link::details::ETypeActivity::etaa_active == info_.active_side_ ? true : false;
    const std::string _send_msg_id = info_.id2val_[::libs::link::consts::text::id_name_queue2dest] + (_active_side ? ".send" : ".recv");

    cmd_send_msgs_.reset (
      new bip::message_queue ( bip::open_only, _send_msg_id.c_str () )
    );

    const std::string _recv_msg_id = info_.id2val_[::libs::link::consts::text::id_name_queue2dest] + (_active_side ? ".recv" : ".send");

    cmd_recv_msgs_.reset (
      new bip::message_queue (
        bip::open_only,
        _recv_msg_id.c_str ()
      )
    );

    XULOG_TRACE ("uuu_soft::helpers::CHelper::create::client side::smem_.reset", "uuu_appl_tag");
    XULOG_TRACE (info_.id2val_[consts::id_name_shared_mem].c_str (), "uuu_appl_tag");

    smem_.reset (
      new bip::managed_shared_memory (
        bip::open_only,
        info_.id2val_[::libs::link::consts::text::id_name_shared_mem].c_str ()
      )
    );

    const std::string _name_sync = info_.id2val_[::libs::link::consts::text::id_sync_init_event];
    const std::string _name_flag = _name_sync + ".flag";
    const std::string _name_cond = _name_sync + ".cond";

    bip::named_mutex          _sync_mtx (bip::open_or_create, _name_sync.c_str ());
    bip::scoped_lock<bip::named_mutex>  _sync_grd (_sync_mtx);
    bip::named_condition        _sync_cond (bip::open_or_create, _name_cond.c_str ());

    bool* _pflag = smem_->find_or_construct<bool> (_name_flag.c_str ())(false);

    *_pflag = false;
    _sync_cond.notify_all ();

    return true;
#endif
}


void
LinkImplAnyProc::remove_names ()
{
  volatile NameRemover _remover_msgs (info_.id2val_[::libs::link::consts::text::id_name_queue2dest]);
  volatile NameRemover _remover_send_msgs (info_.id2val_[::libs::link::consts::text::id_name_queue2dest] + ".send");
  volatile NameRemover _remover_recv_msgs (info_.id2val_[::libs::link::consts::text::id_name_queue2dest] + ".recv");
  volatile NameRemover _remover_shared_mem (info_.id2val_[::libs::link::consts::text::id_name_shared_mem]);
  volatile NameRemover _remover_sync_init_event (info_.id2val_[::libs::link::consts::text::id_sync_init_event]);
  volatile NameRemover _remover_sync_init_event_flag (info_.id2val_[::libs::link::consts::text::id_sync_init_event] + ".flag");
  volatile NameRemover _remover_sync_init_event_cond (info_.id2val_[::libs::link::consts::text::id_sync_init_event] + ".cond");
  return;
}

}}}}      // namespace libs::ilink::impl::anyproc
