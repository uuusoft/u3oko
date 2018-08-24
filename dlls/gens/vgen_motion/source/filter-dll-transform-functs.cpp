//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-transform-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vgd_motion
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace gens { namespace vgen_motion {

void
fill_search_vecs (BuffEventInfo& _b2b)
{
  _b2b.search_vecs_.reserve (_b2b.size_search_ * _b2b.size_search_);
  _b2b.search_vecs_.clear ();

  for (short _indxy = 0; _indxy < 2 * _b2b.size_search_; ++_indxy)
    {
      for (short _indxx = 0; _indxx < 2 * _b2b.size_search_; ++_indxx)
        {
          const char _aindxx = UUU_ICAST_CHAR (_indxx - _b2b.size_search_);
          const char _aindxy = UUU_ICAST_CHAR (_indxy - _b2b.size_search_);

          _b2b.search_vecs_.push_back (std::pair<char, char> (_aindxx, _aindxy));
        }
    }

  //  переупорядочиваем вектора по дистанции от центра.
  {
    std::vector<std::pair<char, char>> _temp;

    _temp.swap (_b2b.search_vecs_);

    _b2b.search_vecs_.reserve (_b2b.size_search_ * _b2b.size_search_);
    _b2b.search_vecs_.clear ();

    for (std::size_t _rad = 0; _rad <= 2 * UUU_ICAST_SIZE_T (_b2b.size_search_); ++_rad)
      {
        std::copy_if (
          _temp.begin (),
          _temp.end (),
          std::back_inserter (_b2b.search_vecs_),
          [_rad](std::pair<char, char>& _val) { return _rad == UUU_ICAST_SIZE_T (std::abs (_val.first) + std::abs (_val.second)); });
      }
  }

  return;
}


void
Filter::itransform ()
{
  for (BuffEventInfo& _b2b : finfo_.rprops_->buffs_)
    {
      _b2b.check ();

      if (_b2b.search_vecs_.empty ())
        {
          fill_search_vecs (_b2b);
        }

      IVideoBuff::raw_ptr _pcur_src = (*pbuff_)[_b2b.indx_sbuff_];

      if (!_pcur_src || _pcur_src->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
        {
          continue;
        }

      ::libs::buffs::alloc_buff_by_indx (pbuff_, _b2b.indx_dbuff_, _pcur_src);

      IVideoBuff::raw_ptr _pdst = (*pbuff_)[_b2b.indx_dbuff_];

      std::size_t _dwidth  = _pcur_src->get_dim_var (::utils::dbuffs::video::TypeDimVar::width) / _b2b.size_block_;
      std::size_t _dheight = _pcur_src->get_dim_var (::utils::dbuffs::video::TypeDimVar::height) / _b2b.size_block_;

      _pdst->balloc (
        ::utils::dbuffs::video::AllocBuffInfo (
          _dwidth,
          _dheight,
          0,
          ::libs::helpers::uids::minor::y16,
          utils::dbuffs::video::TypeCheckDim::disabled_check));

      IVideoBuff::ptr& _prevbuff = indx2prev_buff_[_b2b.indx_sbuff_];

      if (!_prevbuff)
        {
          auto _ibuff = ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ()->impl ();
          _prevbuff   = _ibuff->get ();
        }

      bool _req_copy2prev = true;

      if (_prevbuff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty) || !utils::dbuffs::video::helpers::is_equal_dim (*_prevbuff, *_pcur_src))
        {
          _prevbuff->clone (_pcur_src, 100.0f);

          _req_copy2prev = false;
        }

      make_motion_est_buff (_b2b, *_pcur_src, *_prevbuff, *_pdst);

      _prevbuff->clone (_pcur_src, 100.0f);

      _pdst->set_mem_var (
        ::utils::dbuffs::TypeMemVar::size_data,
        _pdst->get_dim_var (::utils::dbuffs::video::TypeDimVar::stride) * _pdst->get_dim_var (::utils::dbuffs::video::TypeDimVar::height));
    }

  return;
}

}}}      // namespace dlls::gens::vgen_motion
