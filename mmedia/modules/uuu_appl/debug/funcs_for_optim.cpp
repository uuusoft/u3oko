/**
\file       funcs_for_optim.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_module_appl
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-appl-includes_int.hpp"

// old shit
#if 0
void
debug_func_for_optim1 (const ::libs::properties::vers::links::links_type* plinks)
{
  ::libs::helpers::statistic::ExpandedTimes timer;
  std::list< std::string >                  times;
  const std::size_t                         count_cycles = 10;
  const std::size_t                         width        = 1280;
  const std::size_t                         height       = 720;
  const std::size_t                         stride_src   = width * 3;
  const std::size_t                         stride_dst   = ::libs::helpers::mem::get_align32 (width * sizeof (std::int16_t));
  ::libs::helpers::mem::IBlockMem::ptr      rgb24        = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->alloc (stride_src * 2 * height);
  ::libs::helpers::mem::IBlockMem::ptr      l1           = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->alloc (stride_dst * 2 * height);
  ::libs::helpers::mem::IBlockMem::ptr      l2           = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->alloc (stride_dst * 2 * height);

  timer.begin ("Debug");

  for (std::size_t indx = 0; indx < count_cycles; ++indx)
  {
#  if 1
    conv3x3_test (
      l1->get_as< std::int16_t > () + stride_dst * 3,
      l2->get_as< std::int16_t > () + stride_dst * 3,
      width,
      height,
      stride_dst);

#  elif 1
    rgb24_to_l_avx2_test (
      8,
      l1->get_as< std::int16_t > (),
      rgb24->get_as< std::uint32_t > (),
      width,
      height,
      stride_src,
      stride_dst);

#  else
    mm256_zeroall ();

    memset (mem->get (), 1, mem->size ());

    std::int16_t* vals1   = mem->get_as< std::int16_t > ();
    const __m256i addreg1 = mm256_setr_epi16 (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    const __m256i addreg2 = mm256_setr_epi16 (-1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    for (std::size_t indxe = 0; indxe < count_elements; indxe += 4)
    {
      __m256i data1 = mm256_lddqu_si256 (U3_CAST_REINTERPRET< __m256i* > (&vals1[indxe]));
      data1         = mm256_adds_epi16 (data1, addreg1);
      data1         = mm256_mulhi_epi16 (data1, addreg2);
      mm256_storeu_si256 (U3_CAST_REINTERPRET< __m256i* > (&vals1[indxe]), data1);
    }
#  endif
  }

  timer.end ();
  timer.get (times);

  ELOGIT2LINK (plinks->all2log_, times.begin ()->c_str ());
}
#endif
