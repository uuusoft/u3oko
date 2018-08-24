//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       CallerImpl_int_functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "caller-impl.hpp"

namespace libs { namespace optim { namespace mcalls {

bool
get_thread_per_height (
  const InfoMFunct&    _funct,
  io::MCallInfo&       _info,
  const unsigned short _athreads,
  std::size_t&         _thread_per_height,
  std::size_t&         _selected_src_height,
  std::size_t&         _selected_dst_height,
  std::size_t&         _width_macro)
{
  _thread_per_height   = 0;      //std::min<std::size_t>( _thread_per_height_src, _thread_per_height_dst );
  _selected_src_height = 0;
  _selected_dst_height = 0;
  _width_macro         = 0;

  {
    //  get info about function from key
    std::size_t _thread_per_height_src = std::numeric_limits<std::size_t>::max ();
    std::size_t _thread_per_height_dst = std::numeric_limits<std::size_t>::max ();

    _width_macro = 1;

    if (!_info.srcs_.empty ())
      {
        //ищем первый заполненный буфер.
        for (const auto& _src : _info.srcs_)
          {
            if (!_src.self_test ())
              {
                //допустимо, некоторые алгоритмы допускают наличие пустых буферов.
                continue;
              }

            _selected_src_height = _src.height_;

            if (!helpers::split_height (_athreads, _funct.src_align_.px_y_, _selected_src_height, _thread_per_height_src))
              {
                UASSERT_SIGNAL ("failed");
                return false;
              }
            break;
          }
      }

    if (!_info.dsts_.empty ())
      {
        for (const auto& _dst : _info.dsts_)
          {
            if (!_dst.self_test ())
              {
                //допустимо, некоторые алгоритмы допускают наличие пустых буферов.
                continue;
              }

            _selected_dst_height = _dst.height_;

            if (!helpers::split_height (_athreads, _funct.dst_align_.px_y_, _selected_dst_height, _thread_per_height_dst))
              {
                UASSERT_SIGNAL ("failed");
                return false;
              }
            break;
          }
      }

    UASSERT (_width_macro);
    UASSERT (1 == _width_macro);

    _thread_per_height = std::min<std::size_t> (_thread_per_height_src, _thread_per_height_dst);
  }

  UASSERT (_thread_per_height);
  UASSERT (_thread_per_height != std::numeric_limits<std::size_t>::max ());
  return true;
}


void
get_count_threads_funct (
  const InfoMFunct&    _funct,
  io::MCallInfo&       _info,
  const unsigned short _max_threads,
  unsigned short&      _athreads)
{
  UASSERT (_info.srcs_.size () || _info.dsts_.size ());      //очевидно, какие то данные алгоритм должен или получать или генерировать.

  //Ищем минимальный размер буфера среди всех переданных, как источников, так и приемников результата.
  std::size_t _min_src_height = std::numeric_limits<std::size_t>::max ();

  for (const io::ProxyBuff& _csrc : _info.srcs_)
    {
      if (_csrc.self_test ())
        {
          _min_src_height = std::min<std::size_t> (_min_src_height, _csrc.height_);
        }
    }

  std::size_t _min_dst_height = std::numeric_limits<std::size_t>::max ();

  for (const io::ProxyBuff& _cdst : _info.dsts_)
    {
      if (_cdst.self_test ())
        {
          _min_dst_height = std::min<std::size_t> (_min_dst_height, _cdst.height_);
        }
    }

  _athreads = UUU_ICAST_USHORT (::libs::helpers::utils::ret_check_bound<std::size_t> (_athreads, 1, _min_src_height / _funct.src_align_.px_y_));
  _athreads = UUU_ICAST_USHORT (::libs::helpers::utils::ret_check_bound<std::size_t> (_athreads, 1, _min_dst_height / _funct.dst_align_.px_y_));
  _athreads = UUU_ICAST_USHORT (::libs::helpers::utils::ret_check_bound<std::size_t> (_athreads, 1, _max_threads));
  return;
}


bool
CallerImpl::mcall_int (
  const InfoMFunct& _funct,
  io::MCallInfo&    _info,
  unsigned short    _athreads)
{
  if (!_funct.self_test ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  _athreads = (0 == _athreads) ? max_threads_ : _athreads;      //вызывающий может явно установить количество потоков для обработки, иначе испольуем максимальное количество.

  UASSERT (_athreads <= max_threads_);
  UASSERT (_athreads > 0);
  UASSERT (max_threads_);

  _athreads = std::min<unsigned short> (_athreads, max_threads_);      //проверяем бессмысленное значение. Количество потоков больше максимально возможного - бессмысленно.

  if (0 == max_threads_)
    {
      //  Идет завершение работы системы и поступил вызов на обработку? Игнорируем?
      return true;
    }

  //  Тестовый запуск потоков.
  if (_funct.is_empty ())
    {
      //  run threads
      sinfo_.bstart_->wait ();
      //  wait result
      sinfo_.bend_->wait ();
      return true;
    }

  //  Ищем минимальный размер буфера среди всех переданных, как источников, так и приемников результата.
  get_count_threads_funct (_funct, _info, max_threads_, _athreads);

  thread_functs_.assign (max_threads_, io::funct_mcall_type ());

  calls_.resize (max_threads_);
  src_heights_.resize (max_threads_);

  for (auto& _call : calls_)
    {
      _call.params_ = _info.params_;
    }

  UASSERT (_info.dsts_.size () || _info.srcs_.size ());

  std::size_t _thread_per_height   = 0;
  std::size_t _selected_src_height = 0;
  std::size_t _selected_dst_height = 0;
  std::size_t _width_macro         = 0;

  if (!get_thread_per_height (
        _funct,
        _info,
        _athreads,
        _thread_per_height,
        _selected_src_height,
        _selected_dst_height,
        _width_macro))
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  std::size_t _indx_thread = 0;

  for (std::size_t _indxy = 0; _indxy < _thread_per_height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width_macro; ++_indxx)
        {
          io::MCallInfo& _ccall = calls_[_indx_thread];

          _ccall.indx_thread_     = _indx_thread;
          _ccall.count_threads_   = _thread_per_height;
          _ccall.full_height_src_ = _selected_src_height;
          _ccall.full_height_dst_ = _selected_dst_height;

          _ccall.srcs_.clear ();
          _ccall.dsts_.clear ();

          if (_indx_thread >= _athreads)
            {
              continue;
            }

          for (const io::ProxyBuff& _cbuff : _info.srcs_)
            {
              io::ProxyBuff _new_add = _cbuff;

              _new_add.reset_const ();

              //UASSERT ( _new_add.buff () ); // допустимо, буфер источник может быть пустым, если он опциональный.

              if (_new_add.buff ())
                {
                  const std::size_t _macro_height      = _new_add.height_ / _funct.src_align_.px_y_;
                  const std::size_t _height_prev_block = _macro_height / _thread_per_height;
                  std::size_t       _height_cur_block  = _height_prev_block;

                  if (_indxy + 1 == _thread_per_height)
                    {
                      if (_height_cur_block * _thread_per_height < _macro_height)
                        {
                          _height_cur_block += _macro_height - _height_cur_block * _thread_per_height;
                        }
                    }

                  _new_add.width_  = _new_add.width_ / _width_macro;
                  _new_add.height_ = _height_cur_block * _funct.src_align_.px_y_;

                  std::size_t _off_rows = _indxy * _height_prev_block * _funct.src_align_.px_y_;
                  std::size_t _off_cols = _indxx * _new_add.width_ * sizeof (short);
                  std::size_t _off_src  = _off_rows * _new_add.stride_ + _off_cols;

                  _new_add.set_ubuff (_new_add.ubuff () + _off_src);
                }

              _ccall.srcs_.push_back (_new_add);
            }

          for (const io::ProxyBuff& _cbuff : _info.dsts_)
            {
              io::ProxyBuff _new_add = _cbuff;

              UASSERT (_new_add.buff ());

              if (_new_add.buff ())
                {
                  const std::size_t _macro_height      = _new_add.height_ / _funct.dst_align_.px_y_;
                  const std::size_t _height_prev_block = _macro_height / _thread_per_height;
                  std::size_t       _height_cur_block  = _height_prev_block;

                  if (_indxy + 1 == _thread_per_height)
                    {
                      if (_height_cur_block * _thread_per_height < _macro_height)
                        {
                          _height_cur_block += _macro_height - _height_cur_block * _thread_per_height;
                        }
                    }

                  _new_add.width_  = _new_add.width_ / _width_macro;
                  _new_add.height_ = _height_cur_block * _funct.dst_align_.px_y_;

                  std::size_t _off_rows = _indxy * _height_prev_block * _funct.dst_align_.px_y_ * _funct.dest_mul_koeffy_ / _funct.dest_div_koeffy_;
                  std::size_t _off_cols = _indxx * _new_add.width_ * sizeof (short);
                  std::size_t _off_src  = _off_rows * _new_add.stride_ + _off_cols;

                  _new_add.set_ubuff (_new_add.ubuff () + _off_src);
                }

              _ccall.dsts_.push_back (_new_add);
            }

          thread_functs_[_indx_thread] = _funct.pfunct_->get ();

          ++_indx_thread;
        }
    }

  //  run threads
  sinfo_.bstart_->wait ();
  //  wait result
  sinfo_.bend_->wait ();
  return true;
}

}}}      // namespace libs::optim::mcalls
