/**
\file       buf-med1-impl.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me

\project    uuu_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-impl-med1-includes_int.hpp"
#include "buf-med1impl.hpp"

namespace dlls::filter_noise::time::impl::med1
{
BuffMed1Impl::BuffMed1Impl (CSharedInfoNodeBuffMed::craw_ptr info) :
  info_ (info)
{
}


void
BuffMed1Impl::update (const BuffMed1Impl::value_type& val)
{
  // U3_CHECK( info_->is_valid(), "invalid shared info" );
  U3_CHECK (info_->count_akk_mbuf_ > 0, "count mbuf less or equal 0");
  U3_CHECK (info_->count_akk_mbuf_ <= info_->count_mbuf_, "count mbuf large max");

  if (info_->count_akk_mbuf_ == info_->count_mbuf_)
  {
    std::rotate (vals_.begin (), vals_.begin () + 1, vals_.begin () + info_->count_mbuf_);
  }

  vals_[info_->count_akk_mbuf_ - 1] = val;
}


void
BuffMed1Impl::fill (const value_type& val)
{
  vals_.fill (val);
}


BuffMed1Impl::value_type
BuffMed1Impl::get_relement (int rang) const
{
#if 0
    //debug
    return vals_[ 0 ];
#elif 1

  // U3_ASSERT( info_->is_valid() );
  // rang = ( -1 == rang ? info_->count_mbuf_ / 2 : rang );
  U3_ASSERT (rang < info_->count_mbuf_);
  U3_ASSERT (rang >= 0);

  auto sort_vals = vals_;

#  if 0

    std::nth_element( 
      sort_vals.begin(),
      sort_vals.begin() + rang,
      sort_vals.begin() + info_->count_akk_mbuf_ );

#  else

  const auto size = U3_CAST_SIZE_T (info_->count_akk_mbuf_);

  for (std::size_t indx1 = 1; indx1 < size; ++indx1)
  {
    for (std::size_t indx2 = indx1; indx2 > 1 && sort_vals[indx2] < sort_vals[indx2 - 1]; --indx2)
    {
      std::swap (sort_vals[indx2], sort_vals[indx2 - 1]);
    }
  }

#  endif

  return sort_vals[rang];
#endif
}
}   // namespace dlls::filter_noise::time::impl::med1
