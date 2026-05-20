/**
\file       BuffMed1Impl.cpp
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
#if 0
  BuffMed1Impl3::BuffMed1Impl3( SharedInfoNodeBuff::craw_ptr info ) : 
    info_(info)
  {}


  void BuffMed1Impl3::update( const BuffMed1Impl3::value_type& val )
  {
#  if 1
    U3_ASSERT_SIGNAL( "failed" );
#  else
    U3_CHECK( info_->is_valid(), "invalid shared info" );
    U3_CHECK( info_->count_akk_mbuf_ > 0, "count mbuf less or equal 0" );
    U3_CHECK( info_->count_akk_mbuf_ <= info_->count_mbuf_, "count mbuf large max" );

    if( info_->count_akk_mbuf_ == info_->count_mbuf_ )
    {
      std::rotate( 
        vals_.begin(), 
        vals_.begin() + 1, 
        vals_.begin() + info_->count_mbuf_ );
    }

    vals_[ info_->count_akk_mbuf_ - 1 ] = val;
#  endif
    return;
  }

#  if 0
  void BuffMed1Impl3::fill(  const value_type& val )
  {
    vals_.fill( val );
    return;
  }
#  endif

  BuffMed1Impl3::value_type BuffMed1Impl3::get_relement( int rang ) const
  {

#  if 0

    return vals_[ 0 ];

#  elif 1
    U3_ASSERT_SIGNAL( "failed" );
    /*
    U3_ASSERT( info_->is_valid() );
    //rang = ( -1 == rang ? info_->count_mbuf_ / 2 : rang );
    U3_ASSERT( rang < info_->count_mbuf_ );
    U3_ASSERT( rang >= 0 );

    auto sort_vals = vals_;
    */
#    if 0

    std::nth_element( 
      sort_vals.begin(),
      sort_vals.begin() + rang,
      sort_vals.begin() + info_->count_akk_mbuf_ );

#    else

    U3_ASSERT_SIGNAL( "failed" );
    /*
    const auto size = U3_CAST_SIZE_T( info_->count_akk_mbuf_ );

    for( std::size_t indx1 = 2; indx1 < size; ++indx1 )
    {
      for ( std::size_t indx2 = indx1; indx2 > 1 && sort_vals[ indx2 ] < sort_vals[ indx2 - 1 ]; --indx2 )
      {
        std::swap( sort_vals[ indx2 ], sort_vals[ indx2 - 1 ] );
      }
    }
    */
#    endif

    U3_ASSERT_SIGNAL( "failed" );
    //return sort_vals[ rang ];
    return 0;
#  endif

  }
#endif
}   // namespace dlls::filter_noise::time::impl::med3
