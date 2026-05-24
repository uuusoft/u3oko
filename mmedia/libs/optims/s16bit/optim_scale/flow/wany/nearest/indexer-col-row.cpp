/**
\file       indexer-col-row.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_scale
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "indexer-col-row.hpp"

namespace libs::optim::s16bit::scale::flow::wany::nearest
{
IndexerColRow::IndexerColRow () :
  src_width_ (0),
  src_height_ (0),
  dst_width_ (0),
  dst_height_ (0),
  src_stride_ (0)
{
}


IndexerColRow::~IndexerColRow ()
{
}


::libs::helpers::mem::IBlockMem::craw_ptr
IndexerColRow::get_indxrow () const
{
  return indxrow_.get ();
}


::libs::helpers::mem::IBlockMem::craw_ptr
IndexerColRow::get_indxcol () const
{
  return indxcol_.get ();
}


void
IndexerColRow::update (
  std::uint32_t src_width,
  std::uint32_t src_height,
  std::uint32_t src_stride,
  std::uint32_t dst_width,
  std::uint32_t dst_height)
{
  if (src_width == src_height_ && src_height == src_height_ && src_stride_ == src_stride && dst_width == dst_height_ && dst_height == dst_height_)
  {
    return;
  }

  src_width_  = src_width;
  src_height_ = src_height;
  dst_width_  = dst_width;
  dst_height_ = dst_height;
  src_stride_ = src_stride;

  indxcol_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ()->alloc (dst_width_ * sizeof (uint32_t));
  indxrow_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ()->alloc (dst_height_ * sizeof (uint32_t));

  //  init offset index for all strings
  const float    colkoeff = U3_CAST_FLOAT (src_width_) / U3_CAST_FLOAT (dst_width_);
  std::uint32_t* pixels   = ::utils::mem_funcs::helpers::get_as< uint32_t > (indxcol_.get ());

  for (std::uint32_t indx = 0; indx < dst_width_; ++indx)
  {
    uint32_t& pixel = pixels[indx];

    pixel = indx * colkoeff;
    pixel = pixel > src_width_ - 1 ? src_width_ - 1 : pixel;
  }

  const float    rowkoeff = U3_CAST_FLOAT (src_height_) / U3_CAST_FLOAT (dst_height_);
  std::uint32_t* strings  = utils::mem_funcs::helpers::get_as< uint32_t > (indxrow_.get ());

  for (std::uint32_t indx = 0; indx < dst_height_; ++indx)
  {
    std::uint32_t& string = strings[indx];

    string = indx * rowkoeff;
    string = string > src_height_ - 1 ? src_height_ - 1 : string;
  }
}
}   // namespace libs::optim::s16bit::scale::flow::wany::nearest
