//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       convert_event2string_funct.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events { namespace helpers {
/**
  \brief      ��������������� ������� ��� "��������" �������� ��������� �� ���������-������.
  \param[in]  _msg  ��������� �� ��������.
  \return     ������� ���������.
  */
inline std::string
to_str (IEvent::craw_ptr _event)
{
  UASSERT (_event);
  std::stringstream             _strstream;
  boost::archive::text_oarchive _arc (_strstream);
  _arc << *_event;
  return _strstream.str ();
}

}}}      // namespace libs::events::helpers
