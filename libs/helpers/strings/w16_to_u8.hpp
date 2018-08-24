//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       w16_to_u8.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Р¤Р°Р№Р» СЃ СЂРµР°Р»РёР·Р°С†РёРµР№ С„СѓРЅРєС†РёРё РєРѕРЅРІРµСЂС‚Р°С†РёРё СЃС‚СЂРѕРє.
*/

namespace libs { namespace helpers { namespace strings {
#if 0
  /**
  \brief      Р’СЃРїРѕРјРѕРіР°С‚РµР»СЊРЅР°СЏ С„СѓРЅРєС†РёСЏ РґР»СЏ РєРѕРЅРІРµСЂС‚Р°С†РёРё СЃС‚СЂРѕРєРё РІ РєРѕРґРёСЂРѕРІРєРµ w(16/32) РІ СЃС‚СЂРѕРєСѓ СЃ РєРѕРґРёСЂРѕРІРєРѕР№ utf8.
  \param[in]  str РІС…РѕРґРЅР°СЏ СЃС‚СЂРѕРєР° РІ РєРѕРґРёСЂРѕРІРєРµ w(16/32)
  \retrun     РІС‹С…РѕРґРЅР°СЏ СЃС‚СЂРѕРєР° Рє РєРѕРґРёСЂРѕРІРєРµ utf8
  */
  inline
  std::string w16_to_u8( const std::wstring& str )
  {
    const std::string ret = std::wstring_convert< std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.to_bytes(str);
    return ret;
  }
#endif
}}}      // namespace libs::helpers::strings
