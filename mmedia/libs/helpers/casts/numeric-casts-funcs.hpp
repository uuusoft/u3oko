#pragma once
/**
\file       numeric-casts-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2026
\project    u3_helpers_lib
*/

namespace libs::helpers::casts
{
#ifndef U3_CAST_BOOL
#  define U3_CAST_BOOL(u3def_val) ::boost::numeric_cast< bool > (u3def_val)
#endif

#ifndef U3_CAST_INT8
#  define U3_CAST_INT8(u3def_val) ::boost::numeric_cast< std::int8_t > (u3def_val)
#endif

#ifndef U3_CAST_UINT8
#  define U3_CAST_UINT8(u3def_val) ::boost::numeric_cast< std::uint8_t > (u3def_val)
#endif

#ifndef U3_CAST_INT16
#  define U3_CAST_INT16(u3def_val) ::boost::numeric_cast< std::int16_t > (u3def_val)
#endif

#ifndef U3_CAST_UINT16
#  define U3_CAST_UINT16(u3def_val) ::boost::numeric_cast< std::uint16_t > (u3def_val)
#endif

#ifndef U3_CAST_INT32
#  define U3_CAST_INT32(u3def_val) ::boost::numeric_cast< std::int32_t > (u3def_val)
#endif

#ifndef U3_CAST_INT32_FORCE
#  define U3_CAST_INT32_FORCE(u3def_val) ::libs::helpers::casts::static_cast_helper< std::int32_t > (u3def_val)
#endif

#ifndef U3_CAST_UINT32
#  define U3_CAST_UINT32(u3def_val) ::boost::numeric_cast< std::uint32_t > (u3def_val)
#endif

#ifndef U3_CAST_UINT32_FORCE
#  define U3_CAST_UINT32_FORCE(u3def_val) ::libs::helpers::casts::static_cast_helper< std::uint32_t > (u3def_val)
#endif

#ifndef U3_CAST_SIZE_T
#  define U3_CAST_SIZE_T(u3def_val) ::boost::numeric_cast< std::size_t > (u3def_val)
#endif

#ifndef U3_CAST_SIZE_T_FORCE
#  define U3_CAST_SIZE_T_FORCE(u3def_val) ::libs::helpers::casts::static_cast_helper< std::size_t > (u3def_val)
#endif

#ifndef U3_CAST_INT64
#  define U3_CAST_INT64(u3def_val) ::boost::numeric_cast< std::int64_t > (u3def_val)
#endif

#ifndef U3_CAST_INT64_FORCE
#  define U3_CAST_INT64_FORCE(u3def_val) ::libs::helpers::casts::static_cast_helper< std::int64_t > (u3def_val)
#endif

#ifndef U3_CAST_UINT64
#  define U3_CAST_UINT64(u3def_val) ::boost::numeric_cast< std::uint64_t > (u3def_val)
#endif

#ifndef U3_CAST_UINT64_FORCE
#  define U3_CAST_UINT64_FORCE(u3def_val) ::libs::helpers::casts::static_cast_helper< std::uint64_t > (u3def_val)
#endif

#ifndef U3_CAST_FLOAT
#  define U3_CAST_FLOAT(u3def_val) ::boost::numeric_cast< float > (u3def_val)
#endif

#ifndef U3_CAST_DOUBLE
#  define U3_CAST_DOUBLE(u3def_val) ::boost::numeric_cast< double > (u3def_val)
#endif
}   // namespace libs::helpers::casts
