#pragma once
/**
\file       save2jpeg-helper-funcs.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mhttp
*/

namespace modules::mhttp::appl::helpers
{
inline std::int32_t
get_offset_iframe (const std::uint8_t* buf)
{
  U3_ASSERT (buf);
  const auto* head = ::libs::helpers::casts::reinterpret_cast_helper< const ::dlls::codecs::codec_gen::HeaderIFrame* > (buf);
  U3_ASSERT (head->check ());
  return head->base_part_.size_;
}

/// Функция сброса данных  jpeg файл
/// \param[in]  root       путь к файлу
/// \param[in]  name_file  имя выходного файла
/// \param[in]  image      сообственно сообщение с буфером
inline void
save_jpeg2file (
  const std::string&         root,
  const std::string&         name_file,
  syn::ZipDataEvent::raw_ptr image)
{
  U3_ASSERT (!root.empty ());
  U3_ASSERT (!name_file.empty ());
  U3_ASSERT (image);

  auto*       osprops     = ::libs::iproperties::helpers::get_shared_prop_os ();
  auto        iappl       = osprops->get_paths_lockfree ();
  const auto  file_folder = root;
  const auto  file_path   = ::libs::helpers::files::make_path (file_folder, name_file);
  const auto* head        = ::libs::helpers::casts::reinterpret_cast_helper< const ::dlls::codecs::codec_gen::HeaderIFrame* > (&image->get_zip ()[0]);

  U3_ASSERT (head->check ());

  const std::uint8_t* beg          = &image->get_zip ()[0];
  const std::uint8_t* sdata        = beg + head->base_part_.size_;
  const std::uint8_t* cdata        = sdata + head->coff_;
  std::uint32_t       src_size_res = head->csize_;

  try
  {
    std::fstream file (file_path, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
    file.write (::libs::helpers::casts::reinterpret_cast_helper< const char* > (cdata), src_size_res);
    file.flush ();
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_HTTP_EXCEPT (std::string ("write image, ") + excpt.what ());
  }
}
}   // namespace modules::mhttp::appl::helpers
