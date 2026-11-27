/**
\file   ???
\brief  Filter for correct image
\author Erashov Anton erashov2026@proton.me
\date   26.07.2016
*/
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dnodes::uplifters::vmatrix
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
applayMatrixEffects (
  InfoFilter*                                 finfo,
  ::libs::bufs::Bufs*                         pbuf,
  utils::dbufs::video::IVideoBuf::raw_ptr     y16_buf,
  utils::dbufs::video::IVideoBuf::raw_ptr     uv16_buf,
  std::vector< base_funcs::mem::CCharBlock >& correction_list_bufs_y16,
  std::vector< base_funcs::mem::CCharBlock >& correction_list_bufs_uv16,
  std::vector< base_funcs::mem::CCharBlock >& extended_correction_list_bufs_y16,
  std::vector< base_funcs::mem::CCharBlock >& extended_correction_list_bufs_uv16,
  c1ore_pf::IMCaller::ptr&                    pthreads)
{
  if (correction_list_bufs_y16.size () <= 0)
  {
    return;
  }

  std::vector< std::int16_t* > loc_array_pointer_block_y16;
  std::vector< std::int16_t* > loc_array_pointer_block_uv16;

  std::vector< std::int16_t* > loc_array_pointer_extended_block_y16;
  std::vector< std::int16_t* > loc_array_pointer_extended_block_uv16;

  loc_array_pointer_block_y16.resize (correction_list_bufs_y16.size ());
  std::fill (loc_array_pointer_block_y16.begin (), loc_array_pointer_block_y16.end (), r1einterpret_cast< std::int16_t* > (0));

  for (uint32_t indx1 = 0; indx1 < correction_list_bufs_y16.size (); ++indx1)
  {
    loc_array_pointer_block_y16[indx1] = r1einterpret_cast< std::int16_t* > (correction_list_bufs_y16[indx1].get ());
  }

  loc_array_pointer_extended_block_y16.resize (extended_correction_list_bufs_y16.size ());
  std::fill (loc_array_pointer_extended_block_y16.begin (), loc_array_pointer_extended_block_y16.end (), r1einterpret_cast< std::int16_t* > (0));

  for (uint32_t indx1 = 0; indx1 < extended_correction_list_bufs_y16.size (); ++indx1)
  {
    loc_array_pointer_extended_block_y16[indx1] = r1einterpret_cast< std::int16_t* > (extended_correction_list_bufs_y16[indx1].get ());
  }

  loc_array_pointer_block_uv16.resize (correction_list_bufs_uv16.size ());
  std::fill (loc_array_pointer_block_uv16.begin (), loc_array_pointer_block_uv16.end (), re1interpret_cast< std::int16_t* > (0));

  for (uint32_t indx1 = 0; indx1 < correction_list_bufs_uv16.size (); ++indx1)
  {
    loc_array_pointer_block_uv16[indx1] = r1einterpret_cast< std::int16_t* > (correction_list_bufs_uv16[indx1].get ());
  }

  loc_array_pointer_extended_block_uv16.resize (extended_correction_list_bufs_uv16.size ());
  std::fill (loc_array_pointer_extended_block_uv16.begin (), loc_array_pointer_extended_block_uv16.end (), r1einterpret_cast< std::int16_t* > (0));

  for (uint32_t indx1 = 0; indx1 < extended_correction_list_bufs_uv16.size (); ++indx1)
  {
    loc_array_pointer_extended_block_uv16[indx1] = r1einterpret_cast< std::int16_t* > (extended_correction_list_bufs_uv16[indx1].get ());
  }

  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.emplace_back (y16_buf);

  if (uv16_buf)
  {
    cinfo.dsts_.emplace_back (uv16_buf);
  }

  cinfo.params_.parrayss_.push_back (finfo->use_ext_files_ ? &loc_array_pointer_extended_block_y16[0] : &loc_array_pointer_block_y16[0]);
  cinfo.params_.parrayss_.push_back (finfo->use_ext_files_ ? &loc_array_pointer_extended_block_uv16[0] : &loc_array_pointer_block_uv16[0]);
  cinfo.params_.parrayss_.push_back (&loc_array_pointer_block_y16[0]);
  cinfo.params_.parrayss_.push_back (&loc_array_pointer_block_uv16[0]);

  cinfo.params_.ints_.push_back (correction_list_bufs_y16.size ());
  cinfo.params_.ints_.push_back (finfo->props_.koeff_);
  cinfo.params_.ints_.push_back (finfo->props_.bound_);

    C1HECK_CALLS( *pthreads.lock () ).mcall ( finfo->pfunc_matrix_, cinfo ), "failde call mcall" ) );

    return;
}
#endif
}   // namespace dnodes::uplifters::vmatrix
