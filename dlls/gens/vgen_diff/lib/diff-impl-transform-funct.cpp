//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       diff-impl-transform-funct.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vgen_diff_lib
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "diff-impl.hpp"

namespace dlls { namespace gens { namespace vgen_diff { namespace lib {

void
DiffImpl::itransform (Buffs& _pbuffs)
{
  UASSERT (props_);
  auto _ibuff = ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ()->impl ();

  for (const TBuff2Info& _b2b : props_->diffs_)
    {
      const off_buff_type _sindx = _b2b.first;
      const off_buff_type _dindx = _b2b.second.bindx_diff_;
      IVideoBuff::raw_ptr _psrc  = _pbuffs[_sindx];

      if (!_psrc || _psrc->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
        {
          continue;
        }

      ::libs::buffs::alloc_buff_by_indx (&_pbuffs, _dindx, _psrc);

      bool                _copy2prev = true;
      const bool          _copy2temp = _sindx == _dindx ? true : false;
      IVideoBuff::raw_ptr _pdst      = _pbuffs[_dindx];
      IVideoBuff::ptr&    _prevbuff  = indx2prev_buff_[_sindx];

      _pdst->clone (_psrc, 100.0f);
      _prevbuff  = _prevbuff ? _prevbuff : _ibuff->get ();
      temp_buff_ = temp_buff_ ? temp_buff_ : _ibuff->get ();

      if (_prevbuff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty) || !utils::dbuffs::video::helpers::is_equal_dim (*_prevbuff, *_psrc))
        {
          _prevbuff->clone (_psrc, 100.0f);
          _copy2prev = false;
        }

      if (_copy2temp)
        {
          temp_buff_->clone (_psrc, 100.0f);
        }

      make_diff_buff (*_prevbuff, *_pdst);

      if (_copy2prev)
        {
          _prevbuff->clone (_copy2temp ? temp_buff_.get () : _psrc, 100.0f);
        }

      if (_b2b.second.op_.enable_)
        {
          bin_buff (_b2b.second.op_.bound_filling_, _b2b.second.op_.val_filling_, _pdst);
        }
    }
  return;
}

}}}}      // namespace dlls::gens::vgen_diff::lib
