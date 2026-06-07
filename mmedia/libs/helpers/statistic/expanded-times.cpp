/**
\file       expanded-times.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "expanded-times.hpp"

namespace libs::helpers::statistic
{
ExpandedTimes::~ExpandedTimes ()
{
  clear ();
}


ExpandedTimes::storages_type::iterator
ExpandedTimes::find_time (const key_storage_type& id_set)
{
  auto find_set = vals_.find (id_set);
  if (vals_.end () == find_set)
  {
    auto res = vals_.insert (storages_type::value_type (id_set, storage_type ()));
    find_set = res.first;
  }
  return find_set;
}


void
ExpandedTimes::begin (
  const key_storage_type& id_set,
  const key_storage_type& id_element)
{
  time_type ticks        = U3_GET_CURRENT_TIME;
  auto      find_set     = find_time (id_set);
  auto&     elements     = find_set->second;
  auto      find_element = elements.find (id_element);

  if (elements.end () == find_element)
  {
    auto res     = elements.insert (storage_type::value_type (id_element, ExpandedTime ()));
    find_element = res.first;
  }

  ops_.push_back ({ id_set, id_element });
  times_.push_back (ticks);
}


bool
ExpandedTimes::end ()
{
  time_type ticks = U3_GET_CURRENT_TIME;

  if (ops_.empty () || times_.empty () || ops_.size () != times_.size ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  const auto      name = ops_.back ();
  const time_type time = times_.back ();

  ops_.pop_back ();
  times_.pop_back ();

  auto find_set = find_time (name.first);
  if (vals_.end () == find_set)
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  auto& elements     = find_set->second;
  auto  find_element = elements.find (name.second);
  if (elements.end () == find_element)
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  const duration_type diff = ticks - time;

  find_element->second.max_ = std::max< duration_type > (diff, find_element->second.max_);
  find_element->second.min_ = ::libs::helpers::statistic::count_time_type (0) == find_element->second.min_ ? diff : std::min< duration_type > (diff, find_element->second.min_);
  find_element->second.sum_ += diff;

  ++find_element->second.count_;
  return true;
}


void
ExpandedTimes::end_skip ()
{
  if (ops_.empty () || times_.empty () || ops_.size () != times_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
  }

  ops_.pop_back ();
  times_.pop_back ();
}

#ifdef U3_FAKE_DISABLE
void
ExpandedTimes::change_last_name (
  const key_storage_type& id_set,
  const key_storage_type& id_element)
{
  auto& update_element  = ops_.back ();
  update_element.second = id_element;

  auto find = vals_.find (name);
  if (vals_.end () == find)
  {
    vals_.insert (storage_type::value_type (name, ExpandedTime ()));
  }
}
#endif
#ifdef U3_FAKE_DISABLE
void
ExpandedTimes::get (std::list< std::string >& info)
{
  info.clear ();

  std::vector< std::string > beg_strings (vals_.size ());
  int                        max_length = 0;
  std::size_t                indx       = 0;

  //  Генерируем строки до среднего времени и оцениваем максимальное размер среди всех них, чтобы позднее выровнять время по горизонтали.
  for (storage_type::value_type& val : vals_)
  {
    std::size_t  spl = val.first.empty () ? 0 : val.first.find_last_of ('/');
    std::string& add = beg_strings[indx++];

    add        = val.first.empty () ? "???" : val.first.substr (std::string::npos == spl ? 0 : spl + 1, std::string::npos);
    max_length = U3_CAST_INT32 (std::max< std::size_t > (max_length, add.length ()));
  }

  indx = 0;

  for (storage_type::value_type& val : vals_)
  {
    std::string&       add        = beg_strings[indx++];
    const std::int32_t add_spaces = max_length - U3_CAST_INT32 (add.length ()) + 2;

    for (int indx_space = 0; indx_space < add_spaces; ++indx_space)
    {
      add += '.';
    }

    add += val.second.count_ ? std::to_string (val.second.sum_.total_microseconds () / val.second.count_ / 1000.0F) : "x";
    add += " ms";
    add += " (";
    add += std::to_string (val.second.count_);
    add += ")";

    info.push_back (add);
  }
}
#endif

void
ExpandedTimes::visit_with (const std::function< void (const storages_type& vals) >& funct)
{
  funct (vals_);
}


bool
ExpandedTimes::clear ()
{
  bool res = true;
  if (!ops_.empty ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    res = false;
  }
  if (!times_.empty ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    res = false;
  }
  vals_.clear ();
  return res;
}


void
merge (const ExpandedTimes::storage_type& source, ExpandedTimes::storage_type& dest)
{
  for (const auto& val : source)
  {
    dest[val.first] += val.second;
  }
}


void
merge (const ExpandedTimes::storages_type& source, ExpandedTimes::storages_type& dest)
{
  for (const auto& val : source)
  {
    merge (val.second, dest[val.first]);
  }
}
}   // namespace libs::helpers::statistic
