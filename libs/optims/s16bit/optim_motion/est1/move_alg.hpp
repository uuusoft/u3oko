#pragma once
/**
\file     move_alg.hpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date     12.09.2016
\project  uuu_optim_motion
\brief    Оценка движения в кадре.
*/
#include "vals.hpp"

namespace libs { namespace optim { namespace s16bit { namespace motion { namespace est1 {
/**
  \brief  empty brief
  */
template <
  typename TTCalculator>
void
move_alg (::libs::optim::MCallInfo& _info)
{
  TTCalculator         _calcs;
  const BuffEventInfo* _pparams  = nullptr;
  const io::ProxyBuff* _cur_src  = nullptr;
  const io::ProxyBuff* _prev_src = nullptr;
  io::ProxyBuff*       _dst_vecs = nullptr;

  get_params (_info, &_cur_src, &_prev_src, &_dst_vecs, &_pparams);

  //optim::mcalls::helpers::fill( _dst_vecs, rand() % 255 );
  optim::mcalls::helpers::fill (_dst_vecs, 0);

  const std::size_t _offy   = _info.indx_thread_ * _cur_src->height_;
  const std::size_t _leaky  = (_info.count_threads_ - _info.indx_thread_ - 1) * _cur_src->height_;
  std::size_t       _dindxy = 0;

  _calcs.init (_info);

  for (std::size_t _indxy = 0; _indxy < _cur_src->height_; _indxy += _pparams->size_block_)
    {
      std::size_t _dindxx = 0;
      short*      _ldst   = _dst_vecs->get_line (_dindxy);

      ++_dindxy;

      if (_indxy + _pparams->size_block_ >= UUU_ICAST_INT_PTR (_cur_src->height_ + _leaky))
        {
          continue;
        }

      for (std::size_t _indxx = 0; _indxx < _cur_src->width_; _indxx += _pparams->size_block_)
        {
          const short*          _cur_ssrc = &_cur_src->get_cline (_indxy)[_indxx];
          int                   _diff     = std::numeric_limits<int>::max ();
          char*                 _rldst    = UUU_MEM_CAST<char*> (&_ldst[_dindxx]);
          std::pair<char, char> _rvec     = ::libs::ievents::props::videos::generics::motion_est::consts::inv_vec;

          ++_dindxx;

          if (_indxx + _pparams->size_block_ >= UUU_ICAST_INT_PTR (_cur_src->width_))
            {
              continue;
            }

          for (std::size_t _indxv = 0; _indxv < _pparams->search_vecs_.size (); ++_indxv)
            {
              const std::pair<char, char>& _ivec   = _pparams->search_vecs_[_indxv];
              int                          _pindxx = UUU_ICAST_INT (_indxx) + _ivec.first;
              int                          _pindxy = UUU_ICAST_INT (_indxy) + _ivec.second;

              if (_pindxx < 0)
                {
                  continue;
                }

              if (_pindxx + _pparams->size_block_ >= UUU_ICAST_INT (_cur_src->width_))
                {
                  continue;
                }

              if (UUU_ICAST_INT (_offy) + _pindxy < 0)
                {
                  continue;
                }

              if (_pindxy + _pparams->size_block_ >= UUU_ICAST_INT (_cur_src->height_ + _leaky))
                {
                  continue;
                }

              const short* _prev_ssrc  = &_prev_src->get_cline (_pindxy, true)[_pindxx];
              const int    _block_diff = _calcs.get_res (_cur_ssrc, _prev_ssrc, _pparams->size_block_, _cur_src->stride_);

              if (_block_diff < _pparams->max_error_)
                {
                  if (_block_diff < _diff)
                    {
                      _diff = _block_diff;
                      _rvec = _ivec;

                      if (_diff <= _pparams->min_error_)
                        {
                          break;
                        }
                    }
                }
            }

          *(_rldst + 0) = _rvec.first;
          *(_rldst + 1) = _rvec.second;

#if 0
        //debug
        *( _rldst + 0) = -8;
        *( _rldst + 1 ) = -8;
#endif
        }
    }
  return;
}

}}}}}      // namespace libs::optim::s16bit::motion::est1
