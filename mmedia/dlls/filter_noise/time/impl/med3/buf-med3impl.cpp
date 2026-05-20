/**
\file       buf-med3impl.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me

\project    uuu_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-impl-med3-includes_int.hpp"
#include "buf-med3impl.hpp"

namespace dlls::filter_noise::time::impl::med3
{
BuffMed3Impl::BuffMed3Impl (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp::raw_ptr params)
{
  shared_info_.params_ = params;
}


BuffMed3Impl::~BuffMed3Impl ()
{
}


void
BuffMed3Impl::sync_by_vbuf (
  const ::utils::dbufs::video::IVideoBuf::raw_ptr                                   buf,
  const ::utils::dbufs::video::IVideoBuf::raw_ptr                                   dbuf,
  ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp::craw_ptr impl_info)
{
  const std::uint32_t width      = buf->get_dim_var (::utils::dbufs::video::Dims::width);
  const std::uint32_t height     = buf->get_dim_var (::utils::dbufs::video::Dims::height);
  const auto          count_bufs = shared_info_.params_->count_bufs_;

  if (!shared_info_.akk_mbuf_)
  {
    shared_info_.akk_mbuf_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ()->create (width * count_bufs * 3 * height);
    //  Cпециальный буфер-аккумулятор, для хранения всех накопленных буферов.
    //  Храним для каждого пикселя 3 массива:
    //  1. Массив значений A пикселей всех буферов.
    //  2. Массив индексов I значений A в отсортированном массиве.
    //  3. Отсортированный массив значений A
    shared_info_.akk_mbuf_->buf_alloc (
      ::utils::dbufs::video::AllocBufInfo (
        width * count_bufs * 3,
        height,
        0,
        ::libs::helpers::uids::minor::id_val::y16,
        utils::dbufs::video::DimChecks::disable));
    //::utils::dbufs::BufFlags::empty));

    shared_info_.akk_mbuf_->set_mem_var (::utils::dbufs::MemVars::size_data, (*shared_info_.akk_mbuf_)[::utils::dbufs::MemVars::size_buf]);
    utils::dbufs::video::helpers::fill (shared_info_.akk_mbuf_.get (), 0);
  }

  const bool full_house = shared_info_.count_akk_mbuf_ == count_bufs ? true : false;
  if (shared_info_.count_akk_mbuf_ < count_bufs)
  {
    ++shared_info_.count_akk_mbuf_;
  }

  const auto count_akk_mbuf = shared_info_.count_akk_mbuf_;
  auto       iline          = ::utils::dbufs::video::helpers::get_line_data_as< std::int16_t* > (buf, 0);
  auto       oline          = ::utils::dbufs::video::helpers::get_line_data_as< std::int16_t* > (shared_info_.akk_mbuf_.get (), 0);
  auto       diline         = ::utils::dbufs::video::helpers::get_line_const_data_as< const std::int16_t* > (dbuf, 0);
  const auto istride        = buf->get_dim_var (::utils::dbufs::video::Dims::stride);
  const auto ostride        = shared_info_.akk_mbuf_->get_dim_var (::utils::dbufs::video::Dims::stride);
  const auto distride       = dbuf->get_dim_var (::utils::dbufs::video::Dims::stride);

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    auto ipx  = iline;
    auto opx  = oline;
    auto dipx = diline;

    for (std::uint32_t indxx = 0; indxx < width; ++indxx)
    {
      if (full_house)
      {
        auto mopx = opx;

        // смещаем неотсортированный массив.
        std::rotate (mopx, mopx + 1, mopx + count_akk_mbuf);
        mopx += count_bufs;

        const auto del_indx = *mopx;   //<-индекс элемента в отсортированном массиве, который требуется удалить
        U3_ASSERT (del_indx < U3_CAST_INT16 (count_akk_mbuf - 1));

        // смещаем массив и значения индексов элементов, которые находятся ЗА удаляемым.
        std::transform (
          mopx + 1,
          mopx + count_akk_mbuf,
          mopx,
          [del_indx] (short val) {
            if (val <= del_indx)
            {
              return val;
            }
            --val;
            return val;
          });

        mopx += count_bufs;

        // удаляем из отсортированного массива значение по индексу.
        std::rotate (
          mopx + del_indx,
          mopx + del_indx + 1,
          mopx + count_akk_mbuf);

        U3_ASSERT (std::is_sorted (mopx, mopx + count_akk_mbuf - 1));
      }

      // сохраняем новое полученное значение в первом буфере и сбрасываем индекс в нейтральное значение во втором.
      auto& ropx = opx[0 * count_bufs + count_akk_mbuf - 1];
      auto& ripx = opx[1 * count_bufs + count_akk_mbuf - 1];
      auto& sipx = opx[2 * count_bufs + count_akk_mbuf - 1];

      ropx = *ipx;
      ripx = 0;
      sipx = ropx;

      //  Если требуется пропустить этап сортировки (для тестирования), то просто ничего не делаем.
      if ((count_akk_mbuf > 1) && /*full_house &&*/ (::libs::ievents::props::videos::noises::time::ext::Sortings::skip != impl_info->sort_type_))
      {
        //  Всегда поддерживаем отсортированный массив в консистентном состоянии.
        //  Для этого производим сначала сортировку слиянием.
        //  Т.к. стандарт гарантирует стабильность этой сортировки в пределах каждой из входных последовательностей,
        //  то нам надо найти последний элемент в новой последовательности, который равен вставленному.
        //  Его позиция и будет индексом вставленного элемента, которая нам нужна, чтобы обновить второй массив индексов.
        auto sbuf_opx = opx + 2 * count_bufs;

        std::inplace_merge (
          sbuf_opx,
          sbuf_opx + count_akk_mbuf - 1,
          sbuf_opx + count_akk_mbuf);

        auto orange = std::equal_range (
          sbuf_opx,
          sbuf_opx + count_akk_mbuf,
          ropx);

        const auto oindx = std::distance (sbuf_opx, orange.second);

        ripx = U3_CAST_STATIC< std::remove_reference< decltype (ripx) >::type > (oindx - 1);

        // синхронизируем массим индексов для тех элементов, которые за новым элементом.
        auto mopx = opx + 1 * count_bufs;

        std::transform (
          mopx,
          mopx + count_akk_mbuf - 1,
          mopx,
          [ripx] (short val) {
            if (val < ripx)
            {
              return val;
            }
            ++val;
            return val;
          });

        U3_ASSERT (std::is_sorted (sbuf_opx, sbuf_opx + count_akk_mbuf));

        // Если данный пиксель часть движения, то просто ничего не делаем.
        if (!impl_info->motion_detect_ || !*dipx)
        {
          //<сохраняем результат {ранговый элемент} в входном/выходном буфере
          *ipx = sbuf_opx[shared_info_.params_->rang_];
        }
      }

      dipx += 1;
      ipx += 1;
      opx += count_bufs * 3;
    }

    U3_FAST_MOVE_PTR (iline, istride);
    U3_FAST_MOVE_PTR (oline, ostride);
    U3_FAST_MOVE_CPTR (diline, distride);
  }
}
}   // namespace dlls::filter_noise::time::impl::med3
