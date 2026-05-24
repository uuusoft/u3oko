#pragma once
/**
\file       time-stream.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.07.2018
\project    u3_istorage_events
*/

namespace boost::archive
{
template< class Archive, typename clock >
void
load (Archive& ar, std::chrono::time_point< clock >& tp, unsigned)
{
  std::chrono::milliseconds::rep millis;

  ar& BOOST_SERIALIZATION_NVP (millis);
  tp = std::chrono::time_point< clock > (std::chrono::milliseconds (millis));
}


template< class Archive, typename clock >
void
save (Archive& ar, std::chrono::time_point< clock > const& tp, unsigned)
{
  std::chrono::milliseconds::rep millis = std::chrono::duration_cast< std::chrono::milliseconds > (tp.time_since_epoch ()).count ();

  ar& BOOST_SERIALIZATION_NVP (millis);
}


template< class Archive, typename clock >
inline void
serialize (Archive& ar, std::chrono::time_point< clock >& tp, unsigned version)
{
  boost::serialization::split_free (ar, tp, version);
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
  virtual ~TimeStream ();

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
  serialize (Archive& ar, const std::uint32_t /* file_version */);
};   // namespace istorage_events

bool operator< (const TimeStream& left, const TimeStream& right);

std::string to_string (const TimeStream& val);
void        tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const TimeStream& src);
TimeStream  tag_invoke (::boost::json::value_to_tag< TimeStream >, const ::boost::json::value& jv);
}   // namespace libs::istorage_events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::TimeStream);
