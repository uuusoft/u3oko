#pragma once
/**
\file       defines-boost-lib-serialize-to-archive.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
\brief      Макросы для сериализации boost
*/

#ifndef U3_BOOST_SERIALIZE_MAKE_NVP
#  define U3_BOOST_SERIALIZE_MAKE_NVP(U3XML_NAME_TYPE, U3BASE_TYPE) \
    boost::serialization::make_nvp (U3XML_NAME_TYPE, boost::serialization::base_object< U3BASE_TYPE > (*this));
#endif


#ifndef U3_BOOST_ADD_SERIALIZE_ARCH
#  define U3_BOOST_ADD_SERIALIZE_ARCH(u3def_param)                                                                                    \
    template void u3def_param::serialize< boost::archive::xml_iarchive > (boost::archive::xml_iarchive &, const std::uint32_t);       \
    template void u3def_param::serialize< boost::archive::xml_oarchive > (boost::archive::xml_oarchive &, const std::uint32_t);       \
    template void u3def_param::serialize< boost::archive::binary_iarchive > (boost::archive::binary_iarchive &, const std::uint32_t); \
    template void u3def_param::serialize< boost::archive::binary_oarchive > (boost::archive::binary_oarchive &, const std::uint32_t);
#endif
