//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       transform_functs.cpp
\brief      Filter for correct image
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_dlls_vec2image
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace utils { namespace vec2image1 {

void
Filter::itransform ()
{
  for (BuffEventInfo& _b2b : finfo_.rprops_->buffs_)
    {
      _b2b.check ();

      IVideoBuff::raw_ptr _psrc = (*pbuff_)[_b2b.indx_sbuff_];

      if (!_psrc || _psrc->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
        {
          continue;
        }

      ::libs::buffs::alloc_buff_by_indx (pbuff_, _b2b.indx_dbuff_, _psrc);

      IVideoBuff::raw_ptr _pdst = (*pbuff_)[_b2b.indx_dbuff_];

      std::size_t _dwidth  = _psrc->get_dim_var (::utils::dbuffs::video::TypeDimVar::width) * _b2b.size_block_;
      std::size_t _dheight = _psrc->get_dim_var (::utils::dbuffs::video::TypeDimVar::height) * _b2b.size_block_;

      _pdst->balloc (::utils::dbuffs::video::AllocBuffInfo (_dwidth, _dheight, 0, ::libs::helpers::uids::minor::y16));

      make_vec2buff (_b2b, *_psrc, *_pdst);

      _pdst->set_mem_var (::utils::dbuffs::TypeMemVar::size_data, _pdst->get_dim_var (::utils::dbuffs::video::TypeDimVar::stride) * _pdst->get_dim_var (::utils::dbuffs::video::TypeDimVar::height));
    }
  return;
}

}}}      // namespace dlls::utils::vec2image1
