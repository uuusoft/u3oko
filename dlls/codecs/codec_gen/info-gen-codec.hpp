#pragma once
/**
\file       info-gen-codec.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
/**
  \brief  empty brief
  */
struct InfoGenCodec
{
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (InfoGenCodec);

  InfoGenCodec () :
    finfo_ (nullptr)
  {}

  void
  check () const
  {
    CHECK_STATE (finfo_, "failed, empty finfo");
    return;
  }

  ::libs::icore::impl::var1::obj::FilterInfo::raw_ptr finfo_;      //< ???
};

}}}      // namespace dlls::codecs::codec_gen
