/**
\file LoadListImageForMatrixEffect.cpp
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
template< typename CElement >
bool
CreateVertInvCopy (
  const CElement* source,
  CElement*       dest,
  std::uint32_t   stride_bytes,
  std::uint32_t   height)
{
  ::libs::utility::checks::throw_ifn (source);
  ::libs::utility::checks::throw_ifn (dest);
  ::libs::utility::checks::throw_ifn (stride_bytes);
  ::libs::utility::checks::throw_ifn (height);

  for (uint32_t indx_string = 0; indx_string < height; ++indx_string)
  {
    std::uint32_t offset_dest = (height - indx_string - 1) * stride_bytes;
    ::base_funcs::mem::copy (
      r1einterpret_cast< void* > (r1einterpret_cast< std::uint8_t* > (dest) + offset_dest),
      r1einterpret_cast< const void* > (r1einterpret_cast< const std::uint8_t* > (source) + indx_string * stride_bytes),
      stride_bytes);
  }
  return true;
}
/**
\breif
\
*/
template< typename CElement >
bool
CreateHorInvCopy (
  const CElement* source,
  CElement*       dest,
  std::uint32_t   stride_bytes,
  std::uint32_t   height)
{
  ::libs::utility::checks::throw_ifn (source);
  ::libs::utility::checks::throw_ifn (dest);
  ::libs::utility::checks::throw_ifn (stride_bytes);
  ::libs::utility::checks::throw_ifn (height);

  std::uint32_t loc_width = stride_bytes / sizeof (CElement);
  ::libs::utility::checks::throw_ifn (loc_width);
  for (uint32_t indx_string = 0; indx_string < height; ++indx_string)
  {
    for (uint32_t indx_x = 0; indx_x < loc_width; ++indx_x)
    {
      dest[loc_width - 1 - indx_x] = source[indx_x];
    }
    source = r1einterpret_cast< const CElement* > (r1einterpret_cast< const std::uint8_t* > (source) + stride_bytes);
    dest   = r1einterpret_cast< CElement* > (r1einterpret_cast< std::uint8_t* > (dest) + stride_bytes);
  }
  return true;
}


template< typename CElement >
bool
CreateRShiftCopy (
  const CElement* source,
  CElement*       dest,
  std::uint32_t   stride_bytes,
  std::uint32_t   height,
  std::uint32_t   right_shift)
{
  ::libs::utility::checks::throw_ifn (source);
  ::libs::utility::checks::throw_ifn (dest);
  ::libs::utility::checks::throw_ifn (stride_bytes);
  ::libs::utility::checks::throw_ifn (height);

  base_funcs::c1heck_bound< std::uint32_t > (right_shift, 1, 7);

  std::uint32_t loc_width = stride_bytes / sizeof (CElement);
  ::libs::utility::checks::throw_ifn (loc_width);
  for (uint32_t indx_string = 0; indx_string < height; ++indx_string)
  {
    for (uint32_t indx_x = 0; indx_x < loc_width; ++indx_x)
    {
      dest[indx_x] = (source[indx_x] >> right_shift);
    }
    source = r1einterpret_cast< const CElement* > (re1interpret_cast< const std::uint8_t* > (source) + stride_bytes);
    dest   = r1einterpret_cast< CElement* > (rei1nterpret_cast< std::uint8_t* > (dest) + stride_bytes);
  }
  return true;
}
#endif

void
Filter::load_images (InfoFilter* finfo)
{
  finfo->use_ext_files_ = false;

  ::libs::utility::checks::throw_exception ("failed");
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  std::vector< std::string > loc_list_files;

  finfo->y16_meffects_.clear ();
  finfo->uv16_meffects_.clear ();
  finfo->m_array_stride_bufs_matrix_effect.clear ();

  finfo->ext_y16_meffects_.clear ();
  finfo->ext_uv16_meffects_.clear ();
  finfo->m_array_stride_extended_bufs_matrix_effect.clear ();

  if (!finfo->props_.folder_.empty ())
  {
    // получаем полный список файлов
    icore::files::DefaultFileMask check_cond ("?.bmp?");
    icore::files::g - et_files (finfo->props_.folder_, loc_list_files, false, true, false, check_cond);

    if (loc_list_files.size () <= 0)
    {
      return;
    }
  }

  std::uint32_t loc_current_add_elements          = 0;
  std::uint32_t loc_current_add_extended_elements = 0;

  // цикл обхода по всем файлам, загружаем и анализаируем свойства
  for (std::size_t indx1 = 0; indx1 < loc_list_files.size (); ++indx1)
  {
    std::vector< base_funcs::mem::CCharBlock >* loc_array_y16_matrix_effect         = &finfo->y16_meffects_;
    std::vector< base_funcs::mem::CCharBlock >* loc_array_uv16_matrix_effect        = &finfo->uv16_meffects_;
    std::vector< int >*                         loc_array_stride_bufs_matrix_effect = &finfo->m_array_stride_bufs_matrix_effect;
    std::uint32_t*                              loc_loc_current_add_elements        = &loc_current_add_elements;
    bool                                        loc_current_cycle_exended           = false;
    std::string                                 loc_name_file;

    // 10.02.2016 если это специальный файл фикисруем его присуствие и индекс, и пропускам его
    // обработку надо произвести в отдельный список. Файл будет использоваться как источник замещения
    if ((loc_list_files[indx1] == "ExtendedTemplateBlockBlack_4x4.bmp") ||
        (loc_list_files[indx1] == "ExtendedTemplateBlockBlack_6x6.bmp") ||
        (loc_list_files[indx1] == "ExtendedTemplateBlockBlack_8x8.bmp") ||
        (loc_list_files[indx1] == "ExtendedTemplateBlockColor_8x8.bmp"))
    {
      finfo->use_ext_files_     = true;
      loc_current_cycle_exended = true;

      loc_array_y16_matrix_effect         = &finfo->ext_y16_meffects_;
      loc_array_uv16_matrix_effect        = &finfo->ext_uv16_meffects_;
      loc_array_stride_bufs_matrix_effect = &finfo->m_array_stride_extended_bufs_matrix_effect;
      loc_loc_current_add_elements        = &loc_current_add_extended_elements;
    }

    icore::files::make_path (finfo->props_.folder_, loc_list_files[indx1], loc_name_file);

    std::int16_t* y16              = 0;
    std::int16_t* uv16             = 0;
    int           loc_width        = 0;
    int           loc_height       = 0;
    int           loc_stride_byte  = 0;
    int           loc_max_size_buf = 0;

    if (!helpers::bmp::LoadBMP32FileToY16UV16Format (
          finfo->pfuncs2_.m_rgb32tor16g16b16_convert_funct,
          finfo->pfuncs_[::libs::optim::helpers::ofc1Mirror],
          finfo->pfuncs2_.m_r16g16b16torgb24_funct,
          finfo->pfuncs2_.m_rgb24toyuy2_funct,
          finfo->pfuncs_[::libs::optim::helpers::ofc1YuY2_to_Y16UV16],
          loc_name_file,
          &y16,
          &uv16,
          &loc_width,
          &loc_height,
          &loc_stride_byte,
          0,
          &loc_max_size_buf))
    {
      ::libs::utility::checks::throw_exception ("failed");
      continue;
    }

    // если требуется приводим размер буфера к 8х8
    {
      if ((8 > loc_width) || (8 > loc_height))
      {
        ::libs::utility::checks::throw_exception ("failed");
        // loc_name_file.DumpString();
        continue;
      }

#  define MAX_SUPPORT_IMAGE_LIST_MAXTRIX_EFFECT (10 * 1024)
      for (int indx_y_add_block = 0; indx_y_add_block < loc_height / 8; ++indx_y_add_block)
      {
        for (int indx_x_add_block = 0; indx_x_add_block < loc_width / 8; ++indx_x_add_block)
        {
          if ((*loc_loc_current_add_elements) > MAX_SUPPORT_IMAGE_LIST_MAXTRIX_EFFECT)
            break;

          loc_array_y16_matrix_effect->resize ((*loc_loc_current_add_elements) + 1);
          loc_array_uv16_matrix_effect->resize ((*loc_loc_current_add_elements) + 1);
          loc_array_stride_bufs_matrix_effect->resize ((*loc_loc_current_add_elements) + 1);

          std::uint8_t* loc_y16_mackroblock  = 0;
          std::uint8_t* loc_uv16_mackroblock = 0;

#  define SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT (8 * sizeof (std::int16_t))
#  define FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT (8 * SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT)

          ::libs::utility::checks::throw_exception ("failed");   // mem
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
          ::base_funcs::mem::u3alloc (::libs::utility::casts::reinterpret_cast_helper< void** > (&loc_y16_mackroblock), FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT);
          ::base_funcs::mem::u3alloc (::libs::utility::casts::reinterpret_cast_helper< void** > (&loc_uv16_mackroblock), FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT);
#  endif
          for (uint32_t indx_copy_string_macroblock = 0; indx_copy_string_macroblock < 8; ++indx_copy_string_macroblock)
          {
            std::uint8_t* loc_begin_string_y16_makroblock =
              re1interpret_cast< std::uint8_t* > (y16) + (indx_y_add_block * 8 + indx_copy_string_macroblock) * loc_stride_byte + indx_x_add_block * SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT;

            std::uint8_t* loc_begin_string_uv16_makroblock =
              re1interpret_cast< std::uint8_t* > (uv16) + (indx_y_add_block * 8 + indx_copy_string_macroblock) * loc_stride_byte + indx_x_add_block * SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT;

            ::libs::utility::checks::throw_exception ("failed");   // mem
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
            ::base_funcs::mem::copy (
              loc_y16_mackroblock + indx_copy_string_macroblock * SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT,
              loc_begin_string_y16_makroblock,
              SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT,
              0);

            ::base_funcs::mem::copy (
              loc_uv16_mackroblock + indx_copy_string_macroblock * SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT,
              loc_begin_string_uv16_makroblock,
              SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT,
              0);
#  endif
          }

          (*loc_array_y16_matrix_effect)[(*loc_loc_current_add_elements)].set (loc_y16_mackroblock, FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT);
          (*loc_array_uv16_matrix_effect)[(*loc_loc_current_add_elements)].set (loc_uv16_mackroblock, FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT);

          (*loc_array_stride_bufs_matrix_effect)[(*loc_loc_current_add_elements)] = SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT;

          loc_y16_mackroblock  = 0;
          loc_uv16_mackroblock = 0;

          (*loc_loc_current_add_elements)++;
        }
      }

      ::libs::utility::checks::throw_exception ("failed");   // mem
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
      ::base_funcs::mem::u3free (::libs::utility::casts::reinterpret_cast_helper< void** > (&y16));
      ::base_funcs::mem::u3free (::libs::utility::casts::reinterpret_cast_helper< void** > (&uv16));
#  endif
      y16  = 0;
      uv16 = 0;
    }
  }

  // 26.12.2016EAI extended list image
  if (finfo->props_.replicate_images_)
  {
    std::uint32_t count_loaded_image = finfo->y16_meffects_.size ();
    std::uint32_t count_new_image    = count_loaded_image * 4;

    finfo->y16_meffects_.resize (count_new_image);
    finfo->uv16_meffects_.resize (count_new_image);
    finfo->m_array_stride_bufs_matrix_effect.resize (count_new_image);

    for (uint32_t indx_original = 0; indx_original < count_loaded_image; ++indx_original)
    {
      std::uint32_t indx_new        = count_loaded_image + 3 * indx_original;
      std::uint8_t* loc_mackroblock = 0;

      std::vector< base_funcs::mem::CCharBlock >* array_vectors[] = {
        &finfo->y16_meffects_,
        &finfo->uv16_meffects_
      };

      for (uint32_t indx_vectors = 0; indx_vectors < std::size (array_vectors); ++indx_vectors)
      {
        if (0 == (*array_vectors[indx_vectors])[indx_original].get ())
        {
          ::libs::utility::checks::throw_exception ("failed");
          continue;
        }

        ::libs::utility::checks::throw_exception ("failed");   // mem
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
        loc_mackroblock = 0;
        ::base_funcs::mem::u3alloc (::libs::utility::casts::reinterpret_cast_helper< void** > (&loc_mackroblock), FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT);
        ret = CreateVertInvCopy< std::uint8_t > (
          (*array_vectors[indx_vectors])[indx_original].get (),
          loc_mackroblock,
          SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT,
          8);
        C1HECK_CALLS ((*array_vectors[indx_vectors])[indx_new + 0].set (loc_mackroblock, FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT));

        loc_mackroblock = 0;
        ::base_funcs::mem::u3alloc (::libs::utility::casts::reinterpret_cast_helper< void** > (&loc_mackroblock), FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT);
        C1HECK_CALLS (CreateHorInvCopy< short > (
          r1einterpret_cast< short* > ((*array_vectors[indx_vectors])[indx_original].get ()),
          re1interpret_cast< short* > (loc_mackroblock),
          SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT,
          8));
        C1HECK_CALLS ((*array_vectors[indx_vectors])[indx_new + 1].set (loc_mackroblock, FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT));

        loc_mackroblock = 0;
        ::base_funcs::mem::u3alloc (::libs::utility::casts::reinterpret_cast_helper< void** > (&loc_mackroblock), FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT);
        C1HECK_CALLS (CreateHorInvCopy< short > (
          r1einterpret_cast< short* > ((*array_vectors[indx_vectors])[indx_new + 0].get ()),
          re1interpret_cast< short* > (loc_mackroblock),
          SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT,
          8));
        C1HECK_CALLS ((*array_vectors[indx_vectors])[indx_new + 2].set (loc_mackroblock, FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT));
#  endif
      }

      finfo->m_array_stride_bufs_matrix_effect[indx_new + 0] = finfo->m_array_stride_bufs_matrix_effect[indx_original];
      finfo->m_array_stride_bufs_matrix_effect[indx_new + 1] = finfo->m_array_stride_bufs_matrix_effect[indx_original];
      finfo->m_array_stride_bufs_matrix_effect[indx_new + 2] = finfo->m_array_stride_bufs_matrix_effect[indx_original];
    }

    const std::uint32_t array_rshift[] = { 1, 2 };

    count_loaded_image = finfo->y16_meffects_.size ();
    count_new_image    = count_loaded_image * (std::size (array_rshift) + 1);

    finfo->y16_meffects_.resize (count_new_image);
    finfo->uv16_meffects_.resize (count_new_image);
    finfo->m_array_stride_bufs_matrix_effect.resize (count_new_image);

    for (uint32_t indx_original = 0; indx_original < count_loaded_image; ++indx_original)
    {
      std::uint32_t indx_new        = count_loaded_image + std::size (array_rshift) * indx_original;
      std::uint8_t* loc_mackroblock = 0;

      std::vector< base_funcs::mem::CCharBlock >* array_vectors[] = {
        &finfo->y16_meffects_,
        &finfo->uv16_meffects_
      };

      for (uint32_t indx_vectors = 0; indx_vectors < std::size (array_vectors); ++indx_vectors)
      {
        if (0 == (*array_vectors[indx_vectors])[indx_original].get ())
        {
          ::libs::utility::checks::throw_exception ("failed");
          continue;
        }

        for (uint32_t right_shift = 0; right_shift < std::size (array_rshift); ++right_shift)
        {
          loc_mackroblock = 0;

          ::libs::utility::checks::throw_exception ("failed");   // mem
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
          ::base_funcs::mem::u3alloc (::libs::utility::casts::reinterpret_cast_helper< void** > (&loc_mackroblock), FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT);
#  endif
          ::libs::utility::checks::throw_ifn (CreateRShiftCopy< short > (
            re1interpret_cast< short* > ((*array_vectors[indx_vectors])[indx_original].get ()),
            rei1nterpret_cast< short* > (loc_mackroblock),
            SIZE_BYTE_LINE_MACKROBLOCK_MATRIX_EFFECT,
            8,
            array_rshift[right_shift]));
          ::libs::utility::checks::throw_ifn ((*array_vectors[indx_vectors])[indx_new + right_shift].set (loc_mackroblock, FULL_SIZE_MACKROBLOCK_MATRIX_EFFECT));

          finfo->m_array_stride_bufs_matrix_effect[indx_new + right_shift] = finfo->m_array_stride_bufs_matrix_effect[indx_original];
        }
      }
    }
  }
  // 26.12.2016EAI remove duplicate image
  {
    for (uint32_t indx_original = 0; indx_original < finfo->y16_meffects_.size (); ++indx_original)
    {
      for (uint32_t indx_check = indx_original + 1; indx_check < finfo->y16_meffects_.size (); ++indx_check)
      {
        if ((0 == finfo->y16_meffects_[indx_original].get ()) ||
            (0 == finfo->y16_meffects_[indx_check].get ()))
        {
          continue;
        }
        if (0 == memcmp (
                   finfo->y16_meffects_[indx_original].get (),
                   finfo->y16_meffects_[indx_check].get (),
                   finfo->y16_meffects_[indx_original].byte_size ()))
        {
          finfo->y16_meffects_.erase (finfo->y16_meffects_.begin () + indx_check);
          finfo->uv16_meffects_.erase (finfo->uv16_meffects_.begin () + indx_check);
          finfo->m_array_stride_bufs_matrix_effect.erase (finfo->m_array_stride_bufs_matrix_effect.begin () + indx_check);
          indx_check--;
        }
      }
    }
  }
  // 10.02.2016 отдельный цикл, проверяем на соотвествие основных и промежуточных массивов, а также
  // обнуляем не используемые буфера в расширеннм списке
  if (finfo->use_ext_files_)
  {
    if (finfo->ext_y16_meffects_.size () != finfo->y16_meffects_.size ())
    {
      ::libs::utility::checks::throw_exception ("failed");

      finfo->y16_meffects_.resize (finfo->ext_y16_meffects_.size ());
      finfo->uv16_meffects_.resize (finfo->ext_y16_meffects_.size ());
      finfo->m_array_stride_bufs_matrix_effect.resize (finfo->ext_y16_meffects_.size ());
    }
    // рассчет переоринтировал полностью на y компоненту
    {
      std::vector< base_funcs::mem::CCharBlock >& loc_current_extended_buf = finfo->y16_meffects_;   //*( loc_array_extdended_bufs[ indx_in_array_blocks ] );

      for (uint32_t indx1 = 0; indx1 < loc_current_extended_buf.size (); ++indx1)
      {
        std::int16_t* loc_block                 = r1einterpret_cast< short* > (loc_current_extended_buf[indx1].get ());
        std::uint32_t loc_number_block_elements = loc_current_extended_buf[indx1].size () / sizeof (std::int16_t);
        bool          loc_valide_block          = false;

        // рассчет среднего всего блока
        if ((loc_number_block_elements > 0) && loc_block)
        {
          int loc_aver_summ = 0;

          for (uint32_t indx2 = 0; indx2 < loc_number_block_elements; ++indx2)
          {
            loc_aver_summ += loc_block[indx2];
          }

          loc_aver_summ = loc_aver_summ / loc_number_block_elements;

          if (loc_aver_summ > 0x11)
          {
            loc_valide_block = true;
          }
        }
        if (!loc_valide_block)
        {
          ::libs::utility::checks::throw_ifn (loc_current_extended_buf[indx1].set (0, 0));
          ::libs::utility::checks::throw_ifn (finfo->uv16_meffects_[indx1].set (0, 0));
        }
      }
    }
  }
#endif
  return;
}
}   // namespace dnodes::uplifters::vmatrix
