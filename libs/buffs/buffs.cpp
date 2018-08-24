//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       buffs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.05.2016
\copyright  www.uuusoft.com
\project    uuu_buffs
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "buffs.hpp"

namespace libs { namespace buffs {

Buffs::Buffs () :
  indx_base_buff_ (utils::dbuffs::video::consts::offs::raw)
{
  flags_.fill (false);
  flags_.set (TypeBuffsFlags::request_convert2hsl, true);
  //flags_.set (TypeBuffsFlags::empty, true);
  set_flag (TypeBuffsFlags::empty, true);
}


Buffs::~Buffs ()
{}

#if 1
void
Buffs::set_indx_base_buff (const off_buff_type& _indx)
{
  indx_base_buff_ = _indx;
  return;
}


off_buff_type
Buffs::get_indx_base_buff () const
{
  return indx_base_buff_;
}
#endif

void
Buffs::reset (bool _only_indxs)
{
  if (!_only_indxs)
    {
      for (auto& _child : childs_)
        {
          auto& _cbuff = _child.second;
          _cbuff->flush ();
        }
    }

  indx_base_buff_ = utils::dbuffs::video::consts::offs::raw;
  set_flag (TypeBuffsFlags::empty, true);
  flags_.set (TypeBuffsFlags::request_convert2hsl, true);
  return;
}


IVideoBuff::raw_ptr
  Buffs::operator[] (const off_buff_type& _indx)
{
  if (_indx == ::utils::dbuffs::video::consts::offs::invalid)
    {
      return nullptr;
    }

  auto& _ret = childs_[_indx];

  if (!_ret)
    {
      auto _ibuff = ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ();
      _ret        = _ibuff->impl ()->get ();
    }
  return _ret.get ();
}


IVideoBuff::craw_ptr
  Buffs::operator[] (const off_buff_type& _indx) const
{
  if (_indx == ::utils::dbuffs::video::consts::offs::invalid)
    {
      return nullptr;
    }

  auto& _ret = childs_[_indx];

  if (!_ret)
    {
      auto _ibuff = ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ();
      _ret        = _ibuff->impl ()->get ();
    }
  return _ret.get ();
}


void
Buffs::set_buff (const off_buff_type& _indx, IVideoBuff::ptr& _buff)
{
  childs_[_indx] = _buff;
  return;
}


void
Buffs::set_flag (const TypeBuffsFlags& _key, bool _val)
{
  if (TypeBuffsFlags::empty != _key)
    {
      flags_.set (_key, _val);
      return;
    }
#if 0
  if (!_val)
    {
      flags_.set (_key, _val);
      return;
    }

  for (auto& _child : childs_)
    {
      auto& _cbuff = _child.second;
      if (!_cbuff)
        {
          continue;
        }

      _cbuff->set_flag (::utils::dbuffs::TypeFlagsBuff::empty, true);
    }

  flags_.set (_key, _val);
#endif

  auto _base_buff = (*this)[get_indx_base_buff ()];
  if (!_base_buff)
    {
      return;
    }

  _base_buff->set_flag (::utils::dbuffs::TypeFlagsBuff::empty, _val);
  return;
}


bool
Buffs::get_flag (const TypeBuffsFlags& _key) const
{
  if (TypeBuffsFlags::empty != _key)
    {
      return flags_.get (_key);
    }

  auto _base_buff = (*this)[get_indx_base_buff ()];
  if (!_base_buff)
    {
      return true;
    }
  return _base_buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty);
}


void
Buffs::enum_buffs (enum_buffs_funct_type _funct) const
{
  for (const auto& _el : childs_)
    {
      _funct (_el.first, _el.second);
    }
  return;
}

}}      // namespace libs::buffs
