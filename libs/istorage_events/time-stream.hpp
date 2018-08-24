#pragma once
/**
\file       time-stream.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
namespace boost { namespace archive {

namespace chrn = std::chrono;

template <class Archive, typename clock>
void
load (Archive& ar, chrn::time_point<clock>& tp, unsigned)
{
  chrn::milliseconds::rep _millis;

  ar& BOOST_SERIALIZATION_NVP (_millis);
  tp = chrn::time_point<clock> (chrn::milliseconds (_millis));
  return;
}

template <class Archive, typename clock>
void
save (Archive& ar, chrn::time_point<clock> const& tp, unsigned)
{
  chrn::milliseconds::rep _millis = chrn::duration_cast<chrn::milliseconds> (tp.time_since_epoch ()).count ();

  ar& BOOST_SERIALIZATION_NVP (_millis);
  return;
}

template <class Archive, typename clock>
inline void
serialize (Archive& ar, std::chrono::time_point<clock>& tp, unsigned version)
{
  boost::serialization::split_free (ar, tp, version);
}

}}      // namespace boost::archive


namespace libs { namespace istorage_events {
/**
\brief  Время потока.
*/
class TimeStream final
{
  public:
  //  ext types
  using time_point_type = std::chrono::system_clock::time_point;

  TimeStream () :
    time_ (std::chrono::system_clock::now ()),
    type_ (TypeTimeStream::exactly)
  {}

  const time_point_type&
  get_time () const
  {
    return time_;
  }

  void
  set_time (const time_point_type& _time)
  {
    time_ = _time;
    return;
  }

  const TypeTimeStream&
  get_type () const
  {
    return type_;
  }

  void
  set_type (const TypeTimeStream& _type)
  {
    type_ = _type;
    return;
  }


  private:
  time_point_type time_;      //< Текущее время потока.
  TypeTimeStream  type_;      //< Тип времени.

  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (time_);
    ar& BOOST_SERIALIZATION_NVP (type_);
    return;
  }
};      // namespace istorage_events


inline bool
operator< (const TimeStream& _left, const TimeStream& _right)
{
  const auto& _ltime = _left.get_type ();
  const auto& _rtime = _right.get_type ();

  if (TypeTimeStream::exactly == _ltime && TypeTimeStream::exactly == _rtime)
    {
      return _left.get_time () < _right.get_time ();
    }
  if (TypeTimeStream::oldest == _ltime || TypeTimeStream::youngest == _rtime)
    {
      return true;
    }
  if (TypeTimeStream::youngest == _ltime || TypeTimeStream::oldest == _rtime)
    {
      return false;
    }
  XULOG_ERROR ("failed compare time, " << UUU_ICAST_INT (_ltime) << ", " << UUU_ICAST_INT (_rtime));
  return false;
}


inline std::string
to_str (const TimeStream& _val)
{
  auto        _ms       = std::chrono::duration_cast<std::chrono::milliseconds> (_val.get_time ().time_since_epoch ());
  auto        _s        = std::chrono::duration_cast<std::chrono::seconds> (_ms);
  std::time_t _time     = _s.count ();
  auto        _fraction = _ms.count () % 1000;
  std::string _ret      = std::string (std::ctime (&_time)) + std::string (".") + ::to_str (_fraction) + " : " + to_str (_val.get_type());
  return _ret;
}

}}      // namespace libs::istorage_events
