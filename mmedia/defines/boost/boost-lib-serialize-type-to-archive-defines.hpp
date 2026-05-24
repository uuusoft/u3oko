#pragma once
/**
\file       boost-lib-serialize-type-to-archive-defines.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
\brief      Макрос для сериализации стандартных типов системы (события, свойства etc) в необходимые (возможно в будущем) архивы
*/

#ifndef U3_BOOST_SERIALIZE_ALL_ARCHIVES
#  define U3_BOOST_SERIALIZE_ALL_ARCHIVES(u3def_param)                                                                                \
    template void u3def_param::serialize< boost::archive::xml_iarchive > (boost::archive::xml_iarchive &, const std::uint32_t);       \
    template void u3def_param::serialize< boost::archive::xml_oarchive > (boost::archive::xml_oarchive &, const std::uint32_t);       \
    template void u3def_param::serialize< boost::archive::binary_iarchive > (boost::archive::binary_iarchive &, const std::uint32_t); \
    template void u3def_param::serialize< boost::archive::binary_oarchive > (boost::archive::binary_oarchive &, const std::uint32_t);
#endif
