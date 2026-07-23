/**
\file       create-info.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_link
*/
#include "_make/libs-link-includes_int.hpp"
#include "create-info.hpp"

namespace libs::link::helpers
{
auto
make_arg (const std::string& id, const std::string& val) -> std::string
{
  U3_ASSERT (!id.empty ());
  U3_ASSERT (!val.empty ());
  const std::string ret (std::string ("--") + id + std::string ("=") + val);
  return ret;
}


auto
get_module_links (const CreateInfo& info) -> details::ModuleLinks
{
  return std::get< details::ModuleLinks > (info.link_params_[consts::text::id_module_links]);
}


auto
get_code_runs (const CreateInfo& info) -> details::CodeRuns
{
  return std::get< details::CodeRuns > (info.link_params_[consts::text::id_code_runs]);
}


auto
get_server_side (const CreateInfo& info) -> bool
{
  return std::get< bool > (info.link_params_[consts::text::id_server_side]);
}
}   // namespace libs::link::helpers


namespace libs::link
{
CreateInfo::CreateInfo (const vals_type& vals) :
  link_params_ { { { consts::text::id_company_name, "u3soft" },
                   { consts::text::id_proc_name, "" },
                   { consts::text::id_lib_name, "u3-lib-name-wtf" },
                   { consts::text::id_appl_name, "u3-appl-name-wtf" },
                   { consts::text::id_service_name, "" },
                   { consts::text::id_size_shared_mem, consts::size_shared_mem_bytes },
                   { consts::text::id_module_links, details::ModuleLinks::gui },
                   { consts::text::id_code_runs, details::CodeRuns::usual },
                   { consts::text::id_server_side, false } } }
{
  U3_XLOG_DEV ("CreateInfo::CreateInfo:---->" + VTOLOG (link_params_.size ()) + VTOLOG (vals.size ()));
  link_params_.reserve (link_params_.size () + vals.size ());
  for (const auto& [key, val] : vals)
  {
    link_params_.insert_or_assign (key, val);
  }

  const std::string sync_init_event = get_prefix () + ".sync_init_event";
  link_params_.insert_or_assign (consts::text::id_sync_init_event, sync_init_event);

  const std::string msg2dest        = get_prefix () + ".msgs";
  const std::string name_shared_mem = get_prefix () + ".shared_mem";

  link_params_.insert_or_assign (consts::text::id_name_queue2dest, msg2dest);
  link_params_.insert_or_assign (consts::text::id_name_shared_mem, name_shared_mem);
  U3_XLOG_DEV ("CreateInfo::CreateInfo:<----" + VTOLOG (link_params_.size ()) + VTOLOG (vals.size ()));
}


void
CreateInfo::check () const
{
  // U3_CHECK (!args_.empty (), "check args");
}


auto
CreateInfo::get_prefix () const -> std::string
{
  std::string ret;
  ret.reserve (256);

  ret += std::get< std::string > (link_params_[consts::text::id_company_name]);
  ret += ".";
  ret += std::get< std::string > (link_params_[consts::text::id_appl_name]);
  ret += ".";
  ret += to_string (std::get< details::ModuleLinks > (link_params_[consts::text::id_module_links]));
  ret += ".";
  ret += "id_";
  ret += "0";
  return ret;
}
}   // namespace libs::link
