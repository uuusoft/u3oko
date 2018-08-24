//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ExpandedTimeStatistic.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "expanded-time-statistic.hpp"

namespace libs { namespace helpers { namespace statistic {

ExpandedTimeStatistic::ExpandedTimeStatistic ()
{}


ExpandedTimeStatistic::~ExpandedTimeStatistic ()
{
  CHECK_CALL_NO_THROW (clear ());
  return;
}


void
ExpandedTimeStatistic::begin (const std::string& _name)
{
  time_type _ticks = UUU_GET_CURRENT_TIME;
  auto      _find  = vals_.find (_name);

  if (vals_.end () == _find)
    {
      vals_.insert (storage_type::value_type (_name, ElementStatInfo ()));
    }

  ops_.push_back (_name);
  times_.push_back (_ticks);
  return;
}


bool
ExpandedTimeStatistic::end ()
{
  time_type _ticks = UUU_GET_CURRENT_TIME;

  if (ops_.empty () || times_.empty () || ops_.size () != times_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  const std::string _name = ops_.back ();
  const time_type   _time = times_.back ();

  ops_.pop_back ();
  times_.pop_back ();

  auto _find = vals_.find (_name);
  if (vals_.end () == _find)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  duration_type _diff = _ticks - _time;

  _find->second.max_ = std::max<duration_type> (_diff, _find->second.max_);
  _find->second.min_ = count_time_type (0) == _find->second.min_ ? _diff : std::min<duration_type> (_diff, _find->second.min_);
  _find->second.sum_ += _diff;      //( _find->second.aver_ * _find->second.count_ + _diff ) / ( _find->second.count_ + 1 );

  ++_find->second.count_;
  return true;
}


void
ExpandedTimeStatistic::end_skip ()
{
  if (ops_.empty () || times_.empty () || ops_.size () != times_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return;
    }

  ops_.pop_back ();
  times_.pop_back ();
  return;
}


void
ExpandedTimeStatistic::change_last_name (const std::string& _name)
{
  UASSERT (!_name.empty ());
  UASSERT (!ops_.empty ());
  ops_.back () = _name;

  auto _find = vals_.find (_name);
  if (vals_.end () == _find)
    {
      vals_.insert (storage_type::value_type (_name, ElementStatInfo ()));
    }
  return;
}


void
ExpandedTimeStatistic::get (std::list<std::string>& _info)
{
  _info.clear ();

  std::vector<std::string> _beg_strings (vals_.size ());
  int                      _max_length = 0;
  std::size_t              _indx       = 0;

  //  Генерируем строки до сренего времени и оцениваем максимальное размер среди всех них, чтобы позднее выровнять время по горизонтали.
  for (storage_type::value_type& _val : vals_)
    {
      std::size_t  _spl = _val.first.empty () ? 0 : _val.first.find_last_of ('/');
      std::string& _add = _beg_strings[_indx++];

      _add        = _val.first.empty () ? "???" : _val.first.substr (std::string::npos == _spl ? 0 : _spl + 1, std::string::npos);
      _max_length = UUU_ICAST_INT (std::max<std::size_t> (_max_length, _add.length ()));
    }

  _indx = 0;

  for (storage_type::value_type& _val : vals_)
    {
      std::string& _add        = _beg_strings[_indx++];
      const int    _add_spaces = _max_length - UUU_ICAST_INT (_add.length ()) + 2;

      for (int _indx_space = 0; _indx_space < _add_spaces; ++_indx_space)
        {
          _add += '.';
        }

      _add += _val.second.count_ ? to_str (_val.second.sum_.total_microseconds () / _val.second.count_ / 1000.0f) : "x";
      _add += " ms";
      _add += " (";
      _add += to_str (_val.second.count_);
      _add += ")";

      _info.push_back (_add);
    }
  return;
}


bool
ExpandedTimeStatistic::clear ()
{
  if (!ops_.empty ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }
  if (!times_.empty ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  vals_.clear ();
  return true;
}

}}}      // namespace libs::helpers::statistic
