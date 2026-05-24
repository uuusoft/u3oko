#pragma once
/**
\file       generic-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
*/

namespace dlls::filter_noise::space::impl::rang::vars
{
/// Шаблон для реализация ранговой фильтрации изображения в пространственной области
/// \tparam alg_type  тип алгоритма
template< typename template_alg_type >
class GenericImpl : public IAlgImpl
{
  public:
  GenericImpl ()
  {
  }

  virtual ~GenericImpl ()
  {
  }

  GenericImpl (const GenericImpl& src)            = delete;
  GenericImpl& operator= (const GenericImpl& src) = delete;


  virtual void
  process (const ProcessAlgInfo& info) override
  {
    template_alg_type   alg;
    const bool          dbuf_exist           = info.dbuf_->self_test ();
    const std::uint32_t width                = info.buf_->width_;
    const std::uint32_t height               = info.buf_->height_;
    const auto          size_core            = info.impl_info_->size_core_;
    const auto          half_size_core       = size_core / 2;
    const auto          dim_core             = info.impl_info_->dim_core_;
    const auto          rang                 = info.impl_info_->rang_;
    auto                sline                = info.sbuf_->get_cline (0);
    auto                iline                = info.buf_->get_line (0);
    auto                diff_line            = dbuf_exist ? info.dbuf_->get_cline (0) : nullptr;
    const auto          count_core_vals      = size_core * (1 == dim_core ? 1 : size_core);
    const auto          sstride              = info.sbuf_->stride_;
    const auto          istride              = info.buf_->stride_;
    const auto          diff_stride          = dbuf_exist ? info.dbuf_->stride_ : 0;
    const std::uint32_t off_beg_core         = 1 == dim_core ? 0 : istride * half_size_core + half_size_core * sizeof (std::int16_t);
    const auto          use_cond_buf         = info.pfinfo_->rprops_->use_cond_buf_;
    const std::int32_t  size_cond_core       = info.impl_info_->size_cond_core_;
    const std::int32_t  half_cond_size_core  = size_cond_core / 2;
    const std::int32_t  cond_rang            = info.impl_info_->cond_rang_;
    const std::int32_t  count_cond_core_vals = size_cond_core * (1 == dim_core ? 1 : size_cond_core);
    const std::uint32_t off_beg_cond_core    = 1 == dim_core ? 0 : istride * half_cond_size_core + half_cond_size_core * sizeof (std::int16_t);

    for (std::uint32_t indxy = 0; indxy < height; ++indxy)
    {
      auto spx     = sline;
      auto ipx     = iline;
      auto diff_px = diff_line;

      for (std::uint32_t indxx = 0; indxx < width; ++indxx)
      {
        //  Если данный пиксель не часть движения, то сортируем и фильтруем.
        //  иначе замещаем все значения последним результатом, чтобы избежать "проявления" на старом месте объекта после остановки
        const bool                app_cond            = use_cond_buf && diff_px ? true : false;
        const auto                app_size_core       = app_cond ? size_cond_core : size_core;
        const auto                app_rang            = app_cond ? cond_rang : rang;
        const std::uint32_t       app_beg_cond_core   = app_cond ? off_beg_cond_core : off_beg_core;
        U3_MARK_UNUSED const auto app_half_size_core  = app_cond ? half_cond_size_core : half_size_core;
        U3_MARK_UNUSED const auto app_count_core_vals = app_cond ? count_cond_core_vals : count_core_vals;
        auto                      beg_spx             = spx;

        U3_ASSERT (app_rang < app_size_core * app_size_core);

        alg.process (
          beg_spx,
          indxx,
          indxy,
          app_size_core,
          app_half_size_core,
          app_count_core_vals,
          app_beg_cond_core,
          sstride,
          app_rang,
          spx,
          ipx);

        diff_px += 1;
        ipx += 1;
        spx += 1;
      }

      U3_FAST_MOVE_CPTR (sline, sstride);
      U3_FAST_MOVE_PTR (iline, istride);
      U3_FAST_MOVE_CPTR (diff_line, diff_stride);
    }
  }
};
}   // namespace dlls::filter_noise::space::impl::rang::vars
