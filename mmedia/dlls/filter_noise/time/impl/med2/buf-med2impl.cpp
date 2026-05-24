/**
\file       CBuffMed.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-impl-med2-includes_int.hpp"
#include "buf-med2impl.hpp"

namespace dlls::filter_noise::time::impl::med2
{
BuffMed2Impl::BuffMed2Impl (MedianTimeFilterProp::raw_ptr params)
{
  shared_info_.params_ = params;
}


BuffMed2Impl::~BuffMed2Impl ()
{
}


void
BuffMed2Impl::update_int_bufs (
  ::libs::optim::io::ProxyBuf*       buf,
  const ::libs::optim::io::ProxyBuf* dbuf,
  MedianTimeFilterProp::craw_ptr     impl_info)
{
  const std::uint32_t width          = buf->width_;
  const std::uint32_t height         = buf->height_;
  auto&               count_akk_bufs = shared_info_.count_akk_mbuf_;
  auto                count_bufs     = shared_info_.params_->count_bufs_;

  if (!shared_info_.akk_mbuf_)
  {
    U3_LOG_DATA_DEV ("time filtartion: update akk" + VTOLOG (count_bufs));
    shared_info_.akk_mbuf_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ()->create (width * count_bufs * height);

    // специальный буфер-аккумулятор, для хранения всех накопленных буферов.
    auto alloc_info = ::utils::dbufs::video::AllocBufInfo (width * count_bufs, height, 0, ::libs::helpers::uids::minor::id_val::y16, utils::dbufs::video::DimChecks::disable);

    // alloc_info.flags_[::utils::dbufs::BufFlags::convolution_support] = true;
    shared_info_.akk_mbuf_->buf_alloc (alloc_info);
    /*
      ::utils::dbufs::video::AllocBufInfo (
        width * count_bufs,
        height,
        0,
        ::libs::helpers::uids::minor::id_val::y16,
        utils::dbufs::video::DimChecks::disable,
        ::utils::dbufs::BufFlags::empty));
        */
    shared_info_.akk_mbuf_->set_mem_var (::utils::dbufs::MemVars::size_data, (*shared_info_.akk_mbuf_)[::utils::dbufs::MemVars::size_buf]);
    utils::dbufs::video::helpers::fill (shared_info_.akk_mbuf_.get (), 0);
  }

  shared_info_.full_house_ = count_akk_bufs == count_bufs ? true : false;

  if (count_akk_bufs < count_bufs)
  {
    ++count_akk_bufs;
  }
}


void
BuffMed2Impl::sync_by_vbuf (
  ::libs::optim::io::ProxyBuf*       buf,
  ::libs::optim::io::ProxyBuf*       akk_mbuf,
  const ::libs::optim::io::ProxyBuf* dbuf,
  MedianTimeFilterProp::craw_ptr     impl_info) const
{
  std::int16_t        sort_vals[::libs::ievents::props::videos::noises::time::ext::consts::max_count_bufs];
  const std::uint32_t width          = buf->width_;
  const std::uint32_t height         = buf->height_;
  const auto          count_akk_bufs = shared_info_.count_akk_mbuf_;
  const auto          count_bufs     = shared_info_.params_->count_bufs_;
  const bool          full_house     = shared_info_.full_house_;
  const auto          rang           = shared_info_.params_->rang_;
  auto                iline          = buf->get_line (0);
  auto                akk_line       = akk_mbuf->get_line (0);
  auto                diff_line      = impl_info->motion_detect_ ? dbuf->get_cline (0) : nullptr;
  const auto          istride        = buf->stride_;
  const auto          akk_stride     = akk_mbuf->stride_;
  const auto          diff_stride    = dbuf->stride_;

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    auto ipx     = iline;
    auto akk_px  = akk_line;
    auto diff_px = diff_line;

    for (std::uint32_t indxx = 0; indxx < width; ++indxx)
    {
      //  если количество буферов превашет максимально допустимое - сдивгаем все значения,отбрасывая самое старое (первое).
      if (full_house)
      {
        std::rotate (akk_px, akk_px + 1, akk_px + count_akk_bufs);
      }

      akk_px[count_akk_bufs - 1] = *ipx;

      //  Если требуется пропустить этап сортировки (для тестирования), или у нас недостаточно данных для фильтрации то просто ничего не делаем.
      if ((::libs::ievents::props::videos::noises::time::ext::Sortings::skip == impl_info->sort_type_) || !full_house)
      {
        std::fill (
          akk_px,
          akk_px + count_akk_bufs - 1,
          akk_px[count_akk_bufs - 1]);
      }
      else
      {
        //  Если данный пиксель не часть движения, то сортируем и фильтруем.
        //  иначе замещаем все значения последним результатом, чтобы избежать "проявления" на старом месте объекта после остановки
        if (!impl_info->motion_detect_ || !*diff_px)
        {
          //  копируем во временный буфер, чтобы отсортировать.
          std::copy (akk_px, akk_px + count_akk_bufs, sort_vals);
          //  сортируем временный буфер.
          sel_sort (impl_info->sort_type_, count_akk_bufs, rang, sort_vals);
          //  сохраняем результат в входном/выходном буфере.
          *ipx = sort_vals[rang];
        }
      }

      diff_px += 1;
      ipx += 1;
      akk_px += count_bufs;
    }

    U3_FAST_MOVE_PTR (iline, istride);
    U3_FAST_MOVE_PTR (akk_line, akk_stride);
    U3_FAST_MOVE_CPTR (diff_line, diff_stride);
  }
}
}   // namespace dlls::filter_noise::time::impl::med2
