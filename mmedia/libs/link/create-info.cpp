/**
\file       create-info.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_link
*/
#include "libs-link-includes_int.hpp"
#include "create-info.hpp"

namespace libs::link
{
CreateInfo::CreateInfo () :
  run_as_ (details::CodeRuns::usual),
  pt2pt_ (details::ModuleLinks::gui),
  size_shared_mem_bytes_ (consts::size_shared_mem_bytes)
{
}


CreateInfo::CreateInfo (
  const details::CodeRuns&    run_as,
  const std::string&          name_proc,
  const std::string&          name_lib,
  const std::string&          company_name,
  const std::string&          appl_name,
  const std::string&          subsys_name,
  const details::ModuleLinks& type,
  std::int32_t                size_shared_mem_bytes) :

  run_as_ (run_as),
  pt2pt_ (type),
  size_shared_mem_bytes_ (size_shared_mem_bytes)
{
  U3_ASSERT (!company_name.empty ());
  U3_ASSERT (!appl_name.empty ());
  U3_ASSERT (!subsys_name.empty ());
  U3_ASSERT (size_shared_mem_bytes_ >= 1024 * 1024);

  id_arg2val_.insert (std::pair< std::string, std::string > (consts::text::id_company_name, company_name));
  id_arg2val_.insert (std::pair< std::string, std::string > (consts::text::id_appl_name, appl_name));
  id_arg2val_.insert (std::pair< std::string, std::string > (consts::text::id_subsys_name, subsys_name));
  id_arg2val_.insert (std::pair< std::string, std::string > (consts::text::id_proc_name, name_proc));

  if (!name_lib.empty ())
  {
    id_arg2val_.insert (std::pair< std::string, std::string > (consts::text::id_lib_name, name_lib));
  }

  const std::string sync_init_event = get_prefix () + ".sync_init_event";
  id_arg2val_.insert (std::pair< std::string, std::string > (consts::text::id_sync_init_event, sync_init_event));

  const std::string msg2dest        = get_prefix () + ".msgs";
  const std::string name_shared_mem = get_prefix () + ".shared_mem";

  U3_XLOG_DEV (TOLOG (msg2dest));
  U3_ASSERT (!msg2dest.empty ());
  U3_ASSERT (!name_shared_mem.empty ());

  args_.reserve (64);

  id_arg2val_.insert (std::pair< std::string, std::string > (consts::text::id_name_queue2dest, msg2dest));
  id_arg2val_.insert (std::pair< std::string, std::string > (consts::text::id_name_shared_mem, name_shared_mem));
  // id_arg2val_.insert( std::pair<std::string, std::string>( consts::text::id_name_queue2source, msg2source ) );

  if (!msg2dest.empty () && !name_shared_mem.empty ())
  {
    args_.push_back (make_arg (consts::text::id_company_name, company_name));
    args_.push_back (make_arg (consts::text::id_appl_name, appl_name));
    args_.push_back (make_arg (consts::text::id_subsys_name, subsys_name));
    args_.push_back (make_arg (consts::text::id_sync_init_event, sync_init_event));

    if (!name_lib.empty ())
    {
      args_.push_back (make_arg (consts::text::id_lib_name, name_lib));
    }
  }
}


void
CreateInfo::check () const
{
  U3_CHECK (!args_.empty (), "check args");
}


std::string
CreateInfo::make_arg (const std::string& id, const std::string& val)
{
  U3_ASSERT (!id.empty ());
  U3_ASSERT (!val.empty ());
  const std::string ret (std::string ("--") + id + std::string ("=") + val);
  return ret;
}


std::string
CreateInfo::get_prefix () const
{
  std::string ret;
  ret.reserve (256);

  ret += id_arg2val_[consts::text::id_company_name];
  ret += ".";
  ret += id_arg2val_[consts::text::id_appl_name];
  ret += ".";
  ret += id_arg2val_[consts::text::id_subsys_name];
  ret += ".";
  ret += std::to_string (U3_CAST_UINT32_FORCE (pt2pt_));
  ret += ".";
  ret += "id_";
  ret += "0";
  return ret;
}


bool
CreateInfo::operator< (const CreateInfo& op) const
{
#ifdef U3_FAKE_DISABLE
  if (create_side_ < op.create_side_)
  {
    return true;
  }
#endif
  if (pt2pt_ < op.pt2pt_)
  {
    return true;
  }
  return args_ < op.args_;
}


bool
CreateInfo::operator== (const CreateInfo& op) const
{
  const bool part1 = args_ == op.args_;
  const bool part2 = id_arg2val_ == op.id_arg2val_;
  const bool part3 = pt2pt_ == op.pt2pt_;
  return part1 && part2 && part3;
}


std::string
to_string (const CreateInfo& val)
{
  std::string res;
  res += "CreateInfo[" + to_string (val.run_as_) + " " + to_string (val.pt2pt_) + " " + std::to_string (val.size_shared_mem_bytes_) + "]";
  return res;
}
}   // namespace libs::link
