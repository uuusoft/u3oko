#pragma once
/**
\file       links-application.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_properties_libs
*/

namespace libs::properties::vers::links::mids
{
using key_storage_type = std::pair< libs::link::details::ModuleLinks, libs::link::details::ModuleLinks >;

inline constexpr key_storage_type appl2log { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type log2appl { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::appl };

inline constexpr key_storage_type http2appl { libs::link::details::ModuleLinks::http, libs::link::details::ModuleLinks::appl };
inline constexpr key_storage_type http2log { libs::link::details::ModuleLinks::http, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type log2http { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::http };
inline constexpr key_storage_type appl2http { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::http };

inline constexpr key_storage_type mdata2appl { libs::link::details::ModuleLinks::mdata, libs::link::details::ModuleLinks::appl };
inline constexpr key_storage_type mdata2log { libs::link::details::ModuleLinks::mdata, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type log2mdata { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::mdata };
inline constexpr key_storage_type appl2mdata { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::mdata };

inline constexpr key_storage_type gui2appl { libs::link::details::ModuleLinks::gui, libs::link::details::ModuleLinks::appl };
inline constexpr key_storage_type gui2log { libs::link::details::ModuleLinks::gui, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type log2gui { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::gui };
inline constexpr key_storage_type appl2gui { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::gui };

inline constexpr key_storage_type events2appl { libs::link::details::ModuleLinks::events, libs::link::details::ModuleLinks::appl };
inline constexpr key_storage_type log2events { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::events };
inline constexpr key_storage_type events2log { libs::link::details::ModuleLinks::events, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type appl2events { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::events };

inline constexpr key_storage_type storage2appl { libs::link::details::ModuleLinks::storage, libs::link::details::ModuleLinks::appl };
inline constexpr key_storage_type storage2log { libs::link::details::ModuleLinks::storage, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type log2storage { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::storage };
inline constexpr key_storage_type appl2storage { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::storage };

inline constexpr key_storage_type network2appl { libs::link::details::ModuleLinks::network, libs::link::details::ModuleLinks::appl };
inline constexpr key_storage_type network2log { libs::link::details::ModuleLinks::network, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type log2network { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::network };
inline constexpr key_storage_type appl2network { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::network };

inline constexpr key_storage_type users2appl { libs::link::details::ModuleLinks::users, libs::link::details::ModuleLinks::appl };
inline constexpr key_storage_type users2log { libs::link::details::ModuleLinks::users, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type log2users { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::users };
inline constexpr key_storage_type appl2users { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::users };

inline constexpr key_storage_type ai2appl { libs::link::details::ModuleLinks::ai, libs::link::details::ModuleLinks::appl };
inline constexpr key_storage_type ai2log { libs::link::details::ModuleLinks::ai, libs::link::details::ModuleLinks::log };
inline constexpr key_storage_type log2ai { libs::link::details::ModuleLinks::log, libs::link::details::ModuleLinks::ai };
inline constexpr key_storage_type appl2ai { libs::link::details::ModuleLinks::appl, libs::link::details::ModuleLinks::ai };

inline constexpr key_storage_type unknown { libs::link::details::ModuleLinks::unknown, libs::link::details::ModuleLinks::unknown };
}   // namespace libs::properties::vers::links::mids

namespace libs::properties::vers::links
{
struct pair_hash {
  template< class T1, class T2 >
  std::size_t
  operator() (const std::pair< T1, T2 >& p) const
  {
    const auto h1 = std::hash< std::uint32_t > {}(U3_CAST_UINT32_FORCE (p.first));
    const auto h2 = std::hash< std::uint32_t > {}(U3_CAST_UINT32_FORCE (p.second));
    return U3_CAST_UINT32_FORCE (h1) ^ (U3_CAST_UINT32_FORCE (h2) << 1);
  }
};

/// Структура для группировки связей модуля
/// link_ptr_type тип хранимого указателя, у владельцев он shared, у агрегатов weak
template< typename TTLinkPtr >
struct LinksApplication final {
  public:
  //  ext types
  using link_ptr_type      = TTLinkPtr;                                                                 //<
  using key_storage_type   = libs::properties::vers::links::mids::key_storage_type;                     //<
  using links_storage_type = boost::unordered_flat_map< key_storage_type, link_ptr_type, pair_hash >;   //<

  LinksApplication () = default;

  ~LinksApplication () noexcept
  {
    reset ();
  }

  template< typename TTLinkPtrRsp >
  void
  copy_links (const LinksApplication< TTLinkPtrRsp >& rsh, bool debug = false)
  {
    std::scoped_lock lock (threadsan_mtx_, rsh.threadsan_mtx_);
    module_links_.clear ();
    for (const auto& [key, val] : rsh.module_links_)
    {
      module_links_[key] = val;
      if (debug)
      {
        U3_XLOG_DEV ("copy link" + TOLOG (to_string (key)) + PTR_TOLOG (module_links_[key].lock ().get ()) + PTR_TOLOG (this));
      }
    }
  }

  void
  reset () noexcept
  {
    std::scoped_lock lock (threadsan_mtx_);
    module_links_.clear ();
  }

  bool
  self_test () const
  {
    return true;
  }

  const TTLinkPtr
  operator[] (const key_storage_type& key) const
  {
    std::scoped_lock lock (threadsan_mtx_);
    auto             finger = module_links_.find (key);
    U3_CHECK_NT (finger != module_links_.end (), "failed get link to module" + TOLOG (to_string (key)) + PTR_TOLOG (this));
    return finger != module_links_.end () ? finger->second : TTLinkPtr ();
  }

  auto
  set (const key_storage_type& key, const TTLinkPtr& ptr) -> void
  {
    std::scoped_lock lock (threadsan_mtx_);
    module_links_[key] = ptr;
  }

  void
  reset_link (const key_storage_type& key)
  {
    std::scoped_lock lock (threadsan_mtx_);
    auto             finger = module_links_.find (key);
    U3_CHECK_NT (finger != module_links_.end (), "failed get link to module" + TOLOG (to_string (key)) + PTR_TOLOG (this));
    if (finger != module_links_.end ())
    {
      finger->second.reset ();
    }
  }

  // EAI-REFACT -> private
#ifdef U3_FORCE_SYNC_FOR_THREAD_SANITIZER
  using sync_type = std::mutex;
#else
  using sync_type = ::libs::utility::thread::EmptyMutex;
#endif

  mutable sync_type  threadsan_mtx_;   //< чтобы успокоить thread sanitizer, т.к. объекты этого типа могут использоваться повторно то и в разных потоках но с разделением по времени
  links_storage_type module_links_;    //<
};
}   // namespace libs::properties::vers::links
