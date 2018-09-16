//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mops-impl-transform-functs.cpp
\brief      Реализация основной функции преобразования фильтра МО.
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_vgen_mops_lib
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "morph-operator.hpp"
#include "mops-impl.hpp"

namespace dlls { namespace gens { namespace vgen_mops { namespace lib {

void
MopsImpl::itransform (Buffs& _buffs)
{
  for (const off_buff2info_type& _b2b : props_->diffs_)
    {
      const off_buff_type _sindx = _b2b.first;
      const off_buff_type _dindx = _b2b.second.bindx_diff_;
      IVideoBuff::raw_ptr _psrc  = _buffs[_sindx];

      if (!_psrc || _psrc->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
        {
          continue;
        }

      ::libs::buffs::alloc_buff_by_indx (&_buffs, _dindx, _psrc);

      IVideoBuff::raw_ptr _pdst = _buffs[_dindx];
      if (_dindx != _sindx)
        {
          _pdst->clone (_psrc, 100.0f);
        }

      for (const auto& _op : _b2b.second.ops_)
        {
          //  бинаризация в 0.1 как подготовка буфера для выполения морфологической операции.
          bin_buff (_b2b, _op.bound_filling_, 1, _pdst);
          //  собственно производим МО над подготовленным буфером.
          morph_helper_.applay_operation2buff (_op, &_buffs, _pdst);
        }
      //  Вспомогательная бинаризация для дальнейшей обработки буфера.
      bin_buff (_b2b, 0, 255, _pdst);
    }
  return;
}

}}}}      // namespace dlls::gens::vgen_mops::lib
