#pragma once
/**
\file       dll-generic-codec-functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      Интерфейс библиотеки кодека.
*/

namespace dlls { namespace codecs { namespace vcodec_gen {
//  forward
class CodecGeneric;

}}}      // namespace dlls::codecs::vcodec_gen

namespace dlls { namespace codecs { namespace vcodec_gen { namespace functs {

using get_codec_info_funct_type = void(::libs::helpers::utils::cuuid* _guid);

using get_codec_funct_type = void(codec_gen::CodecGeneric** _pobj);

using free_codec_funct_type = void(codec_gen::CodecGeneric* _obj);

}}}}      // namespace dlls::codecs::vcodec_gen::functs
