/**
\file       matrix1_alu.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "matrix1.hpp"

// old shit
namespace libs::optim::s16bit::gen::matrix1
{
#if 0
#  if 0
bool
alu (
  const void *source,
  int         stride_source,
  int         width_element,
  int         height_element,
  int        *output_freq_array,
  int         size_output_freq_array)
{
  U3_ASSERT_SIGNAL ("failed");
  //#pragma message( "Outstanding" )
#    if 0
#      define SIZE_BLOCK_FOR_MATRIX_EFFECT (8)

    std::uint32_t loc_block_width = y16_buf.einfo_.video_.width_ / SIZE_BLOCK_FOR_MATRIX_EFFECT;
    std::uint32_t loc_block_height = y16_buf.einfo_.video_.height_ / SIZE_BLOCK_FOR_MATRIX_EFFECT;

    for( std::uint32_t indx_y = 0; indx_y < loc_block_height; ++indx_y )
    {
      for( std::uint32_t indx_x = 0; indx_x < loc_block_width; ++indx_x )
      {
        std::int16_t *loc_pointer_to_block = re1interpret_cast<short*>(y16_buf.m_data + (indx_y * SIZE_BLOCK_FOR_MATRIX_EFFECT * y16_buf.stride_ ) + indx_x * SIZE_BLOCK_FOR_MATRIX_EFFECT * sizeof(std::int16_t) );

        //для данного блока производим поиск наиболее близкого блока из списка, результат индекс этого блока
        std::uint32_t indx_search_block = 0;
        std::int16_t loc_min_diff_block = 0;

        for( std::uint32_t indx_blocks = 0; indx_blocks < correction_list_bufs.size(); ++indx_blocks )
        {
          std::int16_t loc_current_diff_block = 0;
          std::int16_t *temp_source_block = r1einterpret_cast<short*>( correction_list_bufs[ indx_blocks ].get() );

          for( std::uint32_t indx_y = 0; indx_y < SIZE_BLOCK_FOR_MATRIX_EFFECT; ++indx_y)
          {
            std::int16_t *loc_pointer_to_string_dest_block = 
              r1einterpret_cast<short*>( re1interpret_cast<std::uint8_t*>( loc_pointer_to_block) + indx_y * y16_buf.stride_ );

            for( std::uint32_t indx_x = 0; indx_x < SIZE_BLOCK_FOR_MATRIX_EFFECT; ++indx_x )
            {
              std::int16_t loc_diff_pixel = loc_pointer_to_string_dest_block[ indx_x ] - temp_source_block[ indx_y * SIZE_BLOCK_FOR_MATRIX_EFFECT + indx_x ];

              loc_diff_pixel = loc_diff_pixel < 0 ? -loc_diff_pixel : loc_diff_pixel;
              loc_current_diff_block+= loc_diff_pixel;
            };
          };

          if( ( loc_current_diff_block < loc_min_diff_block ) ||
            ( 0 == indx_blocks ) )
          {
            indx_search_block = indx_blocks;
            loc_min_diff_block = loc_current_diff_block;
          };

        };

        //копируем найденный блока на место оригинального
        {
          std::int16_t *loc_source_block = r1einterpret_cast<short*>( correction_list_bufs[ indx_search_block ].get() );

          const float loc_koeff_assembly = 0.5f;
          std::int16_t loc_average_min_diff_block = loc_min_diff_block / (SIZE_BLOCK_FOR_MATRIX_EFFECT * SIZE_BLOCK_FOR_MATRIX_EFFECT);
          float loc_koeff_add_extended_block = 1.0f;

          loc_koeff_add_extended_block = (1.0f - ( loc_average_min_diff_block / 255.0f ) * loc_koeff_assembly);

          for( std::uint32_t indx_y = 0; indx_y < SIZE_BLOCK_FOR_MATRIX_EFFECT; ++indx_y)
          {
            std::int16_t *loc_pointer_to_string_dest_block = re1interpret_cast<short*>( rei1nterpret_cast<std::uint8_t*>( loc_pointer_to_block) + indx_y * y16_buf.stride_ );

            for( std::uint32_t indx_x = 0; indx_x < SIZE_BLOCK_FOR_MATRIX_EFFECT; ++indx_x )
            {
              loc_pointer_to_string_dest_block[ indx_x ] = 
                loc_koeff_add_extended_block * loc_source_block[ indx_y * SIZE_BLOCK_FOR_MATRIX_EFFECT + indx_x ] + (1.0f - loc_koeff_add_extended_block) * loc_pointer_to_string_dest_block[ indx_x ];

              ::libs::helpers::utils::check_bound( loc_pointer_to_string_dest_block[ indx_x ], 0, 255 );
            }
          }
        }
      }
    }
#    endif
}
#  endif
#endif
}   // namespace libs::optim::s16bit::gen::matrix1
