//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       create-info.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "create-info.hpp"

namespace libs { namespace link {

CreateInfo::CreateInfo () :
  run_as_ (details::RunCodeType::usual),
  pt2pt_ (details::LinkModulesType::gui),
  size_shared_mem_bytes_ (consts::size_shared_mem_bytes)
{}


CreateInfo::CreateInfo (
  const details::RunCodeType&     _run_as,
  const std::string&              _name_proc,
  const std::string&              _name_lib,
  const std::string&              _company_name,
  const std::string&              _appl_name,
  const std::string&              _subsys_name,
  const details::LinkModulesType& _type,
  int                             _size_shared_mem_bytes) :

  run_as_ (_run_as),
  pt2pt_ (_type),
  size_shared_mem_bytes_ (_size_shared_mem_bytes)
{
  UASSERT (!_company_name.empty ());
  UASSERT (!_appl_name.empty ());
  UASSERT (!_subsys_name.empty ());
  UASSERT (size_shared_mem_bytes_ >= 1024 * 1024);

  id2val_.insert (std::pair<std::string, std::string> (consts::text::id_company_name, _company_name));
  id2val_.insert (std::pair<std::string, std::string> (consts::text::id_appl_name, _appl_name));
  id2val_.insert (std::pair<std::string, std::string> (consts::text::id_subsys_name, _subsys_name));
  id2val_.insert (std::pair<std::string, std::string> (consts::text::id_proc_name, _name_proc));

  if (!_name_lib.empty ())
    {
      id2val_.insert (std::pair<std::string, std::string> (consts::text::id_lib_name, _name_lib));
    }

  const std::string _sync_init_event = get_prefix () + ".sync_init_event";
  id2val_.insert (std::pair<std::string, std::string> (consts::text::id_sync_init_event, _sync_init_event));

  const std::string _msg2dest        = get_prefix () + ".msgs";
  const std::string _name_shared_mem = get_prefix () + ".shared_mem";

  UASSERT (!_msg2dest.empty ());
  UASSERT (!_name_shared_mem.empty ());

  args_.reserve (64);

  id2val_.insert (std::pair<std::string, std::string> (consts::text::id_name_queue2dest, _msg2dest));
  //id2val_.insert( std::pair<std::string, std::string>( consts::text::id_name_queue2source, _msg2source ) );
  id2val_.insert (std::pair<std::string, std::string> (consts::text::id_name_shared_mem, _name_shared_mem));

  if (!_msg2dest.empty () && !_name_shared_mem.empty ())
    {
      args_.push_back (make_arg (consts::text::id_company_name, _company_name));
      args_.push_back (make_arg (consts::text::id_appl_name, _appl_name));
      args_.push_back (make_arg (consts::text::id_subsys_name, _subsys_name));
      args_.push_back (make_arg (consts::text::id_sync_init_event, _sync_init_event));

      if (!_name_lib.empty ())
        {
          args_.push_back (make_arg (consts::text::id_lib_name, _name_lib));
        }
    }

  return;
}


CreateInfo::~CreateInfo ()
{}


void
CreateInfo::check () const
{
  CHECK_STATE (!args_.empty (), "failed, check args");
  return;
}


std::string
CreateInfo::make_arg (const std::string& _id, const std::string& _val)
{
  UASSERT (!_id.empty ());
  UASSERT (!_val.empty ());
  const std::string _ret (std::string ("--") + _id + std::string ("=") + _val);
  return _ret;
}


std::string
CreateInfo::get_prefix () const
{
  std::string _ret;
  _ret.reserve (256);

  _ret += id2val_[consts::text::id_company_name];
  _ret += ".";
  _ret += id2val_[consts::text::id_appl_name];
  _ret += ".";
  _ret += id2val_[consts::text::id_subsys_name];
  _ret += ".";
  _ret += ::to_str (UUU_ICAST_INT (pt2pt_));
  _ret += ".";
  _ret += "id_";
  _ret += "0";
  return _ret;
}


bool
CreateInfo::operator< (const CreateInfo& _op) const
{
#if 0
    if ( create_side_ < _op.create_side_ )
    {
      return true;
    }
#endif
  if (pt2pt_ < _op.pt2pt_)
    {
      return true;
    }
  return args_ < _op.args_;
}


bool
CreateInfo::operator== (const CreateInfo& _op) const
{
  const bool _part1 = args_ == _op.args_;
  const bool _part2 = id2val_ == _op.id2val_;
  const bool _part3 = pt2pt_ == _op.pt2pt_;

  //return _part1 && _part2 && _part3 && ( create_side_ == _op.create_side_ );
  return _part1 && _part2 && _part3;
}

}}      // namespace libs::link
