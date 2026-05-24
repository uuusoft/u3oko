#pragma once
/**
\file       boost-lib-includes.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_includes
*/
// EAI-REFACT
#if defined(U3_COMPILER_MSC)
#  pragma warning(disable : 4100)
#  pragma warning(disable : 4127)
#  pragma warning(disable : 4244)
#  pragma warning(disable : 4324)
#  pragma warning(disable : 4481)
#  pragma warning(disable : 4503)
#  pragma warning(disable : 4510)
#  pragma warning(disable : 4512)
#  pragma warning(disable : 4610)
#  pragma warning(disable : 4995)
#  pragma warning(disable : 4996)
#  pragma warning(disable : 6011)
#  pragma warning(disable : 6246)
#  pragma warning(disable : 6248)
#  pragma warning(disable : 6285)
#  pragma warning(disable : 6334)
#  pragma warning(disable : 6385)
#  pragma warning(disable : 6386)
#endif

#include <boost/numeric/conversion/cast.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/json.hpp>

// #include <boost/archive/text_iarchive.hpp>
// #include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/tmpdir.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/shared_ptr_132.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/unordered_set.hpp>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_recursive_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

#include <boost/any.hpp>

#include <boost/throw_exception.hpp>
#include <boost/exception_ptr.hpp>

#include <boost/function.hpp>
#include <boost/function_equal.hpp>

#include <boost/algorithm/string.hpp>

#include <boost/throw_exception.hpp>

#include <boost/dll.hpp>

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <boost/container_hash/hash.hpp>
#include <boost/utility.hpp>
