#pragma once
/**
\file       codec-impl-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vcodec_gen
*/

namespace dlls::codecs::vcodec_gen
{
struct CodecImplInfo final {
  //  ext types
  CodecImplInfo () = default;

  void
  reset ()
  {
    // lib_.unload ();   // никогда не выгружаем библиотеки.
    create_codec_   = 0;
    free_codec_     = 0;
    get_codec_info_ = 0;
  }

  bool
  check () const
  {
    if (!lib_.is_loaded ())
    {
      U3_XLOG_WARN ("codec lib not loaded");
      return false;
    }
    return nullptr == create_codec_ || nullptr == free_codec_ || nullptr == get_codec_info_ ? false : true;
  }

  libs::helpers::dlls::dll_type lib_;                  //< Библиотека с реализацией кодека
  funcs::func_get_codec_type    create_codec_   = 0;   //< Функция создания кодека из библиотеки
  funcs::func_free_codec_type   free_codec_     = 0;   //< Функция удаления кодека из библиотеки
  funcs::func_codec_info_type   get_codec_info_ = 0;   //< Функция получения информации о кодеке из библиотеки
};
}   // namespace dlls::codecs::vcodec_gen
