#pragma once
/**
\file       defines-extern-dll-codec-funcs.hpp
\date       28.02.2025
\author     Erashov Anton erashov2026@proton.me
\project    u3_codec_funcs
*/

#ifndef U3_CODEC_CREATE_FUNCT_EXTERN
#  define U3_CODEC_CREATE_FUNCT_EXTERN(name, type)                                                           \
    extern "C" BOOST_SYMBOL_EXPORT void create_codec_##name (::dlls::codecs::codec_gen::CodecGeneric** pobj) \
    {                                                                                                        \
      U3_ASSERT (nullptr == *pobj);                                                                          \
      *pobj = new type;                                                                                      \
    }
#endif

#ifndef U3_CODEC_DELETE_FUNCT_EXTERN
#  define U3_CODEC_DELETE_FUNCT_EXTERN(name, type)                                                         \
    extern "C" BOOST_SYMBOL_EXPORT void delete_codec_##name (::dlls::codecs::codec_gen::CodecGeneric* obj) \
    {                                                                                                      \
      if (obj)                                                                                             \
      {                                                                                                    \
        type* del = dynamic_cast< type* > (obj);                                                           \
        U3_ASSERT (del);                                                                                   \
        delete del;                                                                                        \
      }                                                                                                    \
    }
#endif

#ifndef U3_CODEC_GET_INFO_FUNCT_EXTERN
#  define U3_CODEC_GET_INFO_FUNCT_EXTERN(name, info)                                                        \
    extern "C" BOOST_SYMBOL_EXPORT void get_codec_info_##name (libs::utility::uids::minor::id_val guids[4]) \
    {                                                                                                       \
      constexpr std::array< libs::utility::uids::minor::id_val, 4 > temp = info;                            \
      std::copy (temp.begin (), temp.end (), guids);                                                        \
    }
#endif
