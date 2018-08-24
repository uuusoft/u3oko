//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       serialize_type_to_archive_define.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      Макрос для сериализации стандартных типов системы (события, свойства и т.п.) в необходимые (возможно в будущем) архивы.
*/

#ifndef SERIALIZE_TYPE_TO_ARCHIVES
#define SERIALIZE_TYPE_TO_ARCHIVES(_type)                                                                                     \
  template void _type::serialize<boost::archive::text_iarchive> (boost::archive::text_iarchive & ar, const unsigned int);     \
  template void _type::serialize<boost::archive::text_oarchive> (boost::archive::text_oarchive & ar, const unsigned int);     \
  template void _type::serialize<boost::archive::xml_iarchive> (boost::archive::xml_iarchive & ar, const unsigned int);       \
  template void _type::serialize<boost::archive::xml_oarchive> (boost::archive::xml_oarchive & ar, const unsigned int);       \
  template void _type::serialize<boost::archive::binary_iarchive> (boost::archive::binary_iarchive & ar, const unsigned int); \
  template void _type::serialize<boost::archive::binary_oarchive> (boost::archive::binary_oarchive & ar, const unsigned int);
#endif
