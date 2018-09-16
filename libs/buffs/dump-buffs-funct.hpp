#pragma once
/**
\file       dump-buffs-funct.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       12.08.2018.
\copyright  www.uuusoft.com
\project    uuu_buffs
\brief      empty brief
*/

namespace libs { namespace buffs {
/**
\brief      ???
\param[in]  _buffs
\param[in]  _only_filled
*/
inline void
dump (Buffs::craw_ptr _buffs, bool _only_filled)
{
  if (_only_filled && _buffs->get_flag (TypeBuffsFlags::empty))
    {
      return;
    }

  XULOG_INFO ("dump ::libs::buffs::Buffs");
  UASSERT (_buffs);
  XULOG_INFO ("   indx_base_buff=" << _buffs->get_indx_base_buff () << ", empty=" << _buffs->get_flag (TypeBuffsFlags::empty) << ", request_convert2hsl=" << _buffs->get_flag (TypeBuffsFlags::request_convert2hsl));

  _buffs->enum_buffs (
    [_only_filled](const off_buff_type& _indx, const IVideoBuff::cptr& _buff) {
      UASSERT (_buff);
      if (_only_filled && (_buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty) || _buff->get_flag (::utils::dbuffs::TypeFlagsBuff::null)))
        {
          return;
        }
      XULOG_INFO ("   _indx=" << _indx << ":")
      ::utils::dbuffs::video::helpers::dump (_buff.get (), _only_filled);
      return;
    });
  return;
}

}}      // namespace libs::buffs
