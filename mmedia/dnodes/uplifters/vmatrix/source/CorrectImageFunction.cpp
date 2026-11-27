/**
\file ???
\brief  Filter for correct image
\author Erashov Anton erashov2026@proton.me
\date 26.07.2016
*/
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dnodes::uplifters::vmatrix
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void funcsMatrixEffects (
  InfoFilter*                     finfo,
  ::libs::bufs::Bufs*             pbuf,
  utils::dbufs::video::IVideoBuf& loc_child_y16_buf,
  Filter*                         parent_object,
  c1ore_pf::IMCaller::ptr&        pthreads);
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void applayMatrixEffects (
  InfoFilter*                                 finfo,
  ::libs::bufs::Bufs*                         pbuf,
  utils::dbufs::video::IVideoBuf::raw_ptr     y16_buf,
  utils::dbufs::video::IVideoBuf::raw_ptr     uv16_buf,
  std::vector< base_funcs::mem::CCharBlock >& correction_list_bufs_y16,
  std::vector< base_funcs::mem::CCharBlock >& correction_list_bufs_uv16,
  std::vector< base_funcs::mem::CCharBlock >& extended_correction_list_bufs_y16,
  std::vector< base_funcs::mem::CCharBlock >& extended_correction_list_bufs_uv16,
  c1ore_pf::IMCaller::ptr&                    pthreads);
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
funcsMatrixEffects (
  InfoFilter*                     finfo,
  ::libs::bufs::Bufs*             pbuf,
  utils::dbufs::video::IVideoBuf& loc_child_y16_buf,
  Filter*                         parent_object,
  c1ore_pf::IMCaller::ptr&        pthreads)
{
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // 28.12.2016 накладываем матрчный эффект если требуется
  if (!finfo->m_enable_correct)
  {
    return true;
  }
#  endif
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  utils::dbufs::video::IVideoBuf::raw_ptr loc_child_uv16_buf = 0;


  if (pbuf->ichilds_[utils::dbufs::video::consts::offs::off_uv16] >= 0)
  {
    loc_child_uv16_buf = &pbuf->childs_[pbuf->ichilds_[utils::dbufs::video::consts::offs::off_uv16]];
  }
#  endif

  ::libs::utility::checks::throw_exception ("failed");
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  applayMatrixEffects (
    finfo, pbuf, &loc_child_y16_buf, finfo->props_.change_color_ ? loc_child_uv16_buf : 0, finfo->y16_meffects_, finfo->uv16_meffects_, finfo->ext_y16_meffects_, finfo->ext_uv16_meffects_, pthreads);
#  endif
  return;
}
#endif

void
Filter::itransform ()
{
  ::libs::utility::checks::throw_exception ("failed");
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  utils::dbufs::video::IVideoBuf::ptr& l16_buf = pbuf_->childs_[pbuf_->ichilds_[utils::dbufs::video::consts::offs::lit]];
  utils::dbufs::video::IVideoBuf::ptr& s16_buf = pbuf_->childs_[pbuf_->ichilds_[utils::dbufs::video::consts::offs::sat]];
  utils::dbufs::video::IVideoBuf::ptr& h16_buf = pbuf_->childs_[pbuf_->ichilds_[utils::dbufs::video::consts::offs::hue]];

  // 11.05.2016 выделяем память под второй врменной буфер, размер его будет совпадать с буфером для вывода после масштабирования
  // в отличие от первого буфера позднее данный буфер будет использоваться, для примера, в изменении резкости изображения как
  // временной
  {
    utils::dbufs::video::IVideoBuf::ptr& l16_buf = pbuf_->childs_[pbuf_->ichilds_[utils::dbufs::video::consts::offs::lit]];
    utils::dbufs::video::IVideoBuf::ptr& btemp2  = pbuf_->childs_[pbuf_->ichilds_[utils::dbufs::video::consts::offs::temp2]];

    btemp2->alloc_equal (*l16_buf);

    utils::dbufs::video::IVideoBuf::ptr& loc_child_contoure_l16_buf = pbuf_->childs_[pbuf_->ichilds_[utils::dbufs::video::consts::offs::lcountour]];
    utils::dbufs::video::IVideoBuf::ptr& temp1_buf                  = pbuf_->childs_[pbuf_->ichilds_[utils::dbufs::video::consts::offs::temp1]];

    loc_child_contoure_l16_buf->alloc_equal (*l16_buf);
    temp1_buf->alloc_equal (*l16_buf);
  }

  // funcsMatrixEffects ( finfo, events, pbuf, *l16_buf, this, pthreads);
  funcsMatrixEffects (finfo_, pbuf_, *l16_buf, this, *pthreads_);
#endif
}
}   // namespace dnodes::uplifters::vmatrix
