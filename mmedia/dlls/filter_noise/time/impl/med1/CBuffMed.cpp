/**
\file       CBuffMed.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-impl-med1-includes_int.hpp"
#include "CBuffMed.hpp"

// EAI-REMOVE old shit
namespace dlls::filter_noise::time::impl::med1
{
#if 0
CBuffMed::CBuffMed (int count_mbuf)
{
  shared_info_.count_mbuf_ = count_mbuf;
  return;
}


CBuffMed::~CBuffMed ()
{
}


void
CBuffMed::sync_by_vbuf (const ::utils::dbufs::video::IVideoBuf::raw_ptr buf)
{
  const std::size_t width  = buf->get_dim_var (::utils::dbufs::video::Dims::width);
  const std::size_t height = buf->get_dim_var (::utils::dbufs::video::Dims::height);

  buf_.resize (height);

  if (shared_info_.count_akk_mbuf_ < shared_info_.count_mbuf_)
  {
    ++shared_info_.count_akk_mbuf_;
  }

  for (std::size_t indxy = 0; indxy < height; ++indxy)
  {
    auto  iline = ::utils::dbufs::video::helpers::get_line_const_data_as< const std::int16_t* > (buf, indxy);
    auto& oline = buf_[indxy];

    oline.resize (width, node_type (&shared_info_));

    for (std::size_t indxx = 0; indxx < width; ++indxx)
    {
      auto& node = oline[indxx];

      node.update (iline[indxx]);
    }
  }

  return;
}


void
CBuffMed::sync_by_dbuf (const ::utils::dbufs::video::IVideoBuf::raw_ptr buf)
{
#  if 0
    const std::size_t width = buf->get_dim_var( ::utils::dbufs::video::Dims::width );
    const std::size_t height = buf->get_dim_var( ::utils::dbufs::video::Dims::height );

    for( std::size_t indxy = 0; indxy < height; ++indxy )
    {
      auto  iline  = ::utils::dbufs::video::helpers::get_line_const_data_as<const std::int16_t*>( buf, indxy );
      auto& oline  = buf_[ indxy ];

      for ( std::size_t indxx = 0; indxx < width; ++indxx )
      {
        //если данный пиксель часть движения, то просто сбрасываем у него массив в последнее значение.
        if( iline[indxx] )
        {
          auto&   node = oline[indxx];
          const auto  val = node.get_relement( shared_info_.count_akk_mbuf_ - 1 );

          node.fill( val );
        }
      }
    }
#  endif
  return;
}


const CBuffMed::node_type&
CBuffMed::get_node (std::size_t x, std::size_t y) const
{
  return buf_.at (y).at (x);
}
#endif
}   // namespace dlls::filter_noise::time::impl::med1
