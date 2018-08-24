/**
\file       imem-buff.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       11.08.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "imem-buff.hpp"

namespace utils { namespace dbuffs {

IMemBuff::IMemBuff ()
{}


IMemBuff::~IMemBuff ()
{}


void
IMemBuff::ialloc (const mem_type& _size)
{
  if (!raw_)
    {
      auto _imem = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ();
      raw_       = _imem->alloc (_size);
    }
  if (raw_->get_buff_size () < _size)
    {
      raw_->resize (_size);
    }
  UASSERT (raw_);      //“.к. не произошло исключени€, то тут всегда правильный указатель.
  return;
}


void
IMemBuff::flush ()
{
  mem_vars_.set (TypeMemVar::size_data, 0);
  return;
}


void
IMemBuff::set_mem_var_int (const TypeMemVar& _type, mem_type _val)
{
  switch (_type)
    {
    case TypeMemVar::size_data:
      if (_val > 0)
        {
          CHECK_STATE (_val || raw_, "failed, try set size_data to empty raw_");
          CHECK_STATE (_val <= raw_->get_buff_size (), "failed, size large buff, " << _val << ", " << raw_->get_buff_size ());
        }
      break;
    case TypeMemVar::offset_data:
      CHECK_STATE (_val < (*this)[TypeMemVar::size_buffer] || 0 == _val, "failed, offset large size, " << _val << ">=" << (*this)[TypeMemVar::size_buffer]);
      break;
    case TypeMemVar::size_buffer:
      XULOG_ERROR ("try set size_buffer, " << _val);
      return;
    default:
      break;
    }

  mem_vars_.set (_type, _val);
  return;
}


IMemBuff::mem_type
IMemBuff::get_mem_var_int (const ::utils::dbuffs::TypeMemVar& _type) const
{
  switch (_type)
    {
    case TypeMemVar::size_buffer:
      return raw_ ? raw_->get_buff_size () : 0;
    default:
      break;
    }
  return mem_vars_.get (_type);
}


unsigned char*
IMemBuff::get_buff_int ()
{
  UASSERT (raw_);
  return raw_->get ();
}


const unsigned char*
IMemBuff::get_cbuff_int () const
{
  UASSERT (raw_);
  return raw_->get ();
}


void
IMemBuff::clone_int (IBuff::craw_ptr _isrc, float _percent)
{
  auto _src = dynamic_cast<IMemBuff::craw_ptr> (_isrc);
  UASSERT (_src);
  if (this == _src)
    {
      XULOG_WARNING ("try clone itself, 0x" << std::hex << this);
      return;
    }

  mem_vars_.set (TypeMemVar::offset_data, (*_src)[TypeMemVar::offset_data]);
  mem_vars_.set (TypeMemVar::size_buffer, (*_src)[TypeMemVar::size_buffer]);
  mem_vars_.set (TypeMemVar::size_data, (*_src)[TypeMemVar::size_data]);

  ialloc ((*_src)[TypeMemVar::size_buffer]);

  if (_percent <= 0.0f)
    {
      //  копировать нечего.
      mem_vars_.set (TypeMemVar::size_data, 0);
      return;
    }

  ::libs::helpers::mem::acopy (_src->get_cbuff (), get_buff (), (*_src)[TypeMemVar::size_buffer]);
  return;
}


void
IMemBuff::swap_int (IBuff& _isrc)
{
  IMemBuff& _src = dynamic_cast<IMemBuff&> (_isrc);
  if (this == &_src)
    {
      XULOG_WARNING ("try swap itself, 0x" << std::hex << this);
      return;
    }

  std::swap (raw_, _src.raw_);
  std::swap (mem_vars_, _src.mem_vars_);
  return;
}

}}      // namespace utils::dbuffs
