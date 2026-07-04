#if 0
/**
\file       time-stream.cpp
\author     Erashov Anton erashov2026@proton.me
\date       24.06.2022
\project    u3_events_storage
*/
#  include "mmedia/includes/control-defines-includes.hpp"
#  include "mmedia/includes/includes.hpp"
#  include "events-storage-includes_int.hpp"
#  include "time-stream.hpp"

namespace libs::events_storage
{
TimeStream::TimeStream () :
  time_ (std::chrono::system_clock::now ()),
  type_ (StreamTimes::exactly)
{
}


const TimeStream::time_point_type&
TimeStream::get_time () const
{
  return time_;
}


void
TimeStream::set_time (const time_point_type& time)
{
  time_ = time;
}


const StreamTimes&
TimeStream::get_type () const
{
  return type_;
}


void
TimeStream::set_type (const StreamTimes& type)
{
  type_ = type;
}


template< class Archive >
void
TimeStream::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (time_);
  arh& BOOST_SERIALIZATION_NVP (type_);
}


bool
operator< (const TimeStream& left, const TimeStream& right)
{
  const auto& ltime = left.get_type ();
  const auto& rtime = right.get_type ();

  if (StreamTimes::exactly == ltime && StreamTimes::exactly == rtime)
  {
    return left.get_time () < right.get_time ();
  }
  if (StreamTimes::oldest == ltime || StreamTimes::youngest == rtime)
  {
    return true;
  }
  if (StreamTimes::youngest == ltime || StreamTimes::oldest == rtime)
  {
    return false;
  }
  U3_XLOG_ERROR ("compare time" + VTOLOG (U3_CAST_UINT32_FORCE (ltime)) + VTOLOG (U3_CAST_UINT32_FORCE (rtime)));
  return false;
}


std::string
to_string (const TimeStream& val)
{
  auto        ms       = std::chrono::duration_cast< std::chrono::milliseconds > (val.get_time ().time_since_epoch ());
  auto        s        = std::chrono::duration_cast< std::chrono::seconds > (ms);
  std::time_t time     = s.count ();
  auto        fraction = ms.count () % 1000;
  std::string ret      = std::string (std::ctime (&time)) + std::string (".") + std::to_string (fraction) + " : " + to_string (val.get_type ());
  return ret;
}
}   // namespace libs::events_storage

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_storage::TimeStream);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_storage::TimeStream);
#endif
