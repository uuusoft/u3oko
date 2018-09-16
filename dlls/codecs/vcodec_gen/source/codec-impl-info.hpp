#pragma once
/**
\file       codec-impl-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace vcodec_gen {
/**
\brief  empty brief
*/
struct CodecImplInfo
{
  //  ext types
  using lib_type          = boost::dll::shared_library;
  using create_funct_type = boost::function<functs::get_codec_funct_type>;
  using free_funct_type   = boost::function<functs::free_codec_funct_type>;
  using info_funct_type   = boost::function<functs::get_codec_info_funct_type>;

  CodecImplInfo ()
  {
    reset ();
  }

  void
  reset ()
  {
    //lib_.unload (); // никогда не выгружаем библиотеки.
    pf_create_codec_ = 0;
    pf_free_codec_   = 0;
    pf_get_info_     = 0;
    return;
  }

  bool
  check () const
  {
    if (!lib_.is_loaded ())
      {
        return false;
      }
    if (0 == pf_create_codec_ || 0 == pf_free_codec_ || 0 == pf_get_info_)
      {
        return false;
      }
    return true;
  }

  lib_type          lib_;                  //< Библиотека с реализацией кодека.
  create_funct_type pf_create_codec_;      //< Функция создания кодека из библиотеки.
  free_funct_type   pf_free_codec_;        //< Функция удаления кодека из библиотеки.
  info_funct_type   pf_get_info_;          //< Функция получения информации о кодеке из библиотеки.
};

}}}      // namespace dlls::codecs::vcodec_gen
