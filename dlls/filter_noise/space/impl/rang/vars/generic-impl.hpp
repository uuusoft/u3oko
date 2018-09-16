//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       generic-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang { namespace vars {
/**
\brief  Шаблон для реализация ранговой фильтрации изображения в пространственной области.
\tparam alg_type  тип алгоритма.
*/
template <
  typename alg_type>
class GenericImpl : public IAlgImpl
{
  public:
  GenericImpl ()
  {}

  virtual ~GenericImpl ()
  {}

  GenericImpl (const GenericImpl& _src) = delete;
  GenericImpl& operator= (const GenericImpl& _src) = delete;

  virtual void
  process (const ProcessAlgInfo& _info) override
  {
    alg_type          _alg;
    const bool        _dbuff_exist          = _info.dbuff_->self_test ();
    const std::size_t _width                = _info.buff_->width_;
    const std::size_t _height               = _info.buff_->height_;
    const auto        _size_core            = _info.impl_info_->size_core_;
    const auto        _half_size_core       = _size_core / 2;
    const auto        _dim_core             = _info.impl_info_->dim_core_;
    const auto        _rang                 = _info.impl_info_->rang_;
    auto              _sline                = _info.sbuff_->get_cline (0);
    auto              _iline                = _info.buff_->get_line (0);
    auto              _diff_line            = _dbuff_exist ? _info.dbuff_->get_cline (0) : nullptr;
    const auto        _count_core_vals      = _size_core * (1 == _dim_core ? 1 : _size_core);
    const auto        _sstride              = _info.sbuff_->stride_;
    const auto        _istride              = _info.buff_->stride_;
    const auto        _diff_stride          = _dbuff_exist ? _info.dbuff_->stride_ : 0;
    const auto        _off_beg_core         = 1 == _dim_core ? 0 : _istride * _half_size_core + _half_size_core * sizeof (short);
    const auto        _use_cond_buff        = _info.pfinfo_->rprops_->use_cond_buff_;
    const auto        _size_cond_core       = _info.impl_info_->size_cond_core_;
    const auto        _half_cond_size_core  = _size_cond_core / 2;
    const auto        _cond_rang            = _info.impl_info_->cond_rang_;
    const auto        _count_cond_core_vals = _size_cond_core * (1 == _dim_core ? 1 : _size_cond_core);
    const auto        _off_beg_cond_core    = 1 == _dim_core ? 0 : _istride * _half_cond_size_core + _half_cond_size_core * sizeof (short);

    for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
      {
        auto _spx     = _sline;
        auto _ipx     = _iline;
        auto _diff_px = _diff_line;

        for (std::size_t _indxx = 0; _indxx < _width; ++_indxx)
          {
            //  Если данный пиксель не часть движения, то сортируем и фильтруем.
            //  иначе замещаем все значения последним результатом, чтобы избежать "проявления" на старом месте объекта после остановки
            const bool _app_cond            = _use_cond_buff && *_diff_px ? true : false;
            const auto _app_size_core       = _app_cond ? _size_cond_core : _size_core;
            const auto _app_rang            = _app_cond ? _cond_rang : _rang;
            const auto _app_beg_cond_core   = _app_cond ? _off_beg_cond_core : _off_beg_core;
            const auto _app_half_size_core  = _app_cond ? _half_cond_size_core : _half_size_core;
            const auto _app_count_core_vals = _app_cond ? _count_cond_core_vals : _count_core_vals;
            auto       _beg_spx             = _spx;

            _app_half_size_core;
            _app_count_core_vals;

            _alg.process (
              _beg_spx,
              _indxx,
              _indxy,
              _app_size_core,
              _app_half_size_core,
              _app_count_core_vals,
              _app_beg_cond_core,
              _sstride,
              _app_rang,
              _spx,
              _ipx);

            _diff_px += 1;
            _ipx += 1;
            _spx += 1;
          }

        FAST_MOVE_CPTR (_sline, _sstride);
        FAST_MOVE_PTR (_iline, _istride);
        FAST_MOVE_CPTR (_diff_line, _diff_stride);
      }
    return;
  }
};

}}}}}}      // namespace dlls::filter_noise::space::impl::rang::vars
