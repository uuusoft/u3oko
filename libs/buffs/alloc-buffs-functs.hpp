#pragma once
/**
\file       alloc-buffs-functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       15.08.2018.
\copyright  www.uuusoft.com
\project    uuu_buffs
\brief      empty brief
*/

namespace libs { namespace buffs {
/**
\brief          Функция создает буфер в списке по его индексу.
\param[in, out] _buffs  список буферов.
\param[in]      _off_buff_type  индекс-позиция-тип буфера, который будет создан.
\param[in]      _src  буфер-источник параметров для создаваемого буфера.
*/
inline void
alloc_buff_by_indx (Buffs::raw_ptr _buffs, const off_buff_type& _indx, IVideoBuff::raw_ptr _src)
{
  UASSERT (_buffs);
  UASSERT (_buffs);
  IVideoBuff::raw_ptr _nbuff = (*_buffs)[_indx];
  UASSERT (_nbuff);

  if (!_src || _src->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      XULOG_WARNING ("failed, try alloc buff from empty buff, " << _indx);
      return;
    }

  if (_nbuff == _src)
    {
      return;
    }

  if (!utils::dbuffs::video::helpers::is_equal_dim (*_nbuff, *_src))
    {
      _nbuff->clone (_src, 0.0f);
    }
  return;
}

}}      // namespace libs::buffs
