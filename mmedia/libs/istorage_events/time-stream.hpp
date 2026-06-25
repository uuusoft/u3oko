#pragma once
/**
\file       time-stream.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
\project    u3_istorage_events
*/

namespace boost::archive
{
template< class Archive, typename clock >
void
load (Archive& arh, std::chrono::time_point< clock >& tpc, unsigned)
{
  std::chrono::milliseconds::rep millis;

  arh& BOOST_SERIALIZATION_NVP (millis);
  tpc = std::chrono::time_point< clock > (std::chrono::milliseconds (millis));
}


template< class Archive, typename clock >
void
save (Archive& arh, std::chrono::time_point< clock > const& tpc, unsigned)
{
  std::chrono::milliseconds::rep millis = std::chrono::duration_cast< std::chrono::milliseconds > (tpc.time_since_epoch ()).count ();

  arh& BOOST_SERIALIZATION_NVP (millis);
}


template< class Archive, typename clock >
inline void
serialize (Archive& arh, std::chrono::time_point< clock >& tpc, unsigned version)
{
  boost::serialization::split_free (arh, tpc, version);
}
}   // namespace boost::archive


namespace libs::istorage_events
{
class TimeStream final
{
  public:
  //  ext types
  using time_point_type = std::chrono::system_clock::time_point;

  TimeStream ();
  virtual ~TimeStream () = default;

  const time_point_type& get_time () const;
  void                   set_time (const time_point_type& time);
  const StreamTimes&     get_type () const;
  void                   set_type (const StreamTimes& type);

  private:
  time_point_type time_;   //<
  StreamTimes     type_;   //<

  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */);
};   // namespace istorage_events

bool operator< (const TimeStream& left, const TimeStream& right);

std::string to_string (const TimeStream& val);
void        tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const TimeStream& src);
TimeStream  tag_invoke (::boost::json::value_to_tag< TimeStream >, const ::boost::json::value& jvs);
}   // namespace libs::istorage_events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::TimeStream);
