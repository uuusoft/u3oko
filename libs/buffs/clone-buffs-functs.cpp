//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       clone-buffs-functs.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_buffs
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "buffs.hpp"

namespace libs { namespace buffs {

void
Buffs::swap (Buffs& _src)
{
  if (this == &_src)
    {
      UASSERT_SIGNAL ("failed");
      return;
    }

  std::swap (childs_, _src.childs_);
  //std::swap( ichilds_, _src.ichilds_ );
  std::swap (flags_, _src.flags_);
  std::swap (indx_base_buff_, _src.indx_base_buff_);
  return;
}


void
Buffs::clone (const Buffs& _src)
{
  if (&_src == this)
    {
      UASSERT_SIGNAL ("failed");
      return;
    }

  auto _ibuff = ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ();

  childs_.clear ();

  for (auto& _schild : _src.childs_)
    {
      auto& _dchild = childs_[_schild.first];
      if (!_schild.second)
        {
          continue;
        }

      _dchild = _ibuff->impl ()->get ();
      _dchild->clone (_schild.second.get (), 100.0f);
    }

  //ichilds_ = _src.ichilds_;
  flags_          = _src.flags_;
  indx_base_buff_ = _src.indx_base_buff_;
  return;
}

}}      // namespace libs::buffs
