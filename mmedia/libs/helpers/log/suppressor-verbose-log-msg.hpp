#pragma once
/**
\file       suppressor-verbose-log-msg.hpp
\author     Erashov Anton erashov2026@proton.me
\date       07.10.2024
\project    u3_helpers_lib
*/

namespace libs::helpers::log
{
/// Для подавления слишком частых однообразных сообщений
template< typename TTNode, typename TTSync >
class SupressorVerboseLogMsg final
{
  public:
  inline static constexpr std::chrono::minutes max_time_suppress_period { 5 };   //< max time suppress msgs one type
  inline static constexpr std::uint64_t max_count_msg_before_suppress { 50 };    //< max count msgs before suppress

  using storage_node_type       = std::tuple< TTNode, std::uint64_t, std::uint64_t, libs::helpers::time::TimePoint >;   //< info, counter msg, counter suppress, time
  using storage_type            = std::unordered_map< std::string, storage_node_type >;                                 //<
  using flash_function_type     = std::function< void (const storage_node_type& val) >;                                 //<
  using to_string_function_type = std::function< std::string (const TTNode& val) >;                                     //<

  U3_HELPER_DISABLE_ACOPY_TYPE (SupressorVerboseLogMsg)

  explicit SupressorVerboseLogMsg (bool disable = false) :
    disable_ (disable)
  {
  }

  ~SupressorVerboseLogMsg () = default;

  bool
  process (const TTNode& val, to_string_function_type to_string_func)
  {
    if (disable_)
    {
      return true;
    }

    std::scoped_lock lock (mtx_);
    const auto       now    = std::chrono::system_clock::now ();
    const auto       strval = to_string_func (val);
    auto             finger = vals_.find (strval);

    U3_ASSERT (!strval.empty ());
    if (finger == vals_.end ())
    {
      vals_.insert ({ strval, { val, 1, 0, libs::helpers::time::TimePoint (now) } });
      return true;
    }

    const auto old_time             = std::get< 3 > (finger->second).get_time ();
    const auto old_counter          = std::get< 1 > (finger->second);
    const auto old_counter_suppress = std::get< 2 > (finger->second);

    std::get< 1 > (finger->second) = old_counter + 1;
    std::get< 3 > (finger->second).set_time (now);

    if (old_time - now > max_time_suppress_period)
    {
      std::get< 2 > (finger->second) = 0;
      return true;
    }

    std::get< 2 > (finger->second) = old_counter_suppress + 1;
    return old_counter >= max_count_msg_before_suppress ? false : true;
  }

  void
  flash (flash_function_type& flash_func, bool force)
  {
    std::scoped_lock lock (mtx_);

    for (const auto& val : vals_)
    {
      const auto counter_suppress = std::get< 2 > (val->second);
      if (0 == counter_suppress && !force)
      {
        continue;
      }
      flash_func (val.second);
    }
  }

  private:
  const bool   disable_ = false;   //<
  storage_type vals_;              //<
  TTSync       mtx_;               //<
};
}   // namespace libs::helpers::log
