//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       codecs.cpp
\date       13.07.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "codecs.hpp"

namespace libs { namespace helpers { namespace uids { namespace codecs {

const cuuid any_codec ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', 'a', 'n', 'y', ' ', ' ', '0', '0' });
const cuuid mjpeg ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', 'm', 'j', 'p', 'e', 'g', '0', '0' });
const cuuid mjpg1 ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', 'm', 'j', 'p', 'g', '1', '0', '0' });
const cuuid mjpg2 ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', 'm', 'j', 'p', 'g', '2', '0', '0' });
const cuuid mjpg4 ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', 'm', 'j', 'p', 'g', '4', '0', '0' });
const cuuid x264 ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', '2', '6', '4', '0', '0', '0', '0' });
const cuuid x265 ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', '2', '6', '5', '0', '0', '0', '0' });
const cuuid test ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', 't', 'e', 's', 't', '0', '0', '0' });
const cuuid vp7 ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', 'v', 'p', '7', ' ', '0', '0', '0' });
const cuuid vp9 ({ 'u', 'u', 'u', 'v', 'c', 'o', 'd', 'e', 'c', 'v', 'p', '9', ' ', '0', '0', '0' });

const cuuid mp3 ({ 'u', 'u', 'u', 'a', 'c', 'o', 'd', 'e', 'c', 'm', 'p', '3', ' ', '0', '0', '0' });
const cuuid aac ({ 'u', 'u', 'u', 'a', 'c', 'o', 'd', 'e', 'c', 'a', 'a', 'c', ' ', '0', '0', '0' });
const cuuid ogg ({ 'u', 'u', 'u', 'a', 'c', 'o', 'd', 'e', 'c', 'o', 'g', 'g', ' ', '0', '0', '0' });
const cuuid ilbc ({ 'u', 'u', 'u', 'a', 'c', 'o', 'd', 'e', 'c', 'i', 'l', 'b', 'c', '0', '0', '0' });
const cuuid g723_1 ({ 'u', 'u', 'u', 'a', 'c', 'o', 'd', 'e', 'c', 'g', '7', '2', '3', '-', '1', '0' });

}}}}      // namespace libs::helpers::uids::codecs
